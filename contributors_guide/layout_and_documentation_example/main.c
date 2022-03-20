/******************************************************************************
 Copyright (c) 2022 by Your Name Here
 
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
 * @author Your Name Here
 * @date 15th March 2022
 * @brief Main source file where main() routine is called.
 * @bug Known bugs are declared and described here.
 */

// Include our driver header file here. 
#include "filename.h"

/**
 * Avoid using magic bumbers, use defines or typedef enums instead. 
 */
#define INITIALISATION_VALUE    3000

uint16_t returned_value = 0;

/**
 * Main routine to be executed on MCU.
 */
int main()
{
    // Initialisation routines go here. 
    init_object(INITIALISATION_VALUE);

    while (1) // Loop forever
    {
        returned_value = get_value();   
    }

    return 0; // This line is never reached. 
}


/*** end of file ***/
