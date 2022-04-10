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
 * @file atmega_spi.h
 * @ingroup mcp48x2
 * @author Jason Duffy
 * @date 9th April 2022
 * @brief Driver for SPI communication between the ATmega328P and other SPI
 * compatible devices. 
 * @bug No known bugs. 
 * @details This file provides the basic SPI comms setup and initialisation
 * instructions. The following ports/pins must be defined in pin_defines.h:
 * SPI_DDR, SPI_PORT, SPI_MOSI SPI_MISO, SPI_SCK.
 */

#include <avr/io.h>
#include <avr/interrupt.h>

#include "atmega_spi.h"
#include "pin_defines.h"

/**
 * Initialisation routine to set up SPI comms. Must be called before any other
 * functions in this file can be used.
 * @param spi_transfer_mode_t: lsb_first or msb_first.
 * @param spi_control_mode_t control_mode: controller or peripheral.
 * @param spi_phase_mode_t phase_mode: lead_sample_rising_edge or
 * lead_setup_rising_edge.
 * @param spi_clk_rate_t clk_rate: Sets the speed of the SPI clock - divided
 * down from F_CPU speed.
 * @param spi_dbl_clk_mode_t: single_speed or double_speed. 
 */
void init_spi(spi_transfer_mode_t transfer_mode,
              spi_control_mode_t control_mode,
              spi_polarity_mode_t polarity_mode,
              spi_phase_mode_t phase_mode,
              spi_clk_rate_t clk_rate,
              spi_dbl_clk_mode_t dbl_clock)
{
    SPI_DDR |= (1 << SPI_MOSI); // Set MOSI as output.
    SPI_DDR |= (1 << SPI_SCK); // Set SCK as output.
    SPI_DDR &= ~(1 << SPI_MISO); // Set MISO as input. 
    SPI_DDR &= ~(1 << SPI_SS); // Set SS as input.
    SPI_PORT |= (1 << SPI_MISO); // Set pullup on MISO.
    SPI_PORT |= (1 << SPI_SS); // Set pullup on SS.

    cli(); // Clear interrupt enable flag.
    SPCR |= (transfer_mode << DORD); // Set data order.
    SPCR |= (control_mode << MSTR); // Controller/peripheral mode select.
    SPCR |= (polarity_mode << CPOL); // Set polarity of SPI data. 
    SPCR |= (phase_mode << CPHA); // Set phase of SPI data.
    SPCR |= (clk_rate); // Set speed

    SPSR |= (dbl_clock << SPI2X); // Set double speed bit. 

    SPCR |= (1 << SPE); // Enable SPI. 

    sei(); // Set interrupt enable flag.
}


/**
 * Sends out a byte of data over SPI and returns the byte it receives. 
 */
uint8_t spi_trade_byte(uint8_t data)
{
    SPDR = data; // Send out byte of data. 
    loop_until_bit_is_set(SPSR, SPIF); // Wait for flag to be set. 
    data = SPDR; // Store the data received. 
    return data;
}


/**
 * Sends out a 16bit word of data over spi (in two bytes) and returns the byte
 * it receives. 
 */
uint16_t spi_trade_word(uint16_t data)
{
    uint8_t msb = 0;
    uint8_t lsb = 0;

    // Split word to send into 2 bytes and send the first one out. 
    msb |= (data >> 8U);
    lsb |= (data);
    SPDR = msb; 
    loop_until_bit_is_set(SPSR, SPIF);
    msb = SPDR; // Store the byte received. 

    // Send the second byte out. 
    SPDR = lsb;
    loop_until_bit_is_set(SPSR, SPIF);
    lsb = SPDR; // Store the second byte received. 

    // Combine the bytes received into 1 word. 
    uint16_t received_data = 0;
    received_data = (msb << 8U);
    received_data |= (lsb);

    return received_data;
}