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
 * \defgroup ccs811 CCS811 Gas Sensor
 */

/**
 * @file ccs811.c
 * \ingroup ccs811
 * @author Jason Duffy
 * @date 4th March 2022
 * @brief Driver for the CCS811 gas sensor.
 * @bug No known bugs. 
 * 
 * This file provides the basic low-level functionality for the CCS81 gas
 * sensor / air quality sensor. It was tested with the CJMCU-811 module which
 * provides pin breakout to THT for breadboard prototyping, and some peripheral
 * circuitry. The CCS811 eatures an on-board MCU to interface with, greatly
 * reducing the load on the host MCU. 
 * 
 * When the sensor is new, a burn-in period of 48hr is necessary for the
 * resistive elements to level out and make readings more accurate. The CCS81
 * controls the burn-in period, allowing eCO2 and eTVOC readings to be used
 * from first power-on after 60 minutes of operation in modes 1-3.
 * 
 * After early-life (Burn-In) use the conditioning period is the time required
 * to achieve good sensor stability before measuring VOCs after a long idle
 * period. After starting the application and calling init_ccs811(), run the
 * sensor for 20 minutes before accurate readings are generated. The
 * conditioning period must also be observed before writing to the BASELINE
 * register.
 * 
 * This driver was written using the datasheet for the ams CCS81 gas sensor,
 * which can be found at the link below.
 * @see
 * https://pdf1.alldatasheet.com/datasheet-pdf/view/1047395/AMSCO/CCS811.html
 */

#include <util/delay.h>
#include "ccs811.h"
#include "i2c.h"

// 7 bit address of i2c device followwed by write bit (0) or read bit (1)
#define CCS811_ADDRESS_W		0xB4
#define CCS811_ADDRESS_R		0xB5
	
// Register mailbox ID's	
#define STATUS_REG				0x00 // Read
#define MEAS_MODE_REG			0x01 // Read/Write
#define ALG_RESULT_DATA_REG		0x02 // Read
#define RAW_DATA_REG 			0x03 // Read
#define ENV_DATA_REG			0x05 // Write
#define THRESHOLDS_REG 			0x10 // Write
#define BASELINE_REG 			0x11 // Read/Write
#define HW_ID_REG	 			0x20 // Read - should return 0x81 
#define HW_VERSION_REG			0x21 // Read
#define FW_BOOT_VERSION_REG		0x23 // Read
#define FW_APP_VERSION_REG		0x24 // Read
#define INTERNAL_STATE_REG		0xA0 // Read
#define ERROR_ID_REG	 		0xE0 // Read
#define SW_RESET_REG 			0xFF // Write

// Register sizes (BYTES)
#define ALG_RESULT_DATA_SIZE	8
#define ETVOC_SIZE				4
#define RAW_DATA_SIZE 			2
#define ENV_DATA_SIZE			4
#define THRESHOLDS_SIZE 		5
#define BASELINE_SIZE 			2
#define FW_BOOT_VERSION_SIZE	2
#define FW_APP_VERSION_SIZE		2
#define SW_RESET_SIZE			4

// Command mailbox ID's
#define APP_START	 			0xF4 // Go from boot state to application mode
#define GPIO_WAKE 				0x5

// Error codes (bit numbers)
#define HEATER_SUPPLY			5
#define HEATER_FAULT			4
#define MAX_RESISTANCE			3
#define MEASMODE_INVALID		2
#define READ_REG_INVALID		1
#define WRITE_REG_INVALID		0

// Meas_mode register (bit numbers)
#define DRIVE_MODE_BITS			4
#define INT_DATARDY_BIT			3
#define INT_THRESH_BIT			2

// Status register (bit numbers)
#define FW_MODE_BIT				7
#define APP_ERASE_BIT			6
#define APP_VERIFY_BIT			5
#define APP_VALID_BIT			4
#define DATA_READY_BIT			3
#define ERROR_BIT 				0

#define BUS_SPEED_100KHZ		100000U
#define ATTEMPTS_MAX			10
#define CCS811_ID				0x81

static ccs811_config_t *p_config_global;

static uint8_t read_buffer[10];

// Forward declarations
uint8_t ccs811_read_byte(uint8_t reg);
void ccs811_burst_read(uint8_t reg, uint8_t length);
uint16_t ccs811_read_word(uint8_t reg);
void ccs811_write_byte(uint8_t reg, uint8_t byte);
uint8_t ccs811_get_status(void);



uint8_t init_ccs811(ccs811_config_t *p_config)
{
	p_config_global = p_config; // Make a copy of pointer with file scope. 
	uint8_t ret = 0; // For return value
	init_i2c(BUS_SPEED_100KHZ);
	if (ccs811_read_byte(HW_ID_REG) == CCS811_ID)
	{
		uint8_t status = ccs811_get_status();
		if (bit_is_set(status, APP_VALID_BIT))
		{
			i2c_start();
			i2c_send(CCS811_ADDRESS_W);
			i2c_send(APP_START);
			i2c_stop();
			_delay_ms(100);

			uint8_t byte = 0;
			byte |= (p_config_global->drive_mode << DRIVE_MODE_BITS);
			byte |= (p_config_global->interrupt_dataready << INT_DATARDY_BIT);
			byte |= (p_config_global->interrupt_threshold <<INT_THRESH_BIT);

			for (uint8_t count = 0; count < ATTEMPTS_MAX; ++count)
			{
				ccs811_write_byte(MEAS_MODE_REG, byte);
				_delay_ms(500);
				uint8_t mode = ccs811_read_byte(MEAS_MODE_REG);
				if (mode == byte)
				{
					break; // Success
				}
				if (count == (ATTEMPTS_MAX - 1))
				{
					ret = 3; // Max attempts reached
				}
			}
		}
		else
		{
			ret = 2; // Error - app invalid
		}
	}
	else
	{
		ret = 1; // ccs81 ID failed
	}
	return ret;
}


uint16_t ccs811_get_eco2_level(void)
{
	uint16_t data = ccs811_read_word(ALG_RESULT_DATA_REG);
	return data;
}


uint16_t ccs811_get_etvoc_level(void)
{
	uint8_t data = 0;
	ccs811_burst_read(ALG_RESULT_DATA_REG, ETVOC_SIZE);
	uint8_t msb = read_buffer[ETVOC_SIZE - 2];
	data = read_buffer[ETVOC_SIZE - 1];
	data |= (msb << 8);
	return data;
}


bool ccs811_data_ready_check(void)
{
	bool ret = false;
	uint8_t status = ccs811_get_status();
	if (bit_is_set(status, DATA_READY_BIT))
	{
		ret =  true;
	}
	return ret;
}

void ccs811_get_alg_result_data(void)
{
	ccs811_burst_read(ALG_RESULT_DATA_REG, ALG_RESULT_DATA_SIZE);
}

void ccs811_update_env_data(uint8_t humidity, uint8_t temp)
{
	uint8_t lsb = 0;

	i2c_start();
	i2c_send(CCS811_ADDRESS_W);
	i2c_send(ENV_DATA_REG);
	i2c_send(humidity << 1);
	i2c_send(lsb);
	i2c_send(((temp + 25) << 1));
	i2c_send(lsb);
	i2c_stop();
}


char* ccs811_error_to_string(void)
{
	char *msg;
	uint8_t error = ccs811_read_byte(ERROR_ID_REG);
	if (bit_is_set(error, HEATER_SUPPLY))
	{
		msg = "Heater Supply";
	}
	else if (bit_is_set(error, HEATER_FAULT))
	{
		msg = "Heater Fault";
	}
	else if (bit_is_set(error, MAX_RESISTANCE))
	{
		msg = "Max Resistance";
	}
	else if (bit_is_set(error, MEASMODE_INVALID))
	{
		msg = "Invalid Meas Mode";
	}
	else if (bit_is_set(error, READ_REG_INVALID))
	{
		msg = "Read Reg Invalid";
	}
	else if (bit_is_set(error, WRITE_REG_INVALID))
	{
		msg = "Write Reg Invalid";
	}
	else
	{
		msg = "Unknown Error";
	}
	return msg;
}


///////////////////////////////////////////////////////////////////////////////
//							Private Helper Functions						 //
///////////////////////////////////////////////////////////////////////////////

uint8_t ccs811_get_status(void)
{
	uint8_t status = ccs811_read_byte(STATUS_REG);
	return status;
}

void ccs811_write_byte(uint8_t reg, uint8_t byte)
{
	i2c_start();
	i2c_send(CCS811_ADDRESS_W);
	i2c_send(reg);
	i2c_send(byte);
	i2c_stop();
}

uint8_t ccs811_read_byte(uint8_t reg)
{
	uint8_t byte;

	i2c_start();
	i2c_send(CCS811_ADDRESS_W);
	i2c_send(reg);
	i2c_start();
	i2c_send(CCS811_ADDRESS_R);
	byte = i2c_read_no_ack();
	i2c_stop();
	return byte;
}

void ccs811_burst_read(uint8_t reg, uint8_t length)
{
	i2c_start();
	i2c_send(CCS811_ADDRESS_W);
	i2c_send(reg);
	i2c_start();
	i2c_send(CCS811_ADDRESS_R);

	for (uint8_t i = 0; i < length; ++i)
	{
		read_buffer[i] = i2c_read_ack();
	}
	i2c_stop();
}

uint16_t ccs811_read_word(uint8_t reg)
{
	uint16_t msb;
	uint16_t byte;

	i2c_start();
	i2c_send(CCS811_ADDRESS_W);
	i2c_send(reg);
	i2c_start();
	i2c_send(CCS811_ADDRESS_R);

	msb = i2c_read_ack();
	byte = i2c_read_no_ack();
	byte |= (msb << 8);

	return byte;
}


/*** end of file ***/
