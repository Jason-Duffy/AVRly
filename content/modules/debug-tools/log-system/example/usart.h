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
 * @file usart.h
 * @ingroup log_system
 * @author Jason Duffy
 * @date 15th March 2022
 * @brief Driver file providing core USART communication between the target MCU
 * and your PC. This file was adapted from Elliot Williams' Github repo
 * hexagon5un (link in the see also section below).
 * NOTE: This driver does involve blocking waits, this may be improved on in a
 * later version. 
 * @bug No known bugs. 
 * @see https://github.com/hexagon5un/AVR-Programming
 */


#ifndef BAUD          // If not defined in Makefile
#define BAUD  9600    // Set a safe default baud rate
#endif

#ifndef USART_DOT_H
#define USART_DOT_H

#include <stdint.h>

// These are defined for convenience
#define   USART_HAS_DATA   bit_is_set(UCSR0A, RXC0)
#define   USART_READY      bit_is_set(UCSR0A, UDRE0)


/**
 * Takes the defined BAUD and F_CPU, calculates the bit-clock multiplier,
 * configures the hardware USART ready for use.
 */
void init_usart(void);


/**
 * Utility function to transmit a string.
 * @param my_string is the string constant youd like to print, and should be
 * enclosed in "" quotation marks. 
 */
void usart_print_string(const char my_string[]);


/**
 * Define a string variable, pass it to this function. The string will contain.
 * whatever you typed over serial.
 * @param my_string is a pointer to the first element in the character array
 * you'd like to store the received message in. 
 * @param max_length is the maximum number of characters expected.
 */
void usart_read_string(char my_string[], uint8_t max_length);


/**
 * Prints a byte out as its 3-digit ascii equivalent.
 * @param byte is the 8 bits of data to be sent, must be unsigned. 
 */
void usart_print_byte(uint8_t byte);


/**
 * Prints a byte out as its 1-digit ascii equivalent.
 * @param byte is the 8 bits of data to be sent, must be unsigned, with a
 * value of 0-9;
 */
void usart_print_decimal_digit(uint8_t byte);


/**
 * Prints a byte out as its 1-character ascii equivalent.
 * @param byte is the character to be sent.
 */
void usart_print_char(char byte);


/**
 * Prints a word (16-bits) out as its 5-digit ascii equivalent.
 * @param word is the 16 bits of data to be sent, must be unsigned.
 */
void usart_print_word(uint16_t word);


/**
 * Prints a byte out in 1s and 0s.
 * @param byte is the 8 bits of data to be sent, must be unsigned.
 */
void usart_print_binary_byte(uint8_t byte);


/**
 * Convert a nibble to a hex character.
 * @param nibble is the 4 bits of data to be sent, must be unsigned. 
 */
char usart_nibble_to_hex_character(uint8_t nibble);


/**
 * Prints a byte out in hexadecimal format.
 * @param byte is the 8 bits of data to be sent, must be unsigned. 
 */
void usart_print_hex_byte(uint8_t byte);


/**
 * Takes in up to three ascii digits, converts them to a byte when press enter.
 * @returns an unsigned 8 bit integer is returned - this is the data received. 
 */ 
uint8_t usart_get_number(void);


#endif // USART_DOT_H

/*** end of file ***/
