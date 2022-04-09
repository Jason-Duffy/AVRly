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
 * @file mcp48x2_dac.c
 * @ingroup mcp48x2
 * @author Jason Duffy
 * @date 4th March 2022
 * @brief Driver for the MCP4812 10 bit DAC (digital to analog converter) chip.
 * @bug No known bugs. 
 * @details This file provides the basic low-level functionality for the
 * MCP4812 10 bit DAC from Microchip. This driver currently only allows for a
 * single DAC to be used, but this might be improved on at a later date. This
 * driver was written using the datasheet for the Microchip MCP4812 chip, which
 * can be found at the link below.
 * @see https://ww1.microchip.com/downloads/en/DeviceDoc/20002249B.pdf
 */

#include <util/delay.h>
#include <avr/interrupt.h>

#include "mcp48x2_dac.h"
#include "pin_defines.h"

#include "log_system.h"

#define CHANNEL_BIT              15U
#define GAIN_BIT                 13U
#define SHUTDOWN_BIT             12U
#define TWELVE_BIT_LEVEL_OFFSET  0U
#define TEN_BIT_LEVEL_OFFSET     2U
#define EIGHT_BIT_LEVEL_OFFSET   4U

#define TWELVE_BIT_MV_OFFSET     0U
#define TEN_BIT_MV_OFFSET        1U
#define EIGHT_BIT_MV_OFFSET      3U

static const char *p_system_tag = "MCP48x2_DAC";

/**
 * File scope copy of dac_config_t pointer to store address of config object.
 */
static dac_config_t *p_config_global;

/**
 * File scope variable to store the bitshift value to account for resolution
 * differences between chip models. 
 */
static uint8_t mv_resolution_shift = 0;

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
 * @param *p_config is a pointer to the dac_config_t object.
 */
void init_dac(dac_config_t *p_config)
{
    p_config_global = p_config;
    /**
    * Don't need to set phase & polarity as the default works with MCP4812 (0,0)
    * or (1,1).
    */

    // Delay to allow power ramp up in device.
    _delay_ms(500);

    cli();
    SPCR |= (1 << SPR0); // div 16, safer for breadboards
    SPCR |= (1 << MSTR); // Master mode
    SPCR |= (1 << SPE); // enable   
    DAC_CTRL_DDR |= (1 << DAC_CS); // Set chip select as output.
    DAC_CTRL_PORT |= (1 << DAC_CS); // Set CS line high (not selected).
    DAC_CTRL_DDR |= (1 << LDAC); // Set LDAC line (latch) as output.
    DAC_CTRL_PORT |= (1 << LDAC); // Set LDAC high.
    SPI_DDR |= (1 << SPI_MOSI); // Set MOSI as output.
    SPI_PORT |= (1 << SPI_MISO); // Set pullup on MISO.
    SPI_DDR |= (1 << SPI_SCK); // Set SCK as output.    
    sei(); // Set interrupt enable flag 

    // Save the value to bitshift millivolts value by. 
    if (p_config_global->model == mcp4802)
    {
      mv_resolution_shift = EIGHT_BIT_MV_OFFSET;
    }
    else if (p_config_global->model == mcp4812)
    {
      mv_resolution_shift = TEN_BIT_MV_OFFSET;
    }
    else
    {
      mv_resolution_shift = TWELVE_BIT_MV_OFFSET;
    }  

    // Establish latching settings
    if (!p_config_global->sync_manually)
    {
      DAC_CTRL_PORT &= ~(1 << LDAC);
    }
    log_message(p_system_tag, DEBUG, "About to call dac_reconfigure()");   
    dac_reconfigure(); // Apply config settings.
    log_message(p_system_tag, INFO, "DAC initialised");
}


/*
 * Sends a new millivolts value to be output on DAC. Use this function got the
 * MCP4802 and MCP4812 models.
 */
void dac_set_voltage(bool channel_a, uint16_t millivolts)
{
    // Manipulate mv value to suit register size of chip and gain setting.
    if (channel_a)
    {
        if (p_config_global->channel_a.gain_low)
        {   
            p_config_global->channel_a.level =
                                (millivolts >> mv_resolution_shift);
        }
        else
        {
            p_config_global->channel_a.level =
                                (millivolts >> (mv_resolution_shift + 1));
        }
    }
    else
    {
        if (p_config_global->channel_b.gain_low)
        {
            p_config_global->channel_b.level =
                                (millivolts >> mv_resolution_shift);
        }
        else
        {
            p_config_global->channel_b.level =
                                (millivolts >> (mv_resolution_shift + 1));
        }
    }

    // Send new values to DAC
    dac_reconfigure();
}


/*
 * Sends a new millivolts value to be output on DAC. Use this function for the
 * MCP4822 model with 12bit resolution - for the other chip models use
 * dac_set_voltage(). If gain_low = true, the resolution is down to 0.5mV,
 * however we want to avoid using floating point numbers, so just pass in the
 * integer millivolt value as the second parameter, then add a boolean
 * true/false for the third parameter. True = 0.5mV, false = 0mV. 
 */
void dac_set_voltage_12_bit(bool channel_a, uint16_t millivolts, bool fractional)
{
    if (channel_a)
    {
        if(p_config_global->channel_a.gain_low)
        {
            p_config_global->channel_a.level =
                                (millivolts << (TWELVE_BIT_MV_OFFSET + 1));
            // Add the 0.5mV value if required. 
            if (fractional == true)
            {
                p_config_global->channel_a.level += 1;
            }
        }
        else
        {
            p_config_global->channel_a.level =
                                (millivolts << TWELVE_BIT_MV_OFFSET);
        }
    }
    else
    {
        if(p_config_global->channel_b.gain_low)
        {
            p_config_global->channel_b.level =
                                (millivolts << (TWELVE_BIT_MV_OFFSET + 1));
            // Add the 0.5mV value if required. 
            if (fractional == true)
            {
                p_config_global->channel_b.level += 1;
            }
        }
        else
        {
            p_config_global->channel_b.level =
                                (millivolts << TWELVE_BIT_MV_OFFSET);
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

    // Set up config bits in 16bit word to be sent. 
    channel_a_data &= ~(1 << CHANNEL_BIT); // Clear channel bit (Channel A).
    channel_a_data |= (p_config_global->channel_a.gain_low << GAIN_BIT);
    channel_a_data |= (p_config_global->channel_a.active << SHUTDOWN_BIT);

    channel_b_data |= (1 << CHANNEL_BIT); // Set channel bit (Channel B).
    channel_b_data |= (p_config_global->channel_b.gain_low << GAIN_BIT);
    channel_b_data |= (p_config_global->channel_b.active << SHUTDOWN_BIT);

    // Shift level into correct place for chip and OR it into our 16bit word.
    if (p_config_global->model == mcp4802)
    {
        channel_a_data |=
                (p_config_global->channel_a.level << EIGHT_BIT_LEVEL_OFFSET);

        channel_b_data |=
                (p_config_global->channel_b.level << EIGHT_BIT_LEVEL_OFFSET);
    }
    else if (p_config_global->model == mcp4812)
    {
        channel_a_data |=
                (p_config_global->channel_a.level << TEN_BIT_LEVEL_OFFSET);

        channel_b_data |=
                (p_config_global->channel_b.level << TEN_BIT_LEVEL_OFFSET);
    }
    else
    {
        channel_a_data |=
                (p_config_global->channel_a.level << TWELVE_BIT_LEVEL_OFFSET);
        channel_b_data |=
                (p_config_global->channel_b.level << TWELVE_BIT_LEVEL_OFFSET);
    }

    // Send new data to DAC over SPI. 
    spi_trade_byte(channel_a_data);
    spi_trade_byte(channel_b_data);

    // If sync_manually is set to false, pulse LDAC to update values. 
    if (!p_config_global->sync_manually)
    {
        pulse_latch();
    }
}


/*
 * Pulses LDAC pin pow for 1 microsecond. If sync_manually = true, call this
 * function to latch the new voltage values into the output registers. If
 * sync_manually = false, this function is called automatically by
 * dac_reconfigure() or dac_set_voltage().
 */
void pulse_latch(void)
{
    DAC_CTRL_PORT &= ~(1 << LDAC);
    _delay_us(1);
    DAC_CTRL_PORT |= (1 << LDAC);
}

// ------------------------------------------------------------------------- //
// ------------------------ Private Helper Functions ----------------------- //
// ------------------------------------------------------------------------- // 

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


/*
 * Private helper function - pulls CS line (Chip Select) low in order to begin
 * SPI communication with DAC.
 */
void chip_select(void)
{
    DAC_CTRL_PORT &= ~(1 << DAC_CS);
}

/*
 * Private helper function - pulls CS line (Chip Select) high to signal the end
 * of SPI communication with DAC.
 */
void chip_deselect(void)
{
    DAC_CTRL_PORT |= (1 << DAC_CS);
}


/*** end of file ***/
