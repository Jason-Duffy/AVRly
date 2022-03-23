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
 * @file i2c.h
 * @ingroup ccs811
 * @author Jason Duffy
 * @date 5th March 2022
 * @brief I2C communications driver for AVR MCU's.
 * @bug No known bugs. 
 * 
 * This file provides basic I2C protocol comms functionality.
 * Please note: Blocking waits are used whilst the host waits for hardware to
 * set flags in registers. 
 */

// Functions for i2c communication
#ifndef I_TWO_C_DOT_H
#define I_TWO_C_DOT_H

#include <avr/io.h>


/**
 * Sets pullups and initializes bus speed to desired bus speed.
 */
void init_i2c(uint32_t bus_speed);


/**
 * Waits until the hardware sets the TWINT flag.
 */
void i2c_wait_for_complete(void);


/**
 * Sends a start condition (sets TWSTA).
 */
void i2c_start(void);


/**
 * Sends a stop condition (sets TWSTO).
 */
void i2c_stop(void);


/**
 * Loads data, sends it out, waiting for completion.
 */
void i2c_send(uint8_t data);


/**
 * Read in from slave, sending ACK when done (sets TWEA).
 */
uint8_t i2c_read_ack(void);


/**
 * Read in from slave, sending NOACK when done (no TWEA).
 */
uint8_t i2c_read_no_ack(void);


#endif // I_TWO_C_DOT_H


/*** end of file ***/
