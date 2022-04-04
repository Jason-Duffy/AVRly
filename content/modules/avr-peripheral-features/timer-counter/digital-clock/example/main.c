/******************************************************************************
 @copyright Copyright © 2022 by Jason Duffy
 
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
 * @ingroup digital_clock
 * @author Jason Duffy
 * @date 2nd April 2022
 * @brief
 * @bug No known bugs.
 * @see
 */

#include "digital_clock.h"
#include "hd44780_lcd.h"

#define START_HOURS     21
#define START_MINS      59
#define START_SECS      02

void print_time(void)
{
    static char *time;
    time = get_time();
    lcd_set_cursor(0,0);
    lcd_print_string("    ");
    lcd_print_string(time);
    lcd_print_string("    ");
}

lcd_config_t lcd_config = 
{
    .eight_bit_mode = false,
    .two_line_display = true,
    .five_by_ten_font = false,
    .increment_counter = true,
    .display_shift = false,
    .cursor_enable = false,
    .blink_enable = false,  
};


int main()
{
    // Initialisation routines
    init_lcd(&lcd_config);
    set_time(START_HOURS, START_MINS, START_SECS);
    init_timer_counter_0();

    while (1) // Loop forever
    {
        print_time();
    }
    return 0; // This line is never reached. 
}


/*** end of file ***/
