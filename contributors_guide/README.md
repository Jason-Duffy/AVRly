# Contributor's Guide

## A Word on Doxygen
Throughout this repository, the code has been documented using [Doxygen](https://www.doxygen.nl/index.html). It's an easy way to generate documentation which stays close to the code so it's not too difficult to keep the two in line. 

## Anatomy of Embedded Firmware

### Licence
At the top of each file, a copyright notice and licence terms are added. This let's other users know whether they can use and distribute this software, and the terms under which they may do so. The software in this repository is released under the MIT licence. 

```C
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
```
The licence and copyright notice are enclosed in a Javadoc style banner, which Doxygen will recognise as a banner comment. To use this stye of banner, `JAVADOC_BANNER = YES` must be set in the Doxyfile. Add your name in the copyright notice. 


### C Header File
A C header file should be named after the function of the file or the peripheral that it serves, and the file extension is `.h`. The filename should be entirely in lowercase. An example can be found [here][Header_File_Example_URL].

After the license, place a Javadoc style comment block with some special Doxygen commands: `@file`, `@author`, `@date`, `@brief`, `@bug` and `@see`. 

```C
/**
 * @file filename.h
 * @author Your Name Here.
 * @date 15th March 2022
 * @brief The brief description goes here. After the first full stop, this text
 * becomes the detailed description. Add an explanation of the purpose and
 * limitations of the module, along with any other notes that may be useful to
 * others using it. In the Doxyfile, ensure JAVADOC_BANNER = YES, and
 * JAVADOC_AUTOBRIEF = YES, to use this style of commenting. 
 * @bug Known bugs are declared and described here.
 * @see "See also" links go here https://www.doxygen.nl/manual/docblocks.html
 */
```

 Next come the include guards - a preprocessor mechanism used to prevent the header file contents being included in other files multiple times. 

```C
#ifndef FILENAME_DOT_H
#define FILENAME_DOT_H

// Contents of header file go here. 

#endif // FILENAME_DOT_H
```

`#include` directives come next, with standard library headers listed first, then the local, project specific headers. 

```C
// Header file needed for fixed width integer types. 
#include <stdint.h>
```

Typedefs, enums etc come next, along with any macro definitions. 

Function prototypes/declarations are now listed, with the initialisation function first. 

```C
/**
 * Public initialisation function declaration comes first.
 */
void init_object(uint16_t value);


/**
 * Other public function declarations come afterwards.
 */
uint16_t get_value(void);
```

The file ends with closure of the header guards, two blank lines and an `/*** end of file ***/` comment followed by a blank line. 

```C
// End of include guard.
#endif // FILENAME_DOT_H


/*** end of file ***/

```



[Header_File_Example_URL]: 