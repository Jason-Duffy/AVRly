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
 * @ingroup hd44780_lcd
 * @author Jason Duffy
 * @date 1st March 2022
 * @brief Example main routine demonstrating the HD44780 based 16x2 liquid
 * crystal display.
 * @bug No known bugs. 
 */

#include <util/delay.h>
#include <avr/power.h>

#include "hd44780_lcd.h"

#define MESSAGE_DELAY		2000
#define ANIMATION_DELAY		300


// Lcd configuration object
lcd_config_t lcd_config =
{
	.eight_bit_mode = false,  	// true = 8 bit mode, false = 4 bit mode
	.two_line_display = true,   // true = 2 lines, false = 1 line
  	.five_by_ten_font = false,  // true = 5x10 dots, false = 5x8 dots
  	.increment_counter = true,  // true = increment, false = decrement
  	.display_shift = false,  	// true = display shift, false = cursor shift
  	.cursor_enable = false,  	// true = enabled, false = disabled
  	.blink_enable = false,   	// true = enabled, false = disabled
};

uint8_t test_number = 34;

int main()
{
	// Setup
	init_lcd(&lcd_config);

	// Loop forever
	for(;;)
	{
		lcd_fast_clear();
		lcd_return_home();
		lcd_print_string("  HD44780  LCD  ");
		lcd_set_cursor(0,1);
		lcd_print_string("    example.    ");
		_delay_ms(MESSAGE_DELAY);

		lcd_fast_clear();
		lcd_return_home();

		lcd_config.cursor_enable = true;
		lcd_reconfigure();
		lcd_print_string("Cursor can be:");
		lcd_set_cursor(0,1);
		lcd_print_string("enabled:");
		_delay_ms(MESSAGE_DELAY);

		lcd_set_cursor(0,1);
		lcd_print_string("shifted left");
		_delay_ms(ANIMATION_DELAY);

		for (uint8_t count = 0; count < 12; ++count)
		{
			lcd_shift_cursor_left(1);
			_delay_ms(ANIMATION_DELAY);
		}
		_delay_ms(MESSAGE_DELAY);

		lcd_set_cursor(0,1);
		lcd_print_string("shifted right        ");
		lcd_set_cursor(0,1);
		_delay_ms(ANIMATION_DELAY);

		for (uint8_t count = 0; count < 12; ++count)
		{
			lcd_shift_cursor_right(1);
			_delay_ms(ANIMATION_DELAY);
		}
		_delay_ms(MESSAGE_DELAY);

		lcd_config.blink_enable = true;
		lcd_reconfigure();
		lcd_set_cursor(0,1);
		lcd_print_string("with blink:     ");
		lcd_set_cursor(11,1);
		_delay_ms(MESSAGE_DELAY);

		lcd_config.blink_enable = false;
		lcd_config.cursor_enable = false;
		lcd_reconfigure();
		lcd_set_cursor(0,1);
		lcd_print_string("  disabled:");
		_delay_ms(MESSAGE_DELAY);

		lcd_fast_clear();
		lcd_set_cursor(0,0);
		lcd_print_string("Print integer:");
		lcd_set_cursor(0,1);
		lcd_print_integer(test_number);
		_delay_ms(MESSAGE_DELAY);

		lcd_fast_clear();
		lcd_set_cursor(0,0);
		lcd_print_string("Display");
		lcd_set_cursor(0,1);
		lcd_print_string("<shift>");
		lcd_shift_display_right(9, true);
		lcd_shift_display_left(9, true);
		_delay_ms(MESSAGE_DELAY);
	}
}