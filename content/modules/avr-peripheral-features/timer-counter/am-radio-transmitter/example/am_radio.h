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
 * @file am_radio.h
 * @ingroup am_radio
 * @author Jason Duffy
 * @date 10th September 2022
 * @brief Driver for a small, low power AM radio transmitter, to broadcast
 * monophonic square wave tones over a short distance. This project was
 * inspired by the book "Make: AVR Programming" by Elliot Williams. 
 * 
 * Only tested with F_CPU = 8MHZ, but will build on this later to make it work
 * with other CPU speeds. 
 */

#ifndef AM_RADIO_DOT_H
#define AM_RADIO_DOT_H

#include <stdint.h>
#include "scale.h"


/**
 * Enum to expose the predefined carrier frequency options.
 * 1000KHZ (1MHZ) is ideal, but may be taken in your locality so try another if
 * there is too much interferance. 
 */
typedef enum
{   
    _500_KHZ = 500000,
    _570_KHZ = 570000,
    _670_KHZ = 670000,
    _800_KHZ = 800000,
    _1000_KHZ = 1000000,
    _1333_KHZ = 1333000,
}frequency_khz_t;


/**
 * Enum to expose the predefined duration options. 
 */
typedef enum
{
    SEMIBREVE,
    MINIM,
    CROTCHET,
    QUAVER,
    SEMIQUAVER,
    DEMISEMIQUAVER,
}note_duration_t;


/**
 * Initialises timer/counter for radio transmission at a specified carrier frequency.
 */
void init_am_radio(frequency_khz_t carrier_freq);

/**
 * Sets tempo for musical tones to be transmitted (in BPM).
 */
void am_radio_set_tempo(uint8_t tempo);

/**
 * Transmits a square wave, monophonic note for the specified duration.
 */
void am_radio_transmit_note(note_pitch_t pitch, note_duration_t note_length);

/**
 * Waits a specified duration before playing the next note. 
 */
void am_radio_rest(note_duration_t rest_length);

/**
 * Test sequence, transmits an arpeggio scale in C major. 
 */
void arpeggio_in_c_test(void);


#endif //AM_RADIO_DOT_H

/*** end of file ***/