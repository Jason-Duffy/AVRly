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
 * @file mcp4812_dac.h
 * @author Jason Duffy
 * @date 4th March 2022
 * @brief Driver for the MCP4812 10 bit DAC (digital to analog converter) chip.
 * @bug No known bugs. 
 * 
 * This file provides the basic low-level functionality for the MCP4812 10 bit
 * DAC from Microchip. This driver currently only allows for a single DAC to be
 * used, but this might be improved on at a later date.
 * 
 * This driver was written using the datasheet for the Microchip MCP4812 chip,
 * which can be found at the link below.
 * @see https://ww1.microchip.com/downloads/en/DeviceDoc/20002249B.pdf
 */

#ifndef MCP_FOUR_EIGHT_ONE_TWO_DOT_H
#define MCP_FOUR_EIGHT_ONE_TWO_DOT_H

#include <stdbool.h>

typedef struct
{
    bool channel_a_gain_low;    // true = LOW (0 - 2048mV), false = HIGH (0 - 4096mV).
    bool channel_b_gain_low;    // true = LOW (0 - 2048mV), false = HIGH (0 - 4096mV).
    bool channel_a_active;      // true = Channel active, false = channel shutdown.
    bool channel_b_active;      // true = Channel active, false = channel shutdown.
    uint16_t channel_a_level;   // Value to be output on channel A.
    uint16_t channel_b_level;   // Value to be output on channel B.
} dac_config_t;


/**
 * Initialisation routine (run once at startup).
 * This function is to be called before using any other DAC functions.
 * Instantiate the dac_config_t object first then pass it's address init_lcd()
 * before using any other lcd functions.
 * @param p_config is a pointer to the dac_config_t object.
 * @return Returns void.
 */
void init_dac(dac_config_t *p_config);

void dac_set_voltage(uint16_t millivolts);

void dac_reconfigure(void);

#endif // MCP_FOUR_EIGHT_ONE_TWO_DOT_H