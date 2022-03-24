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
 * @ingroup getting-started
 * @author Jason Duffy
 * @date 15th March 2022
 * @brief Main routine for the Blink example application in Getting Started.
 * This example application is intended to verify the configuration steps for
 * the MCU have been performed correctly and everything is working as it
 * should. The LED should turn on for 1 second, then turn off for 1 second, and
 * repeat. This file also serves to demonstrate the anatomy of embedded
 * firmware. 
 * @bug No known bugs. 
 * 
 */

// Include the header from our blink module.
#include "blink.h"


/**
 * Main routine to be executed on the MCU.
 */
int main()
{
    init_led(); // Call function to initialise LED for use.

    while (1) // Loop forever
    {
        blink_led();
    }

    return 0; // This line is never reached. 
}


/*** end of file ***/
