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
 * @file ccs811.h
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


#ifndef CCS_EIGHT_ONE_ONE_DOT_H
#define CCS_EIGHT_ONE_ONE_DOT_H

#include <stdbool.h>
#include <stdint.h>
#include <util/delay.h>
#include "i2c.h"


// Drive modes
#define DRIVE_MODE_IDLE 		0x0
#define DRIVE_MODE_1SEC 		0x10
#define DRIVE_MODE_10SEC 		0x20
#define DRIVE_MODE_60SEC 		0x30
#define INTERRUPT_DRIVEN 		0x8
#define THRESHOLDS_ENABLED 		0x4


typedef enum
{  
    drive_mode_idle = 0x0U,
    drive_mode_1sec = 0x10U,
    drive_mode_10sec = 0x20U,
    drive_mode_60sec = 0x30U,
    interrupt_driven = 0x8U,
    thresholds_enabled = 0x4U,
}ccs811_drive_mode_t;

typedef struct
{
    ccs811_drive_mode_t mode;
}ccs811_config_t;


//TODO: scope these variables appropriately
extern uint8_t write_buffer[8];
extern uint8_t read_buffer[10];
extern uint8_t error;
extern uint8_t hw_id;
extern uint8_t mode;


uint8_t init_ccs811(ccs811_config_t *p_config);

uint8_t ccs811_get_status(void);

uint16_t ccs811_get_alg_result_data(void);

bool ccs811_data_ready_check(void);

void ccs811_update_env_data(void);


#endif // CCS_EIGHT_ONE_ONE_DOT_H


/*** end of file ***/
