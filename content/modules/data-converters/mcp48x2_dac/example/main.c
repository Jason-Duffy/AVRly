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
#include "mcp4812_dac.h"

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

int main()
{
	// Setup
	init_dac(&dac_config);

	dac_set_voltage(DAC_CHANNEL_A, 3000U);
	dac_set_voltage(DAC_CHANNEL_B, 1500U);

	// Loop forever
	for(;;)
	{
		dac_set_voltage(DAC_CHANNEL_A, 1000U);
		dac_set_voltage(DAC_CHANNEL_B, 2000U);
	}
}