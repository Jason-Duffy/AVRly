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
 * @file hal.h
 * @ingroup hal
 * @author Jason Duffy
 * @date 13th September 2022
 * @brief 
 */

#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>


#ifndef HAL_DOT_H
#define HAL_DOT_H

#define OUTPUT      true
#define INPUT       false

#define HIGH        true
#define LOW         false


void hal_gpio_set_data_direction(volatile uint8_t* mem_addr, uint8_t pin, bool is_output);

void hal_gpio_set_level(volatile uint8_t* mem_addr, uint8_t pin, bool is_high);


#endif // HAL_DOT_H