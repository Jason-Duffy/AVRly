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
 * \defgroup anatomy Anatomy of Embedded Firmware
 */

/**
 * @file filename.c
 * \ingroup anatomy
 * @author Your Name Here.
 * @date 15th March 2022
 * @brief The brief description goes here, keep it relatively short and to the
 * point. 
 * 
 * After the brief, this text becomes the detailed description. Add an
 * explanation of the purpose and limitations of the module, along with any
 * other notes that may be useful to others using it.
 * @bug Known bugs are declared and described here.
 * @see "See also" links go here https://www.doxygen.nl/manual/docblocks.html
 */


// Standard library header files are declared first, with angular brackets. 
#include <stdint.h>

// System header files are declared next, also with angular brackets.
// Define the path to search for these files in the Makefile. 
#include <util/delay.h>

// Project specific includes come next, in quotation marks.
// These files are located in the project directory. 
#include "pin_defines.h"

// Include the header file for this module, with the same name but .h
#include "filename.h"

/**
 * Next come #define statements/macros. Append integer values with a 'U' to 
 * make them unsigned, as the default type is signed integer. 
 */
#define DECIMAL_MACRO     855U


/**
 * Try to keep the scope of variables limited to the file at least, though
 * function level scope is usually better where possible. 
 */
static uint16_t file_scope_variable = 0;


// Private helper function declarations go here.
void do_some_helpful_stuff(void);


/**
 * This is a Javadoc style comment. Again, after the first full stop the text
 * becomes a detailed description. Explain how to use the function here.
 * Initialisation function names should start with 'init' and appear first.
 * @param List the parameters here. 
 * @return Declare the return type here (not needed for void return type).
 */
void init_object(uint16_t value)
{
    OBJECT_DDR |= (1 << OBJECT_GPIO); // Set object gpio as output. 

    OBJECT_PORT |= (1 << OBJECT_GPIO); // Set level of OBJECT_GPIO high.

    // Do some other stuff with the parameters
}


/**
 * Get value and return it without exposing a private variable. 
 */
uint16_t get_value(void)
{
    return file_scope_variable;
}


/**
 * Helper function definitions come last, though their declarations are at the
 * top of the file. 
 */
void do_some_helpful_stuff(void)
{
    // Body of function definition goes here. 
}


/*** end of file ***/
