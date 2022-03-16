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
 * @file blink.h
 * @author Jason Duffy
 * @date 15th March 2022
 * @brief Driver for example application from Getting Started with Blink.
 * This file also serves to demonstrate the anatomy of embedded firmware. 
 * @bug No known bugs.
 */

#ifndef BLINK_DOT_H
#define BLINK_DOT_H


/**
 * Call this function once on entry of main() routine to configure settings and
 * initialise the LED for use. 
 */
void init_led(void);


/**
 * Call this function in the loop of the main() routine to blink the LED. 
 */
void blink_led(void);

#endif // BLINK_DOT_H


/*** end of file ***/
