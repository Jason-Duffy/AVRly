# Anatomy of Embedded Firmware

## A Word on Doxygen
Throughout this repository, the code has been documented using [Doxygen](https://www.doxygen.nl/index.html). It's an easy way to generate documentation which stays closely coupled with the code so it's not too difficult to keep the two in line. The html for this site was also generated using Doxygen. It relies on special comments like this:
```C
/**
 * Comment goes here
 */
```
However, normal C style comments like:
```C
// Comment goes here
```
are ignored by Doxygen. 

## Formatting
Leave a comfortable amount of whitespace between logical sections of code, to make things easy on the eye. Header, Source and Makefiles should all be limited to 80 characters wide. 

## Licence
At the top of each file, a copyright notice and licence terms are added. This let's other users know whether they can use and distribute this software, and the terms under which they may do so. The software in this repository is released under the MIT licence. Add the year the work was produced and your name at the top. 

```C
/******************************************************************************
 @copyright Copyright © YYYY by Your Name Here.
 
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


## C Header Files
A C header file should be named after the function of the file or the peripheral that it serves. The filename should be entirely in lowercase, and the file extension is `.h`. The aim is to expose as little information as possible in the header file - just the public function declarations and any macros or typedefs etc required by other files, without them having to know too much about how it actually works.

An example file can be found in the repo [here][Header_File_Example_URL], and the Doxygen output from these special comments and commands can be found [here][Header_File_Doxygen_Output_URL]. 

After the license, place a Javadoc style comment block with some special Doxygen commands: `@file`, `@author`, `@date`, `@brief`, `@bug` and `@see`.

```C
/**
 * @file filename.h
 * @author Your Name Here.
 * @date 15th March 2022
 * @brief The brief description goes here. Add an explanation of the purpose and
 * limitations of the module, along with any other notes that may be useful to
 * others using it.
 * @bug Known bugs are declared and described here.
 * @see "See also" links go here https://www.doxygen.nl/manual/docblocks.html
 */
```

The doxygen output from these special comments looks like this:
![Doxygen Output](./images/doxygen-output.png)


Next come the include guards - a preprocessor mechanism used to prevent the header file contents being included in other files multiple times. 

```C
#ifndef FILENAME_DOT_H
#define FILENAME_DOT_H

// Contents of header file goes here. 

#endif // FILENAME_DOT_H
```

`#include` directives come next, with standard library headers listed first, then the local, project specific headers. You can think of these `#include` directives as inserting the whole contents of the header file referenced into that section of the file. 

```C
// Header file needed for fixed width integer types. 
#include <stdint.h>
```

Public typedefs, structs, enums etc come next, along with any macro definitions. 

Function prototypes/declarations are now listed, with the initialisation function first. In the Doxyfile, ensure `JAVADOC_AUTOBRIEF = YES` to use this style of commenting. 

```C
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
```

The file ends with closure of the header guards, two blank lines and an `/*** end of file ***/` comment followed by a blank line. 

```C
// End of include guard.
#endif // FILENAME_DOT_H


/*** end of file ***/

```


## C Source Files

C source files should have the same name as their respective header file (if they have one) all in lowercase, with the filename extension `.c`

The source file provides the implementation and definitions of the public functions listed in it's header file, usually along with some helper functions, structs, macros and variables private to the file. 

An example file can be found in the repo [here][Source_File_Example_URL], and the Doxygen output from these special comments and commands can be found [here][Source_File_Doxygen_Output_URL].

Begin with a licence and copyright notice as before, and then the Doxygen commands to provide some information about the file. 

```C
/**
 * @file filename.c
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

`#include` directives come next, with standard library headers listed first, then the local, project specific headers. These serve as an instruction for the preprocessor to insert the contents of the named header file in that section of the source file. 

```C
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
```

Next we have macro definitions. 

```C
/**
 * Next come #define statements/macros. Append integer values with a 'U' to 
 * make them unsigned, as the default type is signed integer. 
 */
#define DECIMAL_MACRO     855U
```

Then we have structs, enums, typedefs, and variable declarations and initialisations.  

```C
/**
 * Try to keep the scope of variables limited to the file at least, though
 * function level scope is usually better where possible. 
 */
static uint16_t file_scope_variable = 0;
```

Next in line are function prototypes/declarations for private helper functions defined at the bottom of the file. They are declared ahead of any definitions to ensure they can be referenced throughout the file.

```C
// Private helper function declarations go here.
void do_some_helpful_stuff(void);
```

Now we have the definitions for the public functions, listed in the same order as they appear in the header file, with the initialisation routine first. 
```C
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
```

Lastly, we have the definitions of private helper functions. Since they are less likely to be needed by people using the software, they are located at the bottom of the file. 

```C
/**
 * Helper function definitions come last, though their declarations are at the
 * top of the file. 
 */
void do_some_helpful_stuff(void)
{
    // Body of function definition goes here. 
}
```

The file is ended with two blank lines and an `/*** end of file ***/` comment followed by a blank line. 
```C


/*** end of file ***/

```

## pin_defines.h

Macro definitions for ports, pins, data direction registers and GPIOs should be listed in the pin_defines.h file. When you have a larger project, it's much clearer to be able to see the pinout all together in one place, rather than strewn across multiple files. 

An example file can be found in the repo [here][Pin_Defines_Example_URL], and the Doxygen output from these special comments and commands can be found [here][Pin_Defines_Doxygen_Output_URL].

Again we start with the Javadoc style Doxygen comment block to provide some info about the file.

```C
/**
 * @file pin_defines.h
 * @author Your Name Here
 * @date 15th March 2022
 * @brief Pin and port definitions for the project.
 * @see Datasheets or other links can go here. 
 */
```

Then we have our include guards, as with all .h files. 

```C
#ifndef PIN_DEFINES_DOT_H
#define PIN_DEFINES_DOT_H

// Contents of header file goes here.

#endif // PIN_DEFINES_DOT_H 
```

This header is required to access pin and port names.
```C
// Definitions for pins and ports are in this header file.
#include <avr/io.h>
```

Then we make our macro definitions for pins, ports and GPIOs - see datasheet for more on this. 
```C
/**
 * Defines the AVR port we have wired our peripheral to.
 */
#define OBJECT_PORT        PORTB

/**
 * Defines the Data Direction Register for the GPIO connected to our peripheral.
 */
#define OBJECT_DDR         DDRB

/**
 * Defines the GPIO number the peripheral is wired to
 */
#define OBJECT_GPIO        PB0
```

The file ends with closure of the header guards, two blank lines and an `/*** end of file ***/` comment followed by a blank line. 

```C
// End of include guard.
#endif // PIN_DEFINES_DOT_H 


/*** end of file ***/

```


## main.c

main.c is where the `int main()` routine lives, and is the heart of the application.

An example file can be found in the repo [here][Main_File_Example_URL], and the Doxygen output from these special comments and commands can be found [here][Main_File_Doxygen_Output_URL].

It begins, as usual with the Javadoc style Doxygen comment block to provide some info about the file. 
```C
/**
 * @file main.c
 * @author Your Name Here
 * @date 15th March 2022
 * @brief Main source file where main() routine is called.
 * @bug Known bugs are declared and described here.
 * @see links to other files or docs go here.
 */
```

Followed by `#include` directives, (standard library headers first).
```C
// Include our driver header file here. 
#include "filename.h"
```

And then macro definitions.
```C
/**
 * Avoid using magic bumbers, use defines or typedef enums instead. 
 */
#define INITIALISATION_VALUE    3000
``` 

Then we have structs, enums, typedefs, and variable declarations and initialisations. 
```C
uint16_t returned_value = 0;
```

Lastly, we have the `main()` routine. Initialisation routines are called on entry of the main routine, this is the Setup stage. Then we enter the while loop, and this runs continuously until the device is powered off or a reset condition is met. The return statement is needed for valid syntax, as the special function main() expects to return an integer value. 
```C
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
```

This application that will be run on the target MCU as a superloop.
![Superloop Diagram](./images/super-loop.jpeg)

The file is ended with two blank lines and an `/*** end of file ***/` comment followed by a blank line. 
```C


/*** end of file ***/

```

## Makefile

The Makefile contains "recipes" intended to simplify the process of building your application. With this, you only need to type `make` to compile and link your code, rather than manually listing the many options, flags, dependancies etc in the terminal each time. 

An example file can be found in the repo [here][Makefile_Example_URL]. They cannot be dosumented using Doxygen, so I prefer to use a `help` recipe instead. Type `make help` to see a list of commands available to the user. 

The Makefile must always be named "Makefile". Keep basic user defined variables at the top of the file. 

```make
##########-----------------------------------------------------------##########
##########                 Project-specific Details                  ##########
##########       Check these every time you start a new project      ##########
##########-----------------------------------------------------------##########

MCU   = atmega328p
F_CPU = 8000000UL  
BAUD  = 9600UL
## Also try BAUD = 19200 or 38400 if you're feeling lucky.

## A directory for common include files. 
LIBDIR = /usr/local/

##########-----------------------------------------------------------##########
##########                   Programmer Defaults                     ##########
##########            Set up once, then forget about it              ##########
##########          (Can override.  See bottom of file.)             ##########
##########-----------------------------------------------------------##########

PROGRAMMER_TYPE = avrisp
# extra arguments to avrdude: baud rate, chip type, -F flag, etc.
PROGRAMMER_ARGS = -b 19200 -P /dev/tty.usbmodem141201
```
If you add a new recipe for users to invoke from terminal, document it by adding it to the `help` recipe at the bottom of the Makefile.

## Templates

The repository contains [templates for each file type][Templates_URL] mentioned in this guide.



[Header_File_Example_URL]: https://github.com/Jason-Duffy/AVRly/blob/main/content/anatomy-of-embedded-firmware/layout-and-documentation-examples/filename.h

[Header_File_Doxygen_Output_URL]: https://jason-duffy.github.io/AVRly/html/filename_8h.html

[Source_File_Example_URL]: https://github.com/Jason-Duffy/AVRly/blob/main/content/anatomy-of-embedded-firmware/layout-and-documentation-examples/filename.c

[Source_File_Doxygen_Output_URL]: https://jason-duffy.github.io/AVRly/html/filename_8c.html

[Pin_Defines_Example_URL]: https://github.com/Jason-Duffy/AVRly/blob/main/content/anatomy-of-embedded-firmware/layout-and-documentation-examples/pin_defines.h

[Pin_Defines_Doxygen_Output_URL]: https://jason-duffy.github.io/AVRly/html/anatomy-of-embedded-firmware_2layout-and-documentation-examples_2pin__defines_8h.html

[Main_File_Example_URL]: https://github.com/Jason-Duffy/AVRly/blob/main/content/anatomy-of-embedded-firmware/layout-and-documentation-examples/main.c

[Main_File_Doxygen_Output_URL]: https://jason-duffy.github.io/AVRly/html/anatomy-of-embedded-firmware_2layout-and-documentation-examples_2main_8c.html

[Makefile_Example_URL]: https://github.com/Jason-Duffy/AVRly/blob/main/content/anatomy-of-embedded-firmware/layout-and-documentation-examples/Makefile

[Makefile_Template_URL]: https://github.com/Jason-Duffy/AVRly/blob/main/content/modules/templates/Makefile

[Templates_URL]: https://github.com/Jason-Duffy/AVRly/tree/main/content/modules/templates
