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
 * @file bme280.h
 * @ingroup bme280
 * @author Jason Duffy
 * @date 22nd June 2022
 * @brief
 * @bug No known bugs.
 * @see
 */

#ifndef BME_TWO_EIGHTY_DOT_H
#define BME_TWO_EIGHTY_DOT_H

/*
 * Burst_read is from registers 0xF7 to 0xFE (temperature, pressure and
 * humidity. Pressure and temperature are read out in 20 bit unsigned format.
 * Humidity is read out in 16 bit unsigned format.
 */

#include <stdint.h>

/**
 * @brief Initialise the device ready for measurements to be taken.
 */
void init_BME280(void);


/**
 * @brief Fetches the latest temperature data from the sensor, compensates and
 * formats the data in degrees Celcius * 100.
 * @returns eg. A return value of 5123 = 51.23˚C (Degrees Celcius).
 */ 
int16_t bme280_get_temperature(void);


/**
 * @brief Fetches the latest humidity data from the sensor, compensates and
 * formats the data as %RH * 100.
 * @returns eg. A return value of 2852 = 28.50 %RH (Relative Humidity).
 */ 
uint16_t bme280_get_humidity(void);


/**
 * @brief Fetches the latest pressure data from the sensor, compensates and
 * formats the data as Pa * 100.
 * @returns eg. A return value of 96386 = 963.86 Pa (Pascals).
 */ 
uint16_t bme280_get_pressure(void);


#endif // BME_TWO_EIGHTY_DOT_H