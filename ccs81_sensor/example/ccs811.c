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
 * @file ccs81.c
 * @author Jason Duffy
 * @date 4th March 2022
 * @brief Driver for the CCS81 .
 * @bug No known bugs. 
 * 
 * This file provides the basic low-level functionality for CCS81 based air
 * quality sensor module CJMCU-811 which features an on-board MCU to interface
 * with.
 * 
 * This driver was written using the datasheet for the ams CCS81 gas sensor,
 * which can be found at the link below.
 * @see
 * https://pdf1.alldatasheet.com/datasheet-pdf/view/1047395/AMSCO/CCS811.html
 */


#include "ccs811.h"
#include "log_system.h"

//static const char *p_system_tag = "CCS81";

// 7 bit address of i2c device followwed by write bit (0) or read bit (1)
#define CCS811_ADDRESS_W		0xB4
#define CCS811_ADDRESS_R		0xB5
	
// Register mailbox ID's	
#define STATUS					0x00 // Read
#define MEAS_MODE				0x01 // Read/Write
#define ALG_RESULT_DATA			0x02 // Read
#define RAW_DATA 				0x03 // Read
#define ENV_DATA				0x05 // Write
#define THRESHOLDS 				0x10 // Write
#define BASELINE 				0x11 // Read/Write
#define HW_ID	 				0x20 // Read - should return 0x81 
#define HW_VERSION				0x21 // Read
#define FW_BOOT_VERSION			0x23 // Read
#define FW_APP_VERSION			0x24 // Read
#define INTERNAL_STATE			0xA0 // Read
#define ERROR_ID	 			0xE0 // Read
#define SW_RESET 				0xFF // Write

	
// Register sizes (BYTES)
#define STATUS_SIZE				1
#define MEAS_MODE_SIZE			1
#define ALG_RESULT_DATA_SIZE	8
#define RAW_DATA_SIZE 			2
#define ENV_DATA_SIZE			4
#define THRESHOLDS_SIZE 		5
#define BASELINE_SIZE 			2
#define HW_ID_SIZE				1
#define HW_VERSION_SIZE			1
#define FW_BOOT_VERSION_SIZE	2
#define FW_APP_VERSION_SIZE		2
#define INTERNAL_STATE_SIZE		1
#define ERROR_ID_SIZE			1
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
#define MSG_INVALID				0


// Status register (bit numbers)
#define FW_MODE					7
#define APP_ERASE				6
#define APP_VERIFY				5
#define APP_VALID				4
#define DATA_READY				3
#define ERROR 					0

uint8_t error;
uint8_t write_buffer[8];
uint8_t read_buffer[10];

/**
 * These values would be provided by another sensor and module - need to be
 * made otional.
 */ 
uint8_t humidity;
uint8_t temp;

// Forward declarations
uint8_t ccs811_read_byte(uint8_t register);
void ccs811_burst_read(uint8_t register, uint8_t length);
uint16_t ccs811_read_word(uint8_t register);
void ccs811_write_byte(uint8_t register, uint8_t byte);



uint8_t init_ccs811(ccs811_config_t *p_config)
{
	init_i2c();
	uint8_t mode = 0;
	uint8_t ret = 0;
	uint8_t status = 0;
	if (ccs811_read_byte(HW_ID) == 0x81)
	{
		status = ccs811_read_byte(STATUS);
		if (bit_is_set(status, APP_VALID))
		{
			i2cStart();
			i2cSend(CCS811_ADDRESS_W);
			i2cSend(APP_START);
			i2cStop();
			_delay_ms(100);

			mode = ccs811_read_byte(MEAS_MODE);

			while (mode == 0)
			{
				ccs811_write_byte(MEAS_MODE, 0b00010000);
				_delay_ms(500);
				mode = ccs811_read_byte(MEAS_MODE);
			}
		}
		else
		{
			ret = 1; // Error - app invalid
		}
	}
	else
	{
		ret = 2; // ccs81 ID failed
	}
	return ret;
}

uint8_t ccs811_get_status(void)
{
	uint8_t status = ccs811_read_byte(STATUS);
	return status;
}

bool ccs811_data_ready_check(void)
{
	bool ret = false;
	uint8_t status = ccs811_get_status();
	if (bit_is_set(status, DATA_READY))
	{
		ret =  true;
	}
	return ret;
}

uint16_t ccs811_get_alg_result_data(void)
{
	uint16_t co2 = 0;
	if (ccs811_data_ready_check())
	{
		co2 = ccs811_read_word(ALG_RESULT_DATA);
	}
	return co2;
}

void ccs811_update_env_data(void)
{
	uint8_t lsb = 0;

	i2cStart();
	i2cSend(CCS811_ADDRESS_W);
	i2cSend(ENV_DATA);
	i2cSend(humidity << 1);
	i2cSend(lsb);
	i2cSend(((temp + 25) << 1));
	i2cSend(lsb);
	i2cStop();
}

void ccs811_write_byte(uint8_t _register, uint8_t byte)
{
	i2cStart();
	i2cSend(CCS811_ADDRESS_W);
	i2cSend(_register);
	i2cSend(byte);
	i2cStop();
}

uint8_t ccs811_read_byte(uint8_t _register)
{
	uint8_t byte;

	i2cStart();
	i2cSend(CCS811_ADDRESS_W);
	i2cSend(_register);
	i2cStart();
	i2cSend(CCS811_ADDRESS_R);
	byte = i2cReadNoAck();
	i2cStop();
	return byte;
}

void ccs811_burst_read(uint8_t _register, uint8_t length)
{
	i2cStart();
	i2cSend(CCS811_ADDRESS_W);
	i2cSend(_register);
	i2cStart();
	i2cSend(CCS811_ADDRESS_R);

	for (uint8_t i = 0; i < length; ++i)
	{
		read_buffer[i] = i2cReadAck();
	}
	i2cStop();
}

uint16_t ccs811_read_word(uint8_t _register)
{
	uint16_t msb;
	uint16_t byte;

	i2cStart();
	i2cSend(CCS811_ADDRESS_W);
	i2cSend(_register);
	i2cStart();
	i2cSend(CCS811_ADDRESS_R);

	msb = i2cReadAck();
	byte = i2cReadNoAck();
	byte |= (msb << 8);

	return byte;
}


/*** end of file ***/
