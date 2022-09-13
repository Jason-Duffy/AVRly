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
 * @file sweet_child_o_mine.c
 * @ingroup am_radio
 * @author Jason Duffy
 * @date 10th September 2022
 * @brief 
 */

#include "sweet_child_o_mine.h"
#include "am_radio.h"

// Function prototypes. 
void sweet_child_riff_part_1(void);
void sweet_child_riff_part_2(void);
void sweet_child_riff_part_3(void);

void init_radio(void)
{
    // Initialisation routines
    init_am_radio(_1000_KHZ);
    // Set tempo in BPM
    am_radio_set_tempo(120);
}


void sweet_child_riff(void)
{
    sweet_child_riff_part_1();
    sweet_child_riff_part_1();
    sweet_child_riff_part_2();
    sweet_child_riff_part_2();
    sweet_child_riff_part_3();
    sweet_child_riff_part_3();
    sweet_child_riff_part_1();
    sweet_child_riff_part_1();
}


void sweet_child_riff_part_1(void)
{
    // Intro, Bar 1
    am_radio_transmit_note(C2, QUAVER);
    am_radio_transmit_note(C3, QUAVER);
    am_radio_transmit_note(G2, QUAVER);
    am_radio_transmit_note(F2, QUAVER);
    am_radio_transmit_note(F3, QUAVER);
    am_radio_transmit_note(G2, QUAVER);
    am_radio_transmit_note(E3, QUAVER);
    am_radio_transmit_note(G2, QUAVER);
}


void sweet_child_riff_part_2(void)
{
    // Intro, Bar 3
    am_radio_transmit_note(D2, QUAVER);
    am_radio_transmit_note(C3, QUAVER);
    am_radio_transmit_note(G2, QUAVER);
    am_radio_transmit_note(F2, QUAVER);
    am_radio_transmit_note(F3, QUAVER);
    am_radio_transmit_note(G2, QUAVER);
    am_radio_transmit_note(E3, QUAVER);
    am_radio_transmit_note(G2, QUAVER);
}


void sweet_child_riff_part_3(void)
{
    // Intro, Bar 5
    am_radio_transmit_note(F2, QUAVER);
    am_radio_transmit_note(C3, QUAVER);
    am_radio_transmit_note(G2, QUAVER);
    am_radio_transmit_note(F2, QUAVER);
    am_radio_transmit_note(F3, QUAVER);
    am_radio_transmit_note(G2, QUAVER);
    am_radio_transmit_note(E3, QUAVER);
    am_radio_transmit_note(G2, QUAVER);
}