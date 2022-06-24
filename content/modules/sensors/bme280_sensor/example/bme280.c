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
 * @file bme280.c
 * @ingroup bme280
 * @author Jason Duffy
 * @date 22nd June 2022
 * @brief
 * @bug No known bugs.
 */

#include <util/delay.h>

#include "bme280.h"
#include "atmega_i2c.h"
#include "log_system.h"


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

#define BUS_SPEED_100KHZ		100000U

log_system_config_t bme280_log = 
{
	.p_system_tag = "BME280",
	.file_log_level = DEBUG,
};


static uint8_t BME280_read_buffer[33]; 

// Temperature compensation variables (values taken from BME280 during init)
static uint16_t dig_T1 = 0;
static int16_t dig_T2 = 0;
static int16_t dig_T3 = 0;

// Pressure compensation values
static uint16_t dig_P1 = 0;
static int16_t dig_P2 = 0;
static int16_t dig_P3 = 0;
static int16_t dig_P4 = 0;
static int16_t dig_P5 = 0;
static int16_t dig_P6 = 0;
static int16_t dig_P7 = 0;
static int16_t dig_P8 = 0;
static int16_t dig_P9 = 0;


// Humidity compensation variables
static uint8_t dig_H1 = 0;
static int16_t dig_H2 = 0;
static uint8_t dig_H3 = 1;
static int16_t dig_H4 = 0;
static int16_t dig_H5 = 0;
static int16_t dig_H6 = 0;

//###########################################################################//
// 		         	Forward declarations for helper functions    	   	     //
//###########################################################################//

void bme280_write_byte(uint8_t reg, uint8_t byte);
void bme280_write_word(uint8_t reg1, uint8_t reg2, uint8_t msb, uint8_t lsb);
uint16_t bme280_read_word(uint8_t start_address);
uint8_t bme280_read_byte(uint8_t reg);
void bme280_read_comp_data(void);
uint32_t bme280_get_raw_temp_val(void);
uint32_t bme280_get_raw_hum_val(void);
void bme280_burst_read(uint8_t start_addr, uint8_t start_position, uint8_t length);
int32_t bme280_compensate_temp(int32_t adc_T);
int32_t bme280_compensate_pressure(int32_t adc_P);
uint32_t bme280_compensate_humidity(int32_t adc_H);

//###########################################################################//
// 			Higher level functions for main to interract with chip		     //
//###########################################################################//


/*
 * @brief Initialise the device ready for measurements to be taken.
 */
void init_bme280(void)
{	
	// Setup I2C hardware fpr use.
	init_i2c(BUS_SPEED_100KHZ);

	// Perform ID check. 
	uint8_t id = bme280_read_byte(CHIP_ID_REG);
	if (id == 0x60)
	{
		log_message(&bme280_log,
					DEBUG,
					"In init_bme280(), Chip ID check passed.");
	}
	else
	{
		log_message(&bme280_log,
					ERROR,
					"In init_bme280(), Chip ID check failed.");
	}

	// Read compensation data from sensor and save it.
	bme280_read_comp_data();

	// 
	bme280_write_byte(CTRL_HUM_REG, OVERSAMPLE_x1);

	//
	bme280_write_byte(CONFIG_REG, 0b10100000);

	// oversample x1 temp, pressure off, forced mode
	bme280_write_byte(CTRL_MEAS_REG, 0b00100001);
}


/*
 * @brief Fetches the latest temperature data from the sensor, compensates and
 * formats the data in degrees Celcius * 100.
 * @returns eg. A return value of 5123 = 51.23˚C (degrees Celcius). 
 */ 
int16_t bme280_get_temperature(void)
{
	int32_t retval;
	uint32_t raw_temp_adc_val;

	bme280_write_byte(CTRL_MEAS_REG, 0b00100001); // oversample x1 temp, pressure off, forced mode
	raw_temp_adc_val = bme280_get_raw_temp_val();
	retval = bme280_compensate_temp(raw_temp_adc_val);

	return retval;
}

#if 0
/*
 * @brief Fetches the latest humidity data from the sensor, compensates and
 * formats the data as %RH * 100.
 * @returns eg. A return value of 2852 = 28.52 %RH (Relative Humidity).
 */ 
uint16_t bme280_get_humidity(void)
{
	uint32_t retval;
	uint16_t raw_hum_adc_val;

	bme280_write_byte(CTRL_MEAS_REG, 0b00100001); // oversample x1 temp, pressure off, forced mode
	raw_hum_adc_val = bme280_get_raw_hum_val();
	retval = bme280_compensate_humidity(raw_hum_adc_val);
	retval *= 100;
	retval = (retval >> 10);

	return retval;
}
#endif



if 1
/*
 * @brief Fetches the latest humidity data from the sensor, compensates and
 * formats the data as %RH * 100.
 * @returns eg. A return value of 2852 = 28.52 %RH (Relative Humidity).
 */ 
uint16_t bme280_get_humidity(void)
{
	uint32_t retval;
	uint16_t raw_hum_adc_val;

	bme280_write_byte(CTRL_MEAS_REG, 0b00100001); // oversample x1 temp, pressure off, forced mode
	raw_hum_adc_val = bme280_get_raw_hum_val();
	retval = bme280_compensate_humidity(raw_hum_adc_val);
	retval *= 100;
	retval = (retval >> 10);

	return retval;
}
#endif

/*
 * @brief Fetches the latest pressure data from the sensor, compensates and
 * formats the data as Pa * 100.
 * @returns eg. A return value of 96386 = 963.86 Pa (Pascals).
 */ 
uint16_t bme280_get_pressure(void)
{
	// Some pressure-getting code goes here.
	return 0; 
}


//######################################################################################################################//
// 												Helper functions for I/O ctrl											//
//######################################################################################################################//

/**
 * @brief Writes a single byte to a specified reguster.
 * @param reg is the reguster to be written to.
 * @param byte is the data to be sent.
 */
void bme280_write_byte(uint8_t reg, uint8_t byte)
{
	i2c_start();
	i2c_send(BME280_ADDRESS_W);
	i2c_send(reg);
	i2c_send(byte);
	i2c_stop();
}

uint8_t bme280_read_byte(uint8_t reg) // Reads a single byte from specified register
{
	uint8_t byte;

	i2c_start();
	i2c_send(BME280_ADDRESS_W);
	i2c_send(reg);
	i2c_start();
	i2c_send(BME280_ADDRESS_R);
	byte = i2c_read_no_ack();
	i2c_stop();
	return byte;
}

// Reads a whole section of memory addresses
void bme280_burst_read(uint8_t start_address, uint8_t start_position, uint8_t length)
{
	i2c_start();
	i2c_send(BME280_ADDRESS_W);
	i2c_send(start_address);
	i2c_start();
	i2c_send(BME280_ADDRESS_R);

	int i;
	for (i = 0; i < (length - 1); ++i)
	{
		BME280_read_buffer[i] = i2c_read_ack();
	}
	BME280_read_buffer[i] = i2c_read_no_ack();

	i2c_stop();
}


/**
 * @brief Reads a 16bit unsigned integer from a specified register.
 * @param start_address is the first memory location to be read from.
 * @returns The data read from the device is returned. 
 */
uint16_t bme280_read_word(uint8_t start_address)
{
	unsigned short msb;
	unsigned short lsb;
	unsigned short word;

	i2c_start();
	i2c_send(BME280_ADDRESS_W);
	i2c_send(start_address);
	i2c_start();
	i2c_send(BME280_ADDRESS_R);

	lsb = i2c_read_ack();
	msb = i2c_read_no_ack();
	i2c_stop();

	word = (msb << 8);
	word |= lsb;
	return word;
}


/**
 * @brief Reads in all compensation data from the device and stores it in a
 * buffer.
 */

void bme280_read_comp_data(void)
{
	signed short h_lsb;
	signed short h_msb;

	// Read and store temperature compensation data. 
	dig_T1 = bme280_read_word(0x88);
	dig_T2 = bme280_read_word(0x8A);
	dig_T3 = bme280_read_word(0x8C);

	// Read and store pressure compensation data.
	dig_P1 = bme280_read_word(0x8E);
	dig_P2 = bme280_read_word(0x90);
	dig_P3 = bme280_read_word(0x92);
	dig_P4 = bme280_read_word(0x94);
	dig_P5 = bme280_read_word(0x96);
	dig_P6 = bme280_read_word(0x98);
	dig_P7 = bme280_read_word(0x9A);
	dig_P8 = bme280_read_word(0x9C);
	dig_P9 = bme280_read_word(0x9E);

	// Read and store humidity compensation data.
	dig_H1 = bme280_read_byte(0xA1);
	dig_H2 = bme280_read_word(0xE1);
	dig_H3 = bme280_read_byte(0xE3);

	h_msb = bme280_read_byte(0xE4);
	h_lsb = bme280_read_byte(0xE5);
	h_lsb &= 0b00001111;
	dig_H4 = h_lsb;
	dig_H4 |= (h_msb << 4);

	h_msb = bme280_read_byte(0xE6);
	h_lsb = bme280_read_byte(0xE5);
	h_lsb &= 0b11110000;
	dig_H5 = (h_lsb >> 4);
	dig_H5 |= (h_msb << 4);

	dig_H6 = bme280_read_byte(0xE7);
}


uint32_t bme280_get_raw_temp_val(void)
{
	uint32_t retval;
	uint32_t temp_msb;
	uint32_t temp_lsb;
	uint32_t temp_xlsb;

	i2c_start();
	i2c_send(BME280_ADDRESS_W);
	i2c_send(0xFA);
	i2c_start();
	i2c_send(BME280_ADDRESS_R);
	temp_msb = i2c_read_ack();
	temp_lsb = i2c_read_ack();
	temp_xlsb = i2c_read_no_ack();
	i2c_stop();

	retval = temp_msb << 12;
	retval |= temp_lsb << 4;
	retval |= temp_xlsb >> 4;

	return retval;
}

uint32_t bme280_get_raw_hum_val(void)
{
	uint32_t retval;
	uint16_t hum_msb;
	uint16_t hum_lsb;

	i2c_start();
	i2c_send(BME280_ADDRESS_W);
	i2c_send(0xFD);
	i2c_start();
	i2c_send(BME280_ADDRESS_R);
	hum_msb = i2c_read_ack();
	hum_lsb = i2c_read_no_ack();
	i2c_stop();

	retval = hum_msb << 8;
	retval |= hum_lsb;

	return retval;
}

//######################################################################################################################//
// 						Compensation formulae for converting raw ADC values into unit measurements						//
//######################################################################################################################//

// Returns temperature in DegC, resolution is 0.01 DegC. Output value of "5123" equals 51.23 DegC.
// t_fine carries fine temperature as global value

int32_t t_fine; // (Signed) Fine temperature value to be carried over to pressure and humidity compensation formulae.

int32_t bme280_compensate_temp(int32_t adc_T)
{
	int32_t var1, var2, T;
	var1 = (((adc_T >> 3) - ((int32_t)dig_T1 << 1)) * ((int32_t)dig_T2)) >> 11;
	var2 = (((((adc_T >> 4) - ((int32_t)dig_T1)) * ((adc_T >> 4) - ((int32_t)dig_T1))) >> 12) * ((int32_t)dig_T3)) >> 14;
	t_fine = var1 + var2;
	T = (t_fine * 5 + 128) >> 8;
	return T;
}

// Returns pressure in Pa as unsigned 32 bit integer. Output value of "96386" equals 96386 Pa = 963.86 hPa

int32_t bme280_compensate_pressure(int32_t adc_P)
{
	int32_t var1, var2;
	uint32_t p;
	var1 = (t_fine >> 1) - 64000;
	var2 = (((var1 >> 2) * (var1 >> 2)) >> 11 ) * ((int32_t)dig_P6);
	var2 = var2 + ((var1 * ((int32_t)dig_P5)) << 1);
	var2 = (var2 >> 2) + (((int32_t)dig_P4) << 16);
	var1 = ((((int32_t)dig_P3 * (((var1 >> 2) * (var1 >> 2)) >> 13 )) >> 3) + (((((int32_t)dig_P2) * var1) >> 1 ))) >> 18;
	var1 = ((((32768 + var1)) * ((int32_t)dig_P1)) >> 15);

	if (var1 == 0)
	{
		return 0; // avoid exception caused by division by zero
	}

	p = ((((1048576) - adc_P) - (var2 >> 12))) * 3125;

	if (p < 0x80000000)
	{
		p = (p << 1) / (var1);
	}

	else
	{
		p = (p / var1) * 2;
	}

	var1 = ((dig_P9) * ((((p>>3) * (p >> 3)) >> 13))) >> 12;
	var2 = (((p >> 2)) * (dig_P8)) >> 13;
	p = (p + ((var1 + var2 + dig_P7) >> 4));
	return p;
}


// Returns humidity in %RH as unsigned 32 bit integer in Q22.10 format (22 integer and 10 fractional bits).
// Output value of "47445" represents 47445/1024 = 46.333 %RH

uint32_t bme280_compensate_humidity(int32_t adc_H)
{
	int32_t v_x1_u32r;

	v_x1_u32r = (t_fine - (76800));

	v_x1_u32r = (((((adc_H << 14) - (((int32_t)dig_H4) << 20) - (((int32_t)dig_H5) * v_x1_u32r)) + (16384)) >> 15) * (((((((v_x1_u32r *
	((int32_t)dig_H6)) >> 10) * (((v_x1_u32r * ((int32_t)dig_H3)) >> 11) + (32768))) >> 10) + (2097152)) * ((int32_t)dig_H2) + 8192) >> 14));

	v_x1_u32r = (v_x1_u32r - (((((v_x1_u32r >> 15) * (v_x1_u32r >> 15)) >> 7) * ((int32_t)dig_H1)) >> 4));
	v_x1_u32r = (v_x1_u32r < 0 ? 0 : v_x1_u32r);
	v_x1_u32r = (v_x1_u32r > 419430400 ? 419430400 : v_x1_u32r);
	return (uint32_t)(v_x1_u32r>>12);
}

