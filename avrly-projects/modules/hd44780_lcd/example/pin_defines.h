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
 * \ingroup hd44780_lcd
 * @author Jason Duffy
 * @date 1st March 2022
 * @brief Definitions for pin mapping (for hd44780_lcd)
 * @bug No known bugs. 
 * 
 * This file provides definitions for pin/port references used in the hd44780
 * driver. If you are using it in 8 bit mode, you need to wire all 8 data pins
 * D0 - D7 to pins Px0 - Px7 of a single port, and define that port as
 * LCD_DATA_PORT. You do not need to define LCD_D0 - LCD_D3 in this file though
 * as they are not referred to by pin in the code, only by whole port. 
 * 
 * If you are using the display in 4 bit mode, you can wire the 4 data pins
 * D4 - D7 to any 4 pins on the port you defined as LCD_DATA_PORT, just make
 * sure they are in the correct order (you cannot wire them as D7, D5, D6, D4
 * for instance). The LCD_CTRL_PORT can either be a separate port, or it can
 * be on the same port as the data pins (this only applies in 4 bit mode). 
 * 
 * If you'd like to expand this project, you need to keep just one
 * pin_defines.h file per project. All pins and ports can be defined here, then
 * just #include "pin_defines.h" in any file that uses these definitions.
 * Remember to prefix your pin/port names with the name of the module or device
 * they belong to. 
 */

#ifndef PIN_DEFINES_DOT_H
#define PIN_DEFINES_DOT_H

// LCD ports, pins & data direction registers
#define LCD_DATA_PORT          PORTB
#define LCD_DATA_DDR           DDRB
#define LCD_DATA_PIN           PINB
#define LCD_CTRL_PORT          PORTA
#define LCD_CTRL_DDR           DDRA

// LCD pinout
#define LCD_RS                 PA0
#define LCD_EN                 PA2

#define LCD_D7                 PB7
#define LCD_D6                 PB6
#define LCD_D5                 PB5
#define LCD_D4                 PB4


#endif //PIN_DEFINES_DOT_H

/*** end of file ***/