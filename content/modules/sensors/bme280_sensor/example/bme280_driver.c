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
 * @file bme280_driver.c
 * @ingroup bme280
 * @author Jason Duffy
 * @date 22nd June 2022
 * @brief
 * @bug No known bugs.
 */


#include "BME280_DRIVER.h"

uint8_t BME280_read_buffer[33]; 

// Temperature compensation variables (values taken from BME280 during init)
uint16_t dig_T1 = 0;
int16_t dig_T2, dig_T3 = 0;

uint32_t raw_temp_adc;
uint16_t raw_hum_adc;
int8_t temp;
uint8_t humidity;

// Pressure compensation variables
/*
uint16_t dig_P1 = 0;
int16_t dig_P2, dig_P3, dig_P4, dig_P5, dig_P6, dig_P7, dig_P8, dig_P9 = 0;
*/

// Humidity compensation variables
unsigned char dig_H1 = 0;
signed short dig_H2 = 0;
unsigned char dig_H3 = 1;
signed short dig_H4, dig_H5 = 0;
signed char dig_H6 = 0;



//###########################################################################//
// 			Higher level functions for main to interract with chip		     //
//###########################################################################//


/*
 * @brief Initialise the device ready for measurements to be taken.
 */
void init_BME280(void)
{
	uint8_t id;
	id = BME280_read_byte(CHIP_ID_REG);

	if (id == 0x60)
	{
		BME280_read_comp_data();
	}
	else
	{
		// Throw ID error here if required. 
	}

	BME280_write_byte(CTRL_HUM_REG, OVERSAMPLE_x1);
	BME280_write_byte(CONFIG_REG, 0b10100000);
	// oversample x1 temp, pressure off, forced mode
	BME280_write_byte(CTRL_MEAS_REG, 0b00100001);

	BME280_read_comp_data();
	BME280_get_raw_temp_val();
	BME280_get_raw_hum_val();
}


/*
 * @brief Reads in all compensation data from the device and stores it in a
 * buffer.
 */
void BME280_read_comp_data(void)
{
	signed short h_lsb;
	signed short h_msb;

	dig_T1 = BME280_read_word_unsigned(0x88);
	dig_T2 = BME280_read_word_signed(0x8A);
	dig_T3 = BME280_read_word_signed(0x8C);
/*
	dig_P1 = BME280_read_word_unsigned_short(0x8E);
	dig_P2 = BME280_read_word_signed_short(0x90);
	dig_P3 = BME280_read_word_signed_short(0x92);
	dig_P4 = BME280_read_word_signed_short(0x94);
	dig_P5 = BME280_read_word_signed_short(0x96);
	dig_P6 = BME280_read_word_signed_short(0x98);
	dig_P7 = BME280_read_word_signed_short(0x9A);
	dig_P8 = BME280_read_word_signed_short(0x9C);
	dig_P9 = BME280_read_word_signed_short(0x9E);
*/
	dig_H1 = BME280_read_unsigned_char(0xA1);
	dig_H2 = BME280_read_word_signed_short(0xE1);
	dig_H3 = BME280_read_unsigned_char(0xE3);

	h_msb = BME280_read_signed_char(0xE4);
	h_lsb = BME280_read_signed_char(0xE5);
	h_lsb &= 0b00001111;
	dig_H4 = h_lsb;
	dig_H4 |= (h_msb << 4);

	h_msb = BME280_read_signed_char(0xE6);
	h_lsb = BME280_read_signed_char(0xE5);
	h_lsb &= 0b11110000;
	dig_H5 = (h_lsb >> 4);
	dig_H5 |= (h_msb << 4);

	dig_H6 = BME280_read_signed_char(0xE7);
}

void BME280_get_raw_temp_val(void)
{
	uint32_t temp_msb;
	uint32_t temp_lsb;
	uint32_t temp_xlsb;

	i2cStart();
	i2cSend(BME280_ADDRESS_W);
	i2cSend(0xFA);
	i2cStart();
	i2cSend(BME280_ADDRESS_R);
	temp_msb = i2cReadAck();
	temp_lsb = i2cReadAck();
	temp_xlsb = i2cReadNoAck();
	i2cStop();

	raw_temp_adc = temp_msb << 12;
	raw_temp_adc |= temp_lsb << 4;
	raw_temp_adc |= temp_xlsb >> 4;
}

void BME280_get_raw_hum_val(void)
{
	uint16_t hum_msb;
	uint16_t hum_lsb;

	i2cStart();
	i2cSend(BME280_ADDRESS_W);
	i2cSend(0xFD);
	i2cStart();
	i2cSend(BME280_ADDRESS_R);
	hum_msb = i2cReadAck();
	hum_lsb = i2cReadNoAck();
	i2cStop();

	raw_hum_adc = hum_msb << 8;
	raw_hum_adc |= hum_lsb;
}

void BME280_get_readings(void)
{
	BME280_write_byte(CTRL_MEAS_REG, 0b00100001); // oversample x1 temp, pressure off, forced mode
	_delay_ms(50); // replace with status check later
	BME280_get_raw_temp_val();
	BME280_get_raw_hum_val();

	temp = (BME280_compensate_temp(raw_temp_adc)/100);
	humidity = (BME280_compensate_humidity(raw_hum_adc)/1024);
}
//######################################################################################################################//
// 												Generic functions for I/O ctrl											//
//######################################################################################################################//

void BME280_write_byte(uint8_t reg, uint8_t byte) // Writes a single byte to specified register
{
	i2cStart();
	i2cSend(BME280_ADDRESS_W);
	i2cSend(reg);
	i2cSend(byte);
	i2cStop();
}

uint8_t BME280_read_byte(uint8_t reg) // Reads a single byte from specified register
{
	uint8_t byte;

	i2cStart();
	i2cSend(BME280_ADDRESS_W);
	i2cSend(reg);
	i2cStart();
	i2cSend(BME280_ADDRESS_R);
	byte = i2cReadNoAck();
	i2cStop();
	return byte;
}

void BME280_burst_read(uint8_t start_address, uint8_t length) // Reads a whole section of memory addresses
{
	i2cStart();
	i2cSend(BME280_ADDRESS_W);
	i2cSend(start_address);
	i2cStart();
	i2cSend(BME280_ADDRESS_R);

	int i;
	for (i = 0; i < (length - 1); ++i)
	{
		BME280_read_buffer[i] = i2cReadAck();
	}
	BME280_read_buffer[i] = i2cReadNoAck();

	i2cStop();
}

unsigned short BME280_read_word_unsigned_short(uint8_t start_address)
{
	unsigned short msb;
	unsigned short lsb;
	unsigned short word;

	i2cStart();
	i2cSend(BME280_ADDRESS_W);
	i2cSend(start_address);
	i2cStart();
	i2cSend(BME280_ADDRESS_R);

	lsb = i2cReadAck();
	msb = i2cReadNoAck();
	i2cStop();

	word = (msb << 8);
	word |= lsb;
	return word;
}

signed short BME280_read_word_signed_short(uint8_t start_address)
{
	signed short msb;
	signed short lsb;
	signed short word;

	i2cStart();
	i2cSend(BME280_ADDRESS_W);
	i2cSend(start_address);
	i2cStart();
	i2cSend(BME280_ADDRESS_R);

	lsb = i2cReadAck();
	msb = i2cReadNoAck();
	i2cStop();

	word = (msb << 8);
	word |= lsb;
	return word;
}

unsigned char BME280_read_unsigned_char(uint8_t start_address)
{
	unsigned char byte;

	i2cStart();
	i2cSend(BME280_ADDRESS_W);
	i2cSend(start_address);
	i2cStart();
	i2cSend(BME280_ADDRESS_R);

	byte = i2cReadNoAck();
	i2cStop();

	return byte;
}

signed char BME280_read_signed_char(uint8_t start_address)
{
	signed char byte;

	i2cStart();
	i2cSend(BME280_ADDRESS_W);
	i2cSend(start_address);
	i2cStart();
	i2cSend(BME280_ADDRESS_R);

	byte = i2cReadNoAck();
	i2cStop();

	return byte;
}

//######################################################################################################################//
// 						Compensation formulae for converting raw ADC values into unit measurements						//
//######################################################################################################################//

// Returns temperature in DegC, resolution is 0.01 DegC. Output value of "5123" equals 51.23 DegC.
// t_fine carries fine temperature as global value

int32_t t_fine; // (Signed) Fine temperature value to be carried over to pressure and humidity compensation formulae.

int32_t BME280_compensate_temp(int32_t adc_T)
{
	int32_t var1, var2, T;
	var1 = (((adc_T >> 3) - ((int32_t)dig_T1 << 1)) * ((int32_t)dig_T2)) >> 11;
	var2 = (((((adc_T >> 4) - ((int32_t)dig_T1)) * ((adc_T >> 4) - ((int32_t)dig_T1))) >> 12) * ((int32_t)dig_T3)) >> 14;
	t_fine = var1 + var2;
	T = (t_fine * 5 + 128) >> 8;
	return T;
}

// Returns pressure in Pa as unsigned 32 bit integer. Output value of "96386" equals 96386 Pa = 963.86 hPa
/*
int32_t BME280_compensate_pressure(int32_t adc_P)
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
*/

// Returns humidity in %RH as unsigned 32 bit integer in Q22.10 format (22 integer and 10 fractional bits).
// Output value of "47445" represents 47445/1024 = 46.333 %RH

uint32_t BME280_compensate_humidity(int32_t adc_H)
{
	int32_t v_x1_u32r;

	v_x1_u32r = (t_fine - (76800));

	v_x1_u32r = (((((adc_H << 14) - (((int32_t)dig_H4) << 20) - (((int32_t)dig_H5) * v_x1_u32r)) + (16384)) >> 15) * (((((((v_x1_u32r *
	((int32_t)dig_H6)) >> 10) * (((v_x1_u32r * ((int32_t)dig_H3)) >> 11) + (32768))) >> 10) + (2097152)) * ((int32_t)dig_H2) + 8192) >> 14));

	v_x1_u32r = (v_x1_u32r - (((((v_x1_u32r >> 15) * (v_x1_u32r >> 15)) >> 7) * ((int32_t)dig_H1)) >> 4));
	v_x1_u32r = (v_x1_u32r < 0 ? 0 : v_x1_u32r);
	v_x1_u32r = (v_x1_u32r > 419430400 ? 419430400 : v_x1_u32r);
	return (v_x1_u32r>>12);
}

