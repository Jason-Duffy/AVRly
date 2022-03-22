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
 * \ingroup ccs811
 * @author Jason Duffy
 * @date 4th March 2022
 * @brief Driver for the CCS811 gas sensor .
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


#ifndef CCS_EIGHT_ONE_ONE_DOT_H
#define CCS_EIGHT_ONE_ONE_DOT_H

#include <stdbool.h>
#include <stdint.h>

/**
 * Drive modes 0 to 3. Mode 4 has been omitted as it does not appear to be
 * particularly useful (only RAW_DATA may be used in mode 4).
 */
typedef enum
{
    drive_mode_idle = 0U,
    drive_mode_1sec = 1U,
    drive_mode_10sec = 2U,
    drive_mode_60sec = 3U,
}ccs811_drive_mode_t;


/**
 * Config object, to be instantiated and values assigned to members before
 * passing the object address into the function init_ccs811().
 * If wake_pin_enabled is set to true, WAKE must be connected to a GPIO pin and
 * defined in pin_defines.h. Otherwise, tie the WAKE pin on the CCS811 to
 * ground. If interrupt_dataready is set to true, INT pin should be connected
 * to a GPIO and defined in pindefines.h. That pin will be driven low when new
 * data is ready. If both interrupt_dataready AND interrupt_threshold are set
 * to true, the INT pin is driven low when ALG_RESULT_DATA crosses one of the
 * thresholds set in the THRESHOLDS register. 
 */
typedef struct
{
    ccs811_drive_mode_t drive_mode; // Sets mode in which readings will be taken. 
    bool wake_pin_enabled; // true = enabled, false = disabled. 
    bool interrupt_dataready; // true = enabled, false = disabled.
    bool interrupt_threshold; // true = enabled, false = disabled. 
}ccs811_config_t;


/**
 * Initialisation routine (run once at startup).
 * This function is to be called before any other functions in this file can be
 * called. Instantiate the ccs811_config_t object first, then pass it's address
 * into init_ccs811() to make config data available at file scope. 
 * @param p_config is a pointer to the ccs811_config_t object.
 * @return An error code is returned as an unsigned 8 bit integer. 
 */
uint8_t init_ccs811(ccs811_config_t *p_config);


/**
 * Read eCO2 (equivalent carbon dioxide) level from sensor. Once the data_ready
 * flag is set, this function can be called.
 * @return eCO2 level in ppm is returned, ranging from (400 - 32768ppm). 
 */
uint16_t ccs811_get_eco2_level(void);


/**
 * Read eTVOC (equivalent total volatile organic compounds) level from sensor.
 * Once the data_ready flag is set, this function can be called.
 * @return eTVOC level in ppb is returned, ranging from (0 - 32768ppb). 
 */
uint16_t ccs811_get_etvoc_level(void);


/**
 * Perform a read operation on all 8 bytes of ALG_RESULT_REGISTER. The data is
 * stored in the read_buffer[] array, and can be extracted using the register
 * size definitions in the source file. 
 */
void ccs811_get_alg_result_data(void);


/**
 * Read the status register and check if the data ready flag is set. Use this
 * function to poll the data ready flag and call the getter functions above
 * only when a new value is ready. 
 * @return A boolean value of true is returned if flag is set, otherwise false
 * is returned. 
 */
bool ccs811_data_ready_check(void);


/**
 * (Optional) Write environmental data from another sensor to the CCS811. The 
 * sensor has the capability to use humidity and temperature data in a
 * compensation formula to imporve the accuracy of it's readings. 
 * @param uint8_t humidity is the Relative Humidity % passed in as an integer. 
 * @param uint8_t temp is the temperature in degrees Celcius.
 */
void ccs811_update_env_data(uint8_t humidity, uint8_t temp);


/**
 * For error handling/logging. If the error flag is set on the status register,
 * call this function to turn the error code into a string message.
 * @param char* pointer to the first element of the string is returned. 
 */
char* ccs811_error_to_string(void);



#endif // CCS_EIGHT_ONE_ONE_DOT_H


/*** end of file ***/
