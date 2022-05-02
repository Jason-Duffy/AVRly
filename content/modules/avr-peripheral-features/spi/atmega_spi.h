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
 * @ingroup spi
 * @author Jason Duffy
 * @date 9th April 2022
 * @brief Driver for SPI communication between the ATmega328P and other SPI
 * compatible devices. 
 * @bug No known bugs. 
 * @details This file provides the basic SPI comms setup and initialisation
 * instructions. The following ports/pins must be defined in pin_defines.h:
 * SPI_DDR, SPI_PORT, SPI_MOSI SPI_MISO, SPI_SCK, SPI_SS.
 */

#ifndef ATMEGA_SPI_DOT_H
#define ATMEGA_SPI_DOT_H

#include <stdint.h>

/**
 * Enumerated constants for selecting the transfer mode, most significant bit
 * first of least significant bit first. 
 */
typedef enum
{
    lsb_first,
    msb_first,
}spi_transfer_mode_t;

/**
 * Enumerated constants for selecting whether the host MCU is the controller or
 * peripheral (formerly known as master/slave).
 */
typedef enum
{
    peripheral,
    controller,   
}spi_control_mode_t;

/**
 * Enumerated constants for selecting the SPI polarity mode, rising or falling
 * on leading clock edge.
 */
typedef enum
{
    rising_edge,
    falling_edge,
}spi_polarity_mode_t;

/**
 * Enumerated constants for selecting the SPI phase mode, on leading clock edge.
 * lead_sample_rising_edge is default. 
 */
typedef enum
{
    sample_leading_edge,
    sample_trailing_edge,
}spi_phase_mode_t;

/**
 * Enumerated constants for selecting the SPI clock rate. cpu_clk_div_4 is
 * default. 
 */
typedef enum
{
    cpu_clk_div_4,
    cpu_clk_div_16,
    cpu_clk_div_64,
    cpu_clk_div_128,
}spi_clk_rate_t;

/**
 * Enumerated constants for selecting whether the SPI clock speed is doubled.
 */
typedef enum
{
    single_speed,
    double_speed,
}spi_dbl_clk_mode_t;


/**
 * Initialisation routine to set up SPI comms. Must be called before any other
 * functions in this file can be used.
 * @param transfer_mode lsb_first or msb_first.
 * @param control_mode controller or peripheral.
 * @param polarity_mode rising_edge or falling_edge.
 * @param phase_mode lead_sample_rising_edge or lead_setup_rising_edge.
 * @param clk_rate Sets the speed of the SPI clock - divided down from F_CPU
 * speed.
 * @param dbl_clock single_speed or double_speed. 
 */
void init_spi(spi_transfer_mode_t transfer_mode,
              spi_control_mode_t control_mode,
              spi_polarity_mode_t polarity_mode,
              spi_phase_mode_t phase_mode,
              spi_clk_rate_t clk_rate,
              spi_dbl_clk_mode_t dbl_clock);


/**
 * Sends out a byte of data over SPI and returns the byte it receives. 
 * @param uint8_t data: The byte of data to be sent from the host MCU to the
 * peripheral device.
 * @return The data received from the peripheral device is returned.
 */
uint8_t spi_trade_byte(uint8_t data);


/**
 * Sends out a 16bit word of data over spi (in two bytes) and returns the byte
 * it receives. 
 * @param uint16_t data: The byte of data to be sent from the host MCU to the
 * peripheral device.
 * @return The data received from the peripheral device is returned.
 */
uint16_t spi_trade_word(uint16_t data);


#endif // ATMEGA_SPI_DOT_H


/*** End of file. ***/
