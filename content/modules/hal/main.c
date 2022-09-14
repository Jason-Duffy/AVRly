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
 * @file scale.c
 * @ingroup hal
 * @author Jason Duffy
 * @date 13th September 2022
 * @brief 
 */

#define LED_DDR     DDRB
#define LED_PORT    PORTB
#define LED         PB0


#include <util/delay.h>
#include "hal.h"

int main()
{
    hal_gpio_set_data_direction(&LED_DDR, LED, INPUT);
    while (1)
    {
        hal_gpio_set_level(&LED_PORT, LED, HIGH);
        _delay_ms(500);
        hal_gpio_set_level(&LED_PORT, LED, LOW);
        _delay_ms(500);
    }
    return 0;
}