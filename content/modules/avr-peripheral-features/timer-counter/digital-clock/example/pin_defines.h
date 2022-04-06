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
 * @ingroup digital_clock
 * @author Jason Duffy
 * @date 2nd April 2022
 * @brief Definitions for pins and ports.
 */

#ifndef PIN_DEFINES_DOT_H
#define PIN_DEFINES_DOT_H

// LCD ports, pins & data direction registers
#define LCD_DATA_PORT          PORTB
#define LCD_DATA_DDR           DDRB
#define LCD_DATA_PIN           PINB
#define LCD_CTRL_PORT          PORTB
#define LCD_CTRL_DDR           DDRB

// LCD pinout
#define LCD_RS                 PB0
#define LCD_EN                 PB1

#define LCD_D7                 PB7
#define LCD_D6                 PB6
#define LCD_D5                 PB5
#define LCD_D4                 PB4


#endif //PIN_DEFINES_DOT_H

/*** end of file ***/