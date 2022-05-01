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
 * @ingroup usart
 * @author Jason Duffy
 * @date 15th March 2022
 * @brief Example main routine demonstrating the USART driver.
 * @bug No known bugs. 
 * @see
 */

#include <util/delay.h>
#include "usart.h"

#define BUFFER_SIZE     4
#define DECIMAL_NUM     255
#define SHORT_DELAY     500
#define LONG_DELAY      4000


/**
 * Character array to store the received data.
 */ 
char receive_buffer[BUFFER_SIZE];


/**
 * Main routine for the example application. 
 */
int main()
{
    // Setup and initialisation routines.
    init_usart();
    usart_print_string("USART Initialised\n\n\n");

    // Loop forever.
    while (1)
    {
        // ------- Echo demonstration. -------- // 
        usart_print_string("Type any three characters.\n");
        usart_read_string(receive_buffer, BUFFER_SIZE);
        usart_print_string("\nYou entered: ");

        for (uint8_t index = 0; index < (BUFFER_SIZE - 1); ++index)
        {
            //char data = receive_buffer[index];
            usart_print_char(receive_buffer[index]);
        }
        usart_print_string("\n\n\n");


        // -------- Data format demonstration. -------- // 
        usart_print_string("Lets start with the decimal number ");
        usart_print_byte(DECIMAL_NUM);
        _delay_ms(SHORT_DELAY);
        usart_print_string("\n");
        usart_print_string("In 8 bit binary format, that's: ");
        usart_print_binary_byte(DECIMAL_NUM);
        _delay_ms(SHORT_DELAY);
        usart_print_string("\n");
        usart_print_string("In hexadecimal format, that's: ");
        usart_print_hex_byte(DECIMAL_NUM);
        usart_print_string("\n\n\n");
        _delay_ms(LONG_DELAY);
    }

    return 0;
}


/*** end of file ***/
