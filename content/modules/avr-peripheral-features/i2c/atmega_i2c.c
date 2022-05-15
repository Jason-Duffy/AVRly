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
 * @file i2c.c
 * @ingroup i2c
 * @author Jason Duffy
 * @date 5th March 2022
 * @brief I2C communications driver for AVR MCU's.
 * @bug No known bugs. 
 * 
 * This file provides basic I2C protocol comms functionality.
 * Please note: Blocking waits are used whilst the host waits for hardware to
 * set bits in registers. 
 * 
 * The symbol F_CPU must be defined for the bus timing calculations - usually
 * defined in Makefile. 
 */


#include <avr/interrupt.h> 

#include "i2c.h"


/*
 * Sets pullups and initializes i2c clock to desired bus speed.
 * @param bus_speed is the desired i2c clock frequency.
 */
void init_i2c(uint32_t bus_speed)
{
  uint32_t base_frequency = (F_CPU / bus_speed);
  TWBR = (uint8_t)((base_frequency - 16) / (2 * 1)); // Prescaler of 1
  TWCR |= (1 << TWEN); // Enable I2C.
}


/*
 * Loops until the i2c message is complete, as the  hardware sets the TWINT
 * flag.
 */
void i2c_wait_for_complete(void)
{
  loop_until_bit_is_set(TWCR, TWINT);
}


/*
 * Sends a start condition (sets TWSTA).
 */
void i2c_start(void)
{
  TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTA);
  i2c_wait_for_complete();
}


/*
 * Sends a stop condition (sets TWSTO).
 */
void i2c_stop(void)
{
  TWCR = (1 << TWINT) | (1 << TWEN) | (1 <<TWSTO);
}


/*
 * Loads data, sends it out, waiting for completion.
 * @param data is the byte of data to be sent. 
 */
void i2c_send(uint8_t data)
{
  TWDR = data;
  TWCR = (1 << TWINT) | (1 << TWEN); // init and enable.
  i2c_wait_for_complete();
}


/*
 * Read in from slave, sending ACK when done (sets TWEA).
 * @returns The data received from the peripheral device. 
 */
uint8_t i2c_read_ack(void)
{
  TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
  i2c_wait_for_complete();
  return (TWDR);
}


/**
 * Read in from slave, sending NOACK when done (no TWEA).
 * @returns The data received from the peripheral device. 
 */

uint8_t i2c_read_no_ack(void)
{
  TWCR = (1 << TWINT) | (1 << TWEN);
  i2c_wait_for_complete();
  return (TWDR);
}


/*** end of file ***/
