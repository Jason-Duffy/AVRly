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
 * @file bme280_driver.h
 * @ingroup bme280
 * @author Jason Duffy
 * @date 22nd June 2022
 * @brief
 * @bug No known bugs. 
 */

#ifndef BME_TWO_EIGHTY_DRIVER_DOT_H
#define BME_TWO_EIGHTY_DRIVER_DOT_H

// burst_read is from registers 0xF7 to 0xFE (temperature, pressure and humidity)
// pressure and temperature are read out in 20 bit unsigned format
// humidity is read out in 16 bit unsigned format

#include <stdbool.h>
#include <stdint.h>
#include <util/delay.h>
#include "i2c.h"

// 7-bit Device Address followed by read/write bit.
#define BME280_ADDRESS_W		0xEC // 0xEE if SDO is pulled high
#define BME280_ADDRESS_R		0xED // 0xEF if SDO is pulled high

// Register addresses (See memory map P.27)
#define CONFIG_REG				0xF5 // Read/Write
#define CTRL_MEAS_REG			0xF4 // Read/Write
#define STATUS_REG				0xF3 // Read
#define CTRL_HUM_REG			0xF2 // Read/Write. Changes here only come into
									 // effect after CTRL_MEAS is written to.
#define SOFT_RESET_REG			0xE0 // Write, value to perform reset is 0xB6
#define CHIP_ID_REG				0xD0 // Read, value returned should be 0x60

// Oversampling settings
#define SKIPPED					0 // Skip, output set to 0x8000
#define OVERSAMPLE_x1			1
#define OVERSAMPLE_x2			2
#define OVERSAMPLE_x4			3
#define OVERSAMPLE_x8			4
#define OVERSAMPLE_x16			5

#define SLEEP_MODE				0
#define FORCED_MODE				1
#define NORMAL_MODE				3

// Temperature compensation variables (values taken from BME280 during init)
extern uint16_t dig_T1;
extern int16_t dig_T2, dig_T3;

// Pressure compensation variables
/*
extern uint16_t dig_P1;
extern int16_t dig_P2, dig_P3, dig_P4, dig_P5, dig_P6, dig_P7, dig_P8, dig_P9;
*/

// Humidity compensation variables
extern uint8_t dig_H1;
extern int16_t dig_H2;
extern uint8_t dig_H3;
extern int16_t dig_H4, dig_H5;
extern int8_t dig_H6;

extern int8_t temp;
extern uint8_t humidity;


/**
 * @brief Initialise the device ready for measurements to be taken.
 */
void init_BME280(void);


/**
 * @brief Writes a single byte to a specified reguster.
 * @param reg is the reguster to be written to.
 * @param byte is the data to be sent.
 */
void BME280_write_byte(uint8_t reg, uint8_t byte);


/**
 * @brief Writes a 16bit word to a pair of 8 bit registers.
 * @param reg1 is the first register to be written to.
 * @param reg2 is the second register to be written to.
 * @param msb is the most signnificant byte to be sent. 
 * @param lsb is the least significant byte to be sent. 
 */
void BME280_write_word(uint8_t reg1, uint8_t reg2, uint8_t msb, uint8_t lsb);


/**
 * @brief Reads an 8bit unsigned integer from a specified memory location.
 * @param start_address is the address to be read from.
 * @returns The data read from the device is returned.
 */
uint8_t BME280_read_byte_unsigned(uint8_t start_address);


/**
 * @brief Reads an 8bit signed integer from a specified memory location.
 * @param start_address is the address to be read from.
 * @returns The data read from the device is returned.
 */
int8_t BME280_read_byte_signed(uint8_t start_address);


/**
 * @brief Reads a 16bit unsigned integer from a specified register.
 * @param start_address is the first memory location to be read from.
 * @returns The data read from the device is returned. 
 */
uint16_t BME280_read_word_unsigned(uint8_t start_address);


/**
 * @brief Reads a 16bit signed integer from a specified register.
 * @param start_address is the first reguster to be written to.
 * @returns The data read from the device is returned. 
 */
int16_t BME280_read_word_signed(uint8_t start_address);


/**
 * @brief Reads in all compensation data from the device and stores it in a
 * buffer.
 */
void BME280_read_comp_data(void);


void BME280_get_raw_temp_val(void);

void BME280_get_raw_hum_val(void);

void BME280_burst_read(uint8_t start_addr, uint8_t length); // Reads all data output regusters and stores in array

int32_t BME280_compensate_temp(int32_t adc_T);

//int32_t BME280_compensate_pressure(int32_t adc_P);

uint32_t BME280_compensate_humidity(int32_t adc_H);

void BME280_get_readings(void);


#endif