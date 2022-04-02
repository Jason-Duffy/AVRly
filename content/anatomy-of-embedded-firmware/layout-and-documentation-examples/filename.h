/******************************************************************************
 @copyright Copyright © 2022 by Your Name Here.
 
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
 * @file filename.h
 * @ingroup anatomy
 * @author Your Name Here.
 * @date 15th March 2022
 * @brief The brief description goes here, keep it relatively short and to the
 * point.
 * @details After the brief comes the detailed description. Add an explanation
 * of the purpose and limitations of the module, along with any other notes
 * that may be useful to others using it.
 * @bug Known bugs are declared and described here.
 * @see "See also" links go here https://www.doxygen.nl/manual/docblocks.html
 */


// Include guards are used to ensure each header is only included once. 
#ifndef FILENAME_DOT_H
#define FILENAME_DOT_H

// Header file needed for fixed width integer types. 
#include <stdint.h>

/**
 * This is a Javadoc autobrief style comment. After the first full stop the text
 * becomes a detailed description. Explain how to use the function here.
 * Initialisation function names should start with 'init' and appear first.
 * @param List the parameters here. 
 * @return Declare the return type here (not needed for void return type).
 */
void init_object(uint16_t value);


/**
 * Other public function declarations come afterwards.
 * @return Returns a 16 bit unsigned integer. Returns are documented like this.
 */
uint16_t get_value(void);


// End of include guard.
#endif // FILENAME_DOT_H


/*** end of file ***/
