

#include <util/delay.h>
#include "ccs811.h"
#include "log_system.h"

static const char *p_system_tag = "MAIN";

static uint16_t co2 = 0;

ccs811_config_t ccs811_config =
{
	drive_mode_1sec,
};

int main()
{
	// Setup
	init_log_system();
	uint8_t error = init_ccs811(&ccs811_config);
	log_message_with_dec_val(p_system_tag, ERROR,
							"CCS81 init return code: ", error);
	// Loop forever
	for(;;)
	{
		co2 = ccs811_get_alg_result_data();
		_delay_ms(1000);
		log_message_with_16bit_dec_val(p_system_tag, DEBUG, "Co2 Level: ", co2);
	}
}