/******************************************************************************
 Copyright (c) 2022 by Jason Duffy
 
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
 * @ingroup ccs811
 * @author Jason Duffy
 * @date 15th March 2022
 * @brief Example main routine to demonstrate taking readings using the CCS811
 * gas sensor.  
 * @bug No known bugs. 
 * @see
 */

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