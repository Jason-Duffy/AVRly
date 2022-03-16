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
 * @file pin_defines.h
 * @author Jason Duffy
 * @date 15th March 2022
 * @brief Pin and port definitions for Getting Started with Blink. This file
 * also serves to demonstrate the anatomy of embedded firmware. 
 */

#ifndef PIN_DEFINES_DOT_H
#define PIN_DEFINES_DOT_H

// Definitions for pins and ports are in this header file.
#include <avr/io.h>


/**
 * Defines the AVR port we have wired our LED to.
 */
#define LED_PORT        PORTB

/**
 * Defines the Data Direction Register for the GPIO connected to our LED.
 */
#define LED_DDR         DDRB

/**
 * Defines the GPIO number the LED is wired to
 */
#define LED_GPIO        PB0


#endif //PIN_DEFINES_DOT_H


/*** end of file ***/
