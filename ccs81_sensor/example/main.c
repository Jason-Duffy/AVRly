

#include <util/delay.h>
#include "ccs811.h"
#include "log_system.h"

static const char *p_system_tag = "MAIN";

static uint16_t eco2 = 0;
static uint16_t etvoc = 0;

ccs811_config_t ccs811_config =
{
	.drive_mode = drive_mode_1sec,
	.wake_pin_enabled = true,
	.interrupt_dataready = false,
	.interrupt_threshold = false,
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
		if(ccs811_data_ready_check())
		{
			eco2 = ccs811_get_eco2_level();
			log_message_with_16bit_dec_val(p_system_tag, DEBUG, "eCo2 Level: ", eco2);
		
			etvoc = ccs811_get_etvoc_level();
			log_message_with_16bit_dec_val(p_system_tag, DEBUG, "eTVOC Level: ", etvoc);
		}
	}
}