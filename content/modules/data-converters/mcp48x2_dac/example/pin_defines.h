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
 * @file pin_defines.h
 * @ingroup mcp48x2
 * @author Jason Duffy
 * @date 1st March 2022
 * @brief Definitions for pin mapping (for mcp4812_dac)
 * @bug No known bugs. 
 * 
 * This file provides definitions for pin/port references used in the MCP4812
 * driver. 
 * 
 * If you'd like to expand this project, you need to keep just one
 * pin_defines.h file per project. All pins and ports can be defined here, then
 * just #include "pin_defines.h" in any file that uses these definitions.
 * Remember to prefix your pin/port names with the name of the module or device
 * they belong to. 
 */

#ifndef PIN_DEFINES_DOT_H
#define PIN_DEFINES_DOT_H

#include <avr/io.h>


#define DAC_CTRL_PORT          PORTB
#define DAC_CTRL_DDR           DDRB
#define DAC_CS                 PB0
#define LDAC                   PB4

#define SPI_PORT               PORTB
#define SPI_DDR                DDRB
#define SPI_MOSI               PB2
#define SPI_MISO               PB3
#define SPI_SCK                PB1

#endif //PIN_DEFINES_DOT_H

/*** end of file ***/