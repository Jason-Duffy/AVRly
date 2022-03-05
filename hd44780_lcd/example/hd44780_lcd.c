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
 * @file hd44780_lcd.c
 * @author Jason Duffy
 * @date 1st March 2022
 * @brief Driver for the HD44780 based 16x2 liquid crystal display.
 * @bug No known bugs. 
 * 
 * This file provides the basic low-level functionality for the ubiquitous 16x2
 * display. Please note that it uses long blocking waits in the initialisation
 * routine (100ms), and short blockign waits in other utility functions
 * (2uS - 2mS). This was done to simplify the code as the busy flag read
 * introduced pitfalls. This driver currently only allows for a single display
 * to be used, but this might be improved on at a later date.
 * 
 * NOTE: Values used in bitwise operations MUST be of unsigned type.
 * 
 * This driver was written using the datasheet for the HITACHI HD44780U LCD
 * driver chip, which can be found here:
 * @see http://www.datasheet-pdf.com/PDF/HD44780U-Datasheet-Hitachi-1109874
 */

// System utility headers. These are installed along with AVR Crosspack.
#include <avr/io.h>
#include <util/delay.h>

//Project specific headers.
#include "hd44780_lcd.h"
#include "pin_defines.h" // Pinout for the display is defined here.

/**
 * Local copy of lcd_config_t pointer to store address of config object.
 */
static lcd_config_t *p_config_local;

/**
 * Bitmask used to manipulate data based on data length setting in config.
 */
static uint8_t data_length_bitmask = 0;

// Base commands without flags applied.
#define CLEAR_DISPLAY				0b00000001U
#define CURSOR_HOME					0b00000010U
#define ENTRY_MODE_SET				0b00000100U
#define ON_OFF_CTRL					0b00001000U
#define CURSOR_DISPLAY_SHIFT		0b00010000U
#define FUNCTION_SET				0b00100000U

// Bit positions for setting flags in base commands.
#define DATA_LENGTH_BIT				4U
#define DISPLAY_LINES_BIT			3U
#define FONT_SIZE_BIT				2U
#define MOVE_DIRECTION_BIT			1U
#define DISPLAY_SHIFT_BIT			0U
#define CURSOR_ENABLE_BIT			1U
#define BLINK_ENABLE_BIT			0U
#define ON_OFF_CTRL_BIT 			2U
#define RIGHT_LEFT_BIT				2U
#define SHIFT_OR_CURSOR_BIT			3U
#define BUSY_FLAG_BIT				7U // Not currently used in this program.

// Flags for setting ON_OFF_CTRL_BIT.
#define DISPLAY_ON 					true
#define DISPLAY_OFF 				false

// Delay time definitions.
#define POWER_RAMP_DELAY_MS			100
#define SHORT_INSTR_DELAY_MS		2
#define LONG_INSTR_DELAY_MS			10
#define SCROLL_DELAY_MS				400
#define ENABLE_DELAY_US				2

// Forward declarations
void lcd_command(uint8_t data);
void lcd_char(char character);
void pulse_enable(void);


/*
 * Initialisation routine (run once at startup).
 */
void init_lcd(lcd_config_t *p_config)
{
	// copy address of config object pointer to a local pointer
	p_config_local = p_config;

	// Set data direction registers to output where applicable
	LCD_CTRL_DDR |= (1U << LCD_RS) | (1U << LCD_EN);

	// Test for bit mode and set appropriate bitmask
	if (p_config_local->eight_bit_mode)
	{
		data_length_bitmask = 0xff; // 0b11111111
	}
	else
	{
		data_length_bitmask |= (1U << LCD_D7) | (1U << LCD_D6);
		data_length_bitmask |= (1U << LCD_D5) | (1U << LCD_D4);
	}

	// Set relevant lcd data port direction to output
	LCD_DATA_DDR |= data_length_bitmask;

	// Delay to allow power ramp up in LCD controller
	_delay_ms(POWER_RAMP_DELAY_MS);

	// Begin initialising HD44780
	uint8_t byte = 0;
	byte |= FUNCTION_SET;
	byte |= (p_config_local->eight_bit_mode << DATA_LENGTH_BIT);

	for (uint8_t count = 0; count < 3; ++count)
	{
		lcd_command(byte);
		_delay_ms(LONG_INSTR_DELAY_MS);
	}

	byte = 0;
	byte |= FUNCTION_SET;
	byte |= (p_config_local->eight_bit_mode << DATA_LENGTH_BIT);
	byte |= (p_config_local->two_line_display << DISPLAY_LINES_BIT);
	byte |= (p_config_local->five_by_ten_font << FONT_SIZE_BIT);
	lcd_command(byte);

	byte = 0;
	byte |= ON_OFF_CTRL;
	byte |= (DISPLAY_OFF << ON_OFF_CTRL_BIT);
	byte |= (p_config_local->cursor_enable << CURSOR_ENABLE_BIT);
	byte |= (p_config_local->blink_enable << BLINK_ENABLE_BIT);
	lcd_command(byte);

	byte = 0;
	byte |= CLEAR_DISPLAY;
	lcd_command(byte);

	byte = 0;
	byte |= ENTRY_MODE_SET;
	byte |= (p_config_local->increment_counter << MOVE_DIRECTION_BIT);
	byte |= (p_config_local->display_shift << DISPLAY_SHIFT_BIT);
	lcd_command(byte);

	byte = 0;
	byte |= ON_OFF_CTRL;
	byte |= (DISPLAY_ON << ON_OFF_CTRL_BIT);
	byte |= (p_config_local->cursor_enable << CURSOR_ENABLE_BIT);
	byte |= (p_config_local->blink_enable << BLINK_ENABLE_BIT);
	lcd_command(byte);
	lcd_return_home();
}


/*
 * Turn display off (config settings are retained).
 */
void lcd_display_off(void)
{
	uint8_t byte = 0;
	byte |= ON_OFF_CTRL; // Default is off
	byte |= (p_config_local->cursor_enable << CURSOR_ENABLE_BIT);
	byte |= (p_config_local->blink_enable << BLINK_ENABLE_BIT);
	lcd_command(byte);
}


/*
 * Turn display on.
 */
void lcd_display_on(void)
{
	uint8_t byte = 0;
	byte |= ON_OFF_CTRL;
	byte |= (DISPLAY_ON << ON_OFF_CTRL_BIT);
	byte |= (p_config_local->cursor_enable << CURSOR_ENABLE_BIT);
	byte |= (p_config_local->blink_enable << BLINK_ENABLE_BIT);
	lcd_command(byte);
}


/*
 * Prints a string of characters to the display.
 */
void lcd_print_string(const char *str)
{
	for (uint8_t index = 0; str[index] != 0; ++index)
	{
		lcd_char(str[index]);
	}
}


/*
 * Prints an integer variable.
 */
void lcd_print_integer(int16_t number)
{
	if (number < 0)
	{
		lcd_char('-');
	}

	uint8_t count = 0;
	uint8_t digit = 0;
	char str[20];

	while (number > 0)
	{
		digit = number % 10;
		str[count] = (digit + '0');
		++count;
		number /= 10;
	}

	while (count > 0)
	{
		lcd_char(str[count - 1]);
		--count;
	}
}


/*
 * Sets cursor location using x and y coordinates.
 */ 
void lcd_set_cursor(uint8_t column, uint8_t row)
{
	uint8_t address = 0;

	if (row == 0)
	{
		address = column;
	}

	else if (row == 1)
	{
		address = (column + 64);
	}

	address |= 0x80U; // Write 1 to MSB
	lcd_command(address);
}


/*
 * Writes space characters to all 32 sections of display (or 16 if in 1 line
 * mode).
 */
void lcd_fast_clear(void)
{
	lcd_set_cursor(0,0);
	for (uint8_t count = 0; count < 16; ++count)
	{
		lcd_char(' ');
	}
	
	if (p_config_local->two_line_display)
	{
		lcd_set_cursor(0,1);
		for (uint8_t count = 0; count < 16; ++count)
		{
			lcd_char(' ');
		}
	}
}


/*
 * Edits config settings for lcd (lcd_config_t members must be changed first).
 */
void lcd_reconfigure(void)
{
	uint8_t byte = 0;
	byte |= ENTRY_MODE_SET;
	byte |= (p_config_local->increment_counter << MOVE_DIRECTION_BIT);
	byte |= (p_config_local->display_shift << DISPLAY_SHIFT_BIT);
	lcd_command(byte);

	// Also resends cursor and blink settings
	lcd_display_on();
}


/*
 * Sets DDRAM address 0 in address counter. Also returns display from being
 * shifted to original position. DDRAM contents remain unchanged.
 */
void lcd_return_home(void)
{
	lcd_command(CURSOR_HOME);
	_delay_ms(SHORT_INSTR_DELAY_MS);
}


/*
 * Moves cursor left without changing DDRAM contents.
 */
void lcd_shift_cursor_left(uint8_t distance)
{
	uint8_t byte = 0;
	byte |= CURSOR_DISPLAY_SHIFT;

	for (uint8_t count = 0; count < distance; ++count)
	{
		lcd_command(byte);
	}
}


/*
 * Moves cursor right without changing DDRAM contents.
 */
void lcd_shift_cursor_right(uint8_t distance)
{
	uint8_t byte = 0;
	byte |= CURSOR_DISPLAY_SHIFT;
	byte |= (1U << RIGHT_LEFT_BIT);

	for (uint8_t count = 0; count < distance; ++count)
	{
		lcd_command(byte);
	}
}


/*
 * Shifts display left without changing DDRAM contents.
 */
void lcd_shift_display_left(uint8_t distance, bool delay)
{
	uint8_t byte = 0U;
	byte |= CURSOR_DISPLAY_SHIFT;
	byte |= (1U << SHIFT_OR_CURSOR_BIT);

	for (uint8_t count = 0; count < distance; ++count)
	{
		lcd_command(byte);
		if (delay == true)
		{
			_delay_ms(SCROLL_DELAY_MS);
		}
	}
}


/*
 * Shifts display right without changing DDRAM contents.
 */
void lcd_shift_display_right(uint8_t distance, bool delay)
{
	uint8_t byte = 0;
	byte |= CURSOR_DISPLAY_SHIFT;
	byte |= (1U << SHIFT_OR_CURSOR_BIT);
	byte |= (1U << RIGHT_LEFT_BIT);

	for (uint8_t count = 0; count < distance; ++count)
	{
		lcd_command(byte);
		if (delay == true)
		{
			_delay_ms(SCROLL_DELAY_MS);
		}
	}
}

//===========================================================================//
//---------------------------------------------------------------------------//
//                         Private utility functions 												 //
//---------------------------------------------------------------------------//
//===========================================================================//

/*
 * Sends a command to the display.
 */
void lcd_command(uint8_t data)
{
	LCD_CTRL_PORT &= ~(1U << LCD_RS);

	if (p_config_local->eight_bit_mode)
	{
		LCD_DATA_PORT = data;
		pulse_enable();
	}
	else
	{
		uint8_t byte = 0;

 		LCD_DATA_PORT &= ~(data_length_bitmask); // Clear relevant bits in port
 		byte = (data & 0b11110000); // Keep high 4 bits only
 		byte = (byte >> (7U - LCD_D7)); // Shift nibble into place
 		LCD_DATA_PORT |= byte; // Send first nibble to LCD
 		pulse_enable();
		
 		LCD_DATA_PORT &= ~(data_length_bitmask); // Clear relevant bits in port
 		byte = (data & 0b00001111); // Keep low 4 bits only
 		byte = (byte << (LCD_D7 - 3U)); // Shift nibble into place
 		LCD_DATA_PORT |= byte; // Send second nibble to LCD
 		pulse_enable();
	}
	_delay_ms(SHORT_INSTR_DELAY_MS);
}


/*
 * Writes a single character to LCD.
 */
void lcd_char(char character)
{
	LCD_CTRL_PORT |= (1U << LCD_RS);

	if (p_config_local->eight_bit_mode)
	{
		LCD_DATA_PORT = character;
		pulse_enable();
	}
	else
	{
		uint8_t byte = 0;

 		LCD_DATA_PORT &= ~(data_length_bitmask); // Clear relevant bits in port
 		byte = (character & 0b11110000); // Keep high 4 bits only
 		byte = (byte >> (7U - LCD_D7)); // Shift nibble into place
 		LCD_DATA_PORT |= byte; // Send first nibble to LCD
 		pulse_enable();
		
 		LCD_DATA_PORT &= ~(data_length_bitmask); // Clear relevant bits in port
 		byte = (character & 0b00001111); // Keep low 4 bits only
 		byte = (byte << (LCD_D7 - 3U)); // Shift nibble into place
 		LCD_DATA_PORT |= byte; // Send second nibble to LCD
 		pulse_enable();
	}
	_delay_ms(SHORT_INSTR_DELAY_MS);
}


/*
 * Pulse enable pin to latch data into register.
 */
void pulse_enable(void)
{
	LCD_CTRL_PORT |= (1U << LCD_EN);
	_delay_us(ENABLE_DELAY_US);
	LCD_CTRL_PORT &= ~(1U << LCD_EN);
	_delay_us(ENABLE_DELAY_US);
}

/*** end of file ***/
