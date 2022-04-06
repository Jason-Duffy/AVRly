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
 * @file digital_clock.h
 * @ingroup digital_clock
 * @author Jason Duffy
 * @date 2nd April 2022
 * @brief Driver to provide setup and configuration of the timer/counter
 * hardware on the ATmega328P.
 * @details
 * @bug No known bugs. 
 * @see
 */

#ifndef DIGITAL_CLOCK_DOT_H
#define DIGITAL_CLOCK_DOT_H

#include <stdint.h>


/**
 * Initialisation routine for 8-bit timer 0.
 */
void init_timer_counter_0(void);

/**
 * Setter function for time variables. 
 */
void set_time(uint8_t hours, uint8_t mins, uint8_t secs);

/**
 * Getter function for time variables.
 * Returns current time as a string eg. 22:03:11
 */
char* get_time(void);



#endif // DIGITAL_CLOCK_DOT_H


/*** end of file ***/
