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
 * @file mcp48x2_dac.c
 * @ingroup mcp48x2
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

#include <util/delay.h>
#include <avr/interrupt.h>

#include "mcp48x2_dac.h"
#include "pin_defines.h"

#define CHANNEL_BIT         15U
#define GAIN_BIT            13U
#define SHUTDOWN_BIT        12U
#define TWELVE_BIT_OFFSET   0U
#define TEN_BIT_OFFSET      2U
#define EIGHT_BIT_OFFSET    4U

/**
 * File scope copy of dac_config_t pointer to store address of config object.
 */
static dac_config_t *p_config_global;

// Forward declarations of private helper functions.
void spi_trade_byte(uint16_t data);
void pulse_latch(void);
void chip_select(void);
void chip_deselect(void);


/**
 * Initialisation routine (run once at startup).
 * This function is to be called before using any other DAC functions.
 * Instantiate the dac_config_t object first then pass it's address into and
 * call init_lcd() before using any other lcd functions.
 * @param p_config is a pointer to the dac_config_t object.
 * @return Returns void.
 */
void init_dac(dac_config_t *p_config)
{
    p_config_global = p_config;
/**
 * Don't need to set phase & polarity as the default works with MCP4812 (0,0)
 * or (1,1).
 */
  SPCR |= (1 << SPR0); // div 16, safer for breadboards
  SPCR |= (1 << MSTR); // clockmaster
  SPCR |= (1 << SPE); // enable

  DAC_CTRL_DDR |= (1 << DAC_CS); // Set chip select as output.
  DAC_CTRL_PORT |= (1 << DAC_CS); // Set CS line high (not selected).
  DAC_CTRL_DDR |= (1 << LDAC); // Set LDAC line (latch) as output.
  DAC_CTRL_PORT |= (1 << LDAC); // Set LDAC high.
  SPI_DDR |= (1 << SPI_MOSI); // Set MOSI as output.
  SPI_PORT |= (1 << SPI_MISO); // Set pullup on MISO.
  SPI_DDR |= (1 << SPI_SCK); // Set SCK as output.

  sei(); // Set interrupt enable flag

  if (!p_config_global->sync_manually)
  {
    DAC_CTRL_PORT &= ~(1 << LDAC);
  }
  dac_reconfigure(); // Apply config settings.
}


/**
 * Sends a new millivolts value to be output on DAC. 
 */
void dac_set_voltage(bool channel_a, uint16_t millivolts)
{
    if (channel_a)
    {
        if (p_config_global->channel_a.gain_low)
        {   
            // Divide mV by 2 bitwise style (faster).
            p_config_global->channel_a.level = (millivolts >> 1);
        }
        else
        {
            // Divide mV by 4 bitwise style (faster).
            p_config_global->channel_a.level = (millivolts >> 2);
        }
    }
    else
    {
        if (p_config_global->channel_b.gain_low)
        {
            // Divide mV by 2 bitwise style (faster).
            p_config_global->channel_b.level = (millivolts >> 1);
        }
        else
        {
            // Divide mV by 4 bitwise style (faster).
            p_config_global->channel_b.level = (millivolts >> 2);
        }
    }
    // Send new values to DAC
    dac_reconfigure();
}


/**
 * Applies new config settings. This function takes updated config settings for
 * both channels of DAC, then re-sends data so that the new settings take
 * effect.
 */
void dac_reconfigure(void)
{
    uint16_t channel_a_data = 0;
    uint16_t channel_b_data = 0;

    channel_a_data &= ~(1 << CHANNEL_BIT); // Clear channel bit (Channel A).
    channel_a_data |= (p_config_global->channel_a.gain_low << GAIN_BIT);
    channel_a_data |= (p_config_global->channel_a.active << SHUTDOWN_BIT);

    channel_b_data |= (1 << CHANNEL_BIT); // Set channel bit (Channel B).
    channel_b_data |= (p_config_global->channel_b.gain_low << GAIN_BIT);
    channel_b_data |= (p_config_global->channel_b.active << SHUTDOWN_BIT);

    if (p_config_global->model == mcp4802)
    {
        channel_a_data |= (p_config_global->channel_a.level << EIGHT_BIT_OFFSET);
        channel_b_data |= (p_config_global->channel_b.level << EIGHT_BIT_OFFSET);
    }
    else if (p_config_global->model == mcp4812)
    {
        channel_a_data |= (p_config_global->channel_a.level << TEN_BIT_OFFSET);
        channel_b_data |= (p_config_global->channel_b.level << TEN_BIT_OFFSET);
    }
    else
    {
        channel_a_data |= (p_config_global->channel_a.level << TWELVE_BIT_OFFSET);
        channel_b_data |= (p_config_global->channel_b.level << TWELVE_BIT_OFFSET);
    }

    spi_trade_byte(channel_a_data);
    spi_trade_byte(channel_b_data);

    if (!p_config_global->sync_manually)
    {
        pulse_latch();
    }
}


//TODO: Make this interrupt based with SPIE bit in SPCR register (Pg198)
void spi_trade_byte(uint16_t data)
{
    uint8_t msb = 0;
    uint8_t lsb = 0;

    chip_select();

    msb |= (data >> 8U);
    lsb |= (data);
    SPDR = msb; 
    loop_until_bit_is_set(SPSR, SPIF);
    SPDR = lsb;
    loop_until_bit_is_set(SPSR, SPIF);
    
    chip_deselect();
}

void pulse_latch(void)
{
    DAC_CTRL_PORT &= ~(1 << LDAC);
    _delay_us(1);
    DAC_CTRL_PORT |= (1 << LDAC);
}

void chip_select(void)
{
    DAC_CTRL_PORT &= ~(1 << DAC_CS);
}


void chip_deselect(void)
{
    DAC_CTRL_PORT |= (1 << DAC_CS);
}
/*** end of file ***/
