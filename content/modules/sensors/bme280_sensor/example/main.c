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
 * @ingroup bme280
 * @author Jason Duffy
 * @date 22nd June 2022
 * @brief Example main routine demonstrating the BME280 sensor. 
 * @bug No known bugs. 
 */

#include <util/delay.h>

#include "bme280.h"
#include "log_system.h"

int16_t temperature = 0;
uint16_t humidity = 0;

log_system_config_t log_system_main = 
{
	.p_system_tag = "Main",
	.file_log_level = DEBUG,
};



int main()
{
	// Initialisations & Setup
	init_log_system();
	log_global_on();
	log_set_global_max_output_level(VERBOSE_DEBUG);
	init_bme280();

	// Superloop
	while (1)
	{
		temperature = bme280_get_temperature();
		humidity = bme280_get_humidity();

		log_message_with_16bit_unsigned_dec_val(&log_system_main,
												INFO,
												"Temperature: ",
												temperature);

		log_message_with_16bit_unsigned_dec_val(&log_system_main,
												INFO,
												"Humidity: ",
												humidity);
		_delay_ms(1000);
	}

	return 0;
}