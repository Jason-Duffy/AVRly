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
 * @file am_radio.c
 * @ingroup am_radio
 * @author Jason Duffy
 * @date 10th September 2022
 * @brief 
 */

#include <avr/power.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "am_radio.h"
#include "pin_defines.h"


// Set default values based on 120BPM tempo. 
static uint16_t duration[6] = {2000,1000,500,250,125,62};


// Initialises timer/counter for radio transmission at a specified carrier frequency. 
void init_am_radio(frequency_khz_t carrier_freq)
{
    cli();
    // ----------------- TIMER 0 setup ------------------ //
    TCCR0A |= (1 << WGM01); // Timer 0 in CTC mode. 
    TCCR0A |= (1 << COM0B0); // Toggle OC0B on compare match.
    TCCR0B |= (1 << CS00); // Prescaler of 1.

    // F_CPU / (2 * 1 * (1 + 3)) = Carrier_freq
    // 8,000,000 / (2 * 1 * (1 + 3)) = 1,000,000
    uint8_t count_value = (((F_CPU / carrier_freq) / 2) - 1); // calculate count value. 
    OCR0A = count_value; // Set the carrier frequency.

    // ----------------- TIMER 1 setup ------------------ //

    // TODO: Make this setup dependant on F_CPU and carrier_freq_khz.

    TCCR1B |= (1 << WGM12); // Timer 1 in CTC mode.
    TCCR1B |= (1 << CS11); // Prescaler of 8.
    TIMSK1 |= (1 << OCIE1A); // Enable output compare match interrupt.
    sei();
}


ISR(TIMER1_COMPA_vect)
{
    ANTENNA_DDR ^= (1 << ANTENNA); // Toggle carrier on and off.
}


// Sets tempo for musical tones to be transmitted (in BPM).
void am_radio_set_tempo(uint8_t bpm)
{
    duration[SEMIBREVE] = (60000 / bpm) * 4;
    duration[MINIM] = (duration[SEMIBREVE] >> 1); // Div by 2
    duration[CROTCHET] = (duration[MINIM] >> 1); // Div by 2
    duration[QUAVER] = (duration[CROTCHET] >> 1); // Div by 2
    duration[SEMIQUAVER] = (duration[QUAVER] >> 1); // Div by 2
    duration[DEMISEMIQUAVER] = (duration[SEMIQUAVER] >> 1); // Div by 2
}


// Transmits a square wave, monophonic note for the specified duration.
void am_radio_transmit_note(note_pitch_t pitch, note_duration_t note_length)
{
    // Set pitch. 
    OCR1A = pitch;

    // Enable interrupts. 
    sei();

    // Wait for specified time. 
    for (uint16_t count = 0; count < duration[note_length]; ++count)
    {
        _delay_ms(1);
    }

    // Disable interrupts. 
    cli();

    // Back to full carrier freq. 
    ANTENNA_DDR |= (1 << ANTENNA);
}


// Waits a specified duration before playing the next note. 
void am_radio_rest(note_duration_t rest_length)
{
    // Wait for specified time. 
    for (uint16_t count = 0; count < duration[rest_length]; ++count)
    {
        _delay_ms(1);
    }
}


// Test sequence, transmits an arpeggio scale in C.
void arpeggio_in_c_test(void)
{
    am_radio_transmit_note(C2, CROTCHET);
    am_radio_rest(QUAVER);
    am_radio_transmit_note(E2, CROTCHET);
    am_radio_rest(QUAVER);
    am_radio_transmit_note(G2, CROTCHET);
    am_radio_rest(QUAVER);
    am_radio_transmit_note(C3, CROTCHET);
    am_radio_rest(QUAVER);
    am_radio_transmit_note(G2, CROTCHET);
    am_radio_rest(QUAVER);
    am_radio_transmit_note(E2, CROTCHET);
    am_radio_rest(QUAVER);
}



/*** end of file ***/

