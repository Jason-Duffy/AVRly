/******************************************************************************
 @copyright Copyright © 2022 by Jason Duffy
 
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
 * @file digital_clock.c
 * @ingroup digital_clock
 * @author Jason Duffy
 * @date 2nd April 2022
 * @brief Driver to provide setup and configuration of the timer/counter
 * hardware on the ATmega328P.
 * @details
 * @bug No known bugs. 
 * @see
 */

#include <avr/interrupt.h>

#include "digital_clock.h"

#define PRESCALER           64
#define UNITS_PER_SECOND    1000

/**
 * File scope variables for digital clock functionality.
 * Must be declared volatile if used in ISR. 
 */
static volatile uint16_t milliseconds = 0;
static volatile uint8_t seconds = 0;
static volatile uint8_t minutes = 31;
static volatile uint8_t hours = 22;

static char msg[9] = {0};


/**
 * Interrupt Service Routine. 
 */
ISR(TIMER0_COMPA_vect)
{
    if (milliseconds < 999)
    {
        ++milliseconds;
    }
    else
    {
        milliseconds = 0;

        if (seconds < 59)
        {
            ++seconds;
        }
        else
        {
            seconds = 0;

            if (minutes < 59)
            {
                ++minutes;
            }
            else
            {
                minutes = 0;

                if (hours < 23)
                {
                    ++hours;
                }
                else
                {
                    hours = 0;
                }
            }
        }
    }
}

/*
 * Initialisation routine for 8-bit timer 0.
 */
void init_timer_counter_0(void)
{
    /*
    cli();
    OCR0A = 125; // Set initial compare value A.

    TCCR0A |= (1 << WGM01); // CTC mode, OCR0A is TOP
    TCCR0B |= (1 << CS00) | (1 << CS01); // start timer with 64 prescaler
    TIMSK0 |= (1 << OCIE0A); // enable output compare interrupt for OCR4A
    sei();
    */

    cli();
    OCR0A = (F_CPU / PRESCALER / UNITS_PER_SECOND);
    TCCR0A |= (1 << WGM01); // CTC mode, OCR0A is TOP
    TCCR0B |= (1 << CS00) | (1 << CS01); // start timer with 64 prescaler
    TIMSK0 |= (1 << OCIE0A); // enable output compare interrupt for OCR4A
    sei();

}


/*
 * Setter function for time variables. 
 */
void set_time(uint8_t hrs, uint8_t mins, uint8_t secs)
{
    cli();
    hours = hrs;
    minutes = mins;
    seconds = secs;
    sei();
}


/*
 * Getter function for time variables.
 * Returns current time as a string eg. 22:03:11
 */
char* get_time(void)
{
    // Store hours as a string.
    msg[0] = '0' + (hours / 10); // 10's
    msg[1] = '0' + (hours % 10); // 1's 

    msg[2] = ':';

    // Store minutes as a string.
    msg[3] = '0' + (minutes / 10); // 10's
    msg[4] = '0' + (minutes % 10); // 1's

    msg[5] = ':';

    // Store seconds as a string.
    msg[6] = '0' + (seconds / 10); // 10's
    msg[7] = '0' + (seconds % 10); // 1's

    return msg;
}


/*** end of file ***/
