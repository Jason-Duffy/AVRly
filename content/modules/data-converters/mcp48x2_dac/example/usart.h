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
 * @ingroup mcp48x2
 * @author Jason Duffy
 * @date 15th March 2022
 * @brief Driver file providing core USART communication between the target MCU
 * and your PC.
 * @bug No known bugs. 
 * @see
 */


#ifndef BAUD          // If not defined in Makefile
#define BAUD  9600    // Set a safe default baud rate
#endif

#ifndef USART_DOT_H
#define USART_DOT_H

#include <stdint.h>

//These are defined for convenience
#define   USART_HAS_DATA   bit_is_set(UCSR0A, RXC0)
#define   USART_READY      bit_is_set(UCSR0A, UDRE0)


/**
 * Takes the defined BAUD and F_CPU, calculates the bit-clock multiplier,
 * configures the hardware USART.
 */
void init_usart(void);


/**
 * Utility function to transmit an entire string from RAM.
 */
void print_string(const char myString[]);


/**
 * Define a string variable, pass it to this function. The string will contain
 * whatever you typed over serial.
 */
void read_string(char myString[], uint8_t maxLength);


/**
 * Prints a byte out as its 3-digit ascii equivalent.
 */
void print_byte(uint8_t byte);


/**
 * Prints a word (16-bits) out as its 5-digit ascii equivalent.
 */
void print_word(uint16_t word);


/**
 * Prints a byte out in 1s and 0s.
 */
void print_binary_byte(uint8_t byte);


// !!
// TODO: find implementation for this and define difference to function below
// !!
/**
 * Convert nibble to hex.
 */
char nibble_to_hex(uint8_t nibble);


/**
 * Convert nibble to hex character.
 */
char nibble_to_hex_character(uint8_t nibble);


/**
 * Prints a byte out in hexadecimal.
 */
void print_hex_byte(uint8_t byte);


/**
 * Takes in up to three ascii digits, converts them to a byte when press enter.
 */ 
uint8_t get_number(void);


#endif // USART_DOT_H

/*** end of file ***/
