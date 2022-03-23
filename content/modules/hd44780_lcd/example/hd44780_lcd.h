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
 * @file hd44780_lcd.h
 * \ingroup hd44780_lcd
 * @author Jason Duffy
 * @date 1st March 2022
 * @brief Driver for the HD44780 based 16x2 liquid crystal display.
 * @bug No known bugs. 
 * 
 * This file provides the basic low-level functionality for the ubiquitous 16x2
 * display. Please note that it uses long blocking waits in the initialisation
 * routine (100ms), and short blocking waits in other utility functions
 * (2uS - 2mS). This was done to simplify the code as the busy flag read
 * introduced pitfalls. This driver currently only allows for a single display
 * to be used, but this might be improved on at a later date.
 * 
 * This driver was written using the datasheet for the HITACHI HD44780U LCD
 * driver chip, which can be found at the link below.
 * @see http://www.datasheet-pdf.com/PDF/HD44780U-Datasheet-Hitachi-1109874
 */

#ifndef HD_FOUR_FOUR_SEVEN_EIGHT_ZERO_LCD_DOT_H
#define HD_FOUR_FOUR_SEVEN_EIGHT_ZERO_LCD_DOT_H

#include <stdint.h>
#include <stdbool.h>


/** 
 * Configuration struct, to be instantiated and values assigned before passing
 * it's address into and calling lcd_init().
 * NOTE: 5x10 font cannot be used in conjunction with 2 line display. 4 bit
 * mode takes at least twice as long as 8 bit mode to send each character, but
 * frees up some GPIO pins. 
 */
typedef struct
{
  bool eight_bit_mode;    ///< true = 8 bit mode, false = 4 bit mode.
  bool two_line_display;  ///< true = 2 lines, false = 1 line.
  bool five_by_ten_font;  ///< true = 5x10 dots, false = 5x8 dots.
  bool increment_counter; ///< true = increment, false = decrement.
  bool display_shift;     ///< true = display shift, false = cursor shift.
  bool cursor_enable;     ///< true = enabled, false = disabled.
  bool blink_enable;      ///< true = enabled, false = disabled.
} lcd_config_t;


/**
 * Initialisation routine (run once at startup).
 * This function is to be called immediately after powerup of the display
 * module. Instantiate the lcd_config_t object first then pass it's address
 * into init_lcd() before using any other lcd functions.
 * @param p_config is a pointer to the lcd_config_t object.
 * @return Returns void.
 */
void init_lcd(lcd_config_t *p_config);


/**
 * Turn display off (config settings are retained). Side effect: cursor_enable
 * and blink_enable variable states are written to the display during this
 * command, so if they have been changed but lcd_reconfigure() was not called
 * afterwards, this function will update those config bits on the display.
 * @return Returns void.
 */
void lcd_display_off(void);


/**
 * Turn display on. Side effect: cursor_enable and blink_enable variable states
 * are written to the display during this command, so if they have been changed
 * but lcd_reconfigure() was not called afterwards, this function will update
 * those config bits on the display. 
 * @return Returns void.
 */
void lcd_display_on(void);


/**
 * Prints a string of characters to the display. This function takes a string
 * literal (constant) as it's parameter. Be sure to enclose text passed in with
 * "" quotation marks. eg: "Hello, World!".
 * @param str is a string literal.
 * @return Returns void.
 */
void lcd_print_string(const char *str);


/**
 * Prints an integer variable. This function prints a signed integer value to
 * the display, values from -32768 to 32767 are acceptable.
 * @param number is a signed, fixed width integer.
 * @return Returns void.
 */
void lcd_print_integer(int16_t number);


/**
 * Sets cursor location using x and y coordinates.
 * Column is 0 for top row, 1 for bottom row (in 2 row mode). Row can be from
 * 0 - 15, values outside of this range will be written to non visible spaces
 * on the display.
 * @param column is the x coordinate.
 * @param row is the y coordinate.
 * @return Returns void.
 */
void lcd_set_cursor(uint8_t column, uint8_t row);


/**
 * Writes space characters to all 32 sections of display (or 16 if in 1 line
 * mode). This is much faster than the clear_display command, as that works by
 * writing a space character to every single section of the display, even all
 * the non-visible ones.
 * @return Returns void.
 */
void lcd_fast_clear(void);


/**
 * Edits config settings on the display (lcd_config_t members must be changed
 * first). data_length, display_lines, and font_size cannot be changed after
 * init_lcd() is called.
 * @return Returns void.
 */
void lcd_reconfigure(void);


/**
 * Sets DDRAM address 0 in address counter. Also returns display from being
 * shifted to original position. DDRAM contents remain unchanged.
 * @return Returns void.
 */
void lcd_return_home(void);


/**
 * Moves cursor left without changing DDRAM contents.
 * @param distance is used to specify how many spaces to move.
 * @return Returns void.
 */
void lcd_shift_cursor_left(uint8_t distance);


/**
 * Moves cursor right without changing DDRAM contents.
 * @param distance is used to specify how many spaces to move.
 * @return Returns void.
 */
void lcd_shift_cursor_right(uint8_t distance);


/**
 * Shifts display left without changing DDRAM contents. Optional delay between
 * shifts for scrolling effect.
 * @param distance is used to specify how many spaces to move.
 * @param delay - pass in true for scrolling effect, false for no delay.
 * @return Returns void.
 */
void lcd_shift_display_left(uint8_t distance, bool delay);


/**
 * Shifts display right without changing DDRAM contents. Optional delay between
 * shifts for scrolling effect.
 * @param distance is used to specify how many spaces to move.
 * @param delay - pass in true for scrolling effect, false for no delay.
 * @return Returns void.
 */
void lcd_shift_display_right(uint8_t distance, bool delay);


#endif // HD_FOUR_FOUR_SEVEN_EIGHT_ZERO_LCD_DOT_H


/*** end of file ***/
