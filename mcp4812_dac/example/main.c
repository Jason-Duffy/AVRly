/******************************************************************************
  FileName    [ main.c ]
  PackageName [ LCD Demo ]
  Description [ Main routine for demonstration of LCD driver on AtMega2560 ]
  Author      [ Jason Duffy ]
  Copyright   [  ]
  Revision    [ v0.0.1
******************************************************************************/

#include <util/delay.h>
#include "mcp4812_dac.h"
#include "log_system.h"

static const char *p_system_tag = "MAIN";

dac_config_t dac_config =
{
	.model = mcp4812,
	.sync_on_reconfigure = true,

	.channel_a.gain_low = false,
	.channel_a.active = true,
	.channel_a.level = 0,

	.channel_b.gain_low = false,
	.channel_b.active = true,
	.channel_b.level = 0,
};

int main()
{
	// Setup
	init_log_system();
	init_dac(&dac_config);
	log_message(p_system_tag, VERBOSE_DEBUG, "Im Here!");

	dac_set_voltage(DAC_CHANNEL_A, 3000U);
	dac_set_voltage(DAC_CHANNEL_B, 1500U);

	// Loop forever
	for(;;)
	{
		dac_set_voltage(DAC_CHANNEL_A, 1000U);
		dac_set_voltage(DAC_CHANNEL_B, 2000U);

	}
}