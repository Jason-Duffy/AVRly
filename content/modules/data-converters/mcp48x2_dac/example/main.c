/******************************************************************************
 @copyright Copyright © 2022 by Jason Duffy.
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
******************************************************************************/

/**
 * @file main.c
 * @ingroup mcp48x2
 * @author Jason Duffy
 * @date 1st March 2022
 * @brief Example main routine demonstrating the mcp48x2 DAC driver. 
 * @bug No known bugs. 
 */

#include <util/delay.h>
#include "mcp48x2_dac.h"

// Edit these values to modify the demo behaviour. 
#define DELAY_TIME_1			1000

#define CHANNEL_A_VOLTAGE_1		1000
#define CHANNEL_B_VOLTAGE_1		2000

#define CHANNEL_A_VOLTAGE_2		3300
#define CHANNEL_B_VOLTAGE_2		1650


/**
 * Instantiation of config object for DAC. 
 */
dac_config_t dac_config =
{
	.model = mcp4812,
	.sync_manually = false,

	.channel_a.gain_low = false,
	.channel_a.active = true,
	.channel_a.level = 0,

	.channel_b.gain_low = false,
	.channel_b.active = true,
	.channel_b.level = 0,
};

/**
 * Main routine of application. 
 */
int main()
{
	// Initialisation of DAC is called here. 
	init_dac(&dac_config);

	// Loop forever.
	while (1)
	{	
		// Set initial voltage levels. 
		dac_set_voltage(DAC_CHANNEL_A, CHANNEL_A_VOLTAGE_1);
		dac_set_voltage(DAC_CHANNEL_B, CHANNEL_B_VOLTAGE_1);

		// Wait a short time. 
		_delay_ms(DELAY_TIME_1);

		// Set secondary voltage levels. 
		dac_set_voltage(DAC_CHANNEL_A, CHANNEL_A_VOLTAGE_2);
		dac_set_voltage(DAC_CHANNEL_B, CHANNEL_B_VOLTAGE_2);

		// Wait a short time. 
		_delay_ms(DELAY_TIME_1);
	}
	
	return 0;
}