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
 * @file log_system.h
 * @ingroup bme280
 * @author Jason Duffy
 * @date 1st March 2022
 * @brief Driver file providing logging functionality over USART, to print
 * debug messages and values to a teminal program on your PC. 
 * @bug No known bugs. 
 */

#ifndef LOG_SYSTEM_DOT_H
#define LOG_SYSTEM_DOT_H

/**
 * Enumerated constants for the type of message to be logged.
 */
typedef enum
{
    NONE,
    ERROR,
    WARNING,
    INFO,
    DEBUG,
    VERBOSE_DEBUG
} log_type_t;


/**
 * Enumerated constants to specify the output format of numerical values.
 */
typedef enum name
{
    DECIMAL,
    HEXADECIMAL,
    BINARY    
} format_type_t;


/**
 * Config object, to be instantiated in each file the log system is to be used,
 * then pass it's address into the functions with names beginning with "log".
 * p_system_tag is a string, and is used for the logsystem to report which file
 * or subsystem the message came from, e.g. "Main".
 * file_log_level is the maximum level you'd like logging output for a
 * particular file.
 */
typedef struct
{
    const char *p_system_tag;
    log_type_t file_log_level;
}log_system_config_t;


/**
 * Initialisation routine - call this function once at startup before using
 * other functions. Log system will then be turned on by default - call
 * log_global_off() if you do not wish it to be.
 */
void init_log_system(void);


/**
 * Sends only the system tag, log level and message string.
 * @param p_config is a pointer to the log_system config object. Instantiate
 * the config object at the head of each file where logging is required and
 * pass it's address into this function.
 * @param level is the level status of the log message - see log_type_t for
 * available options.
 * @param msg is the message to be logged, enclose it in "" quotation marks.
 */
void log_message(log_system_config_t *p_config,
                 log_type_t level,
                 const char *msg);


/**
 * Sends a string, followed by an 8 bit unsigned value.
 * @param p_config is a pointer to the log_system config object. Instantiate
 * the config object at the head of each file where logging is required and
 * pass it's address into this function.
 * @param level is the level status of the log message - see log_type_t for
 * available options.
 * @param msg is the message to be logged, enclose it in "" quotation marks.
 * @param val is the numerical value to be logged - Acceptable values 0 to 255.
 * @param format is the desired output format of val - see format_type_t for
 * avilable options. 
 */
void log_message_with_8bit_unsigned_val(log_system_config_t *p_config,
                                        log_type_t level,
                                        const char *msg,
                                        uint8_t val,
                                        format_type_t format);


/**
 * Sends a string, followed by an 8 bit value.
 * @param p_config is a pointer to the log_system config object. Instantiate
 * the config object at the head of each file where logging is required and
 * pass it's address into this function.
 * @param level is the level status of the log message - see log_type_t for
 * available options.
 * @param msg is the message to be logged, enclose it in "" quotation marks.
 * @param val is the numerical value to be logged - Acceptable values -128 to 127.
 * @param format is the desired output format of val - see format_type_t for
 * avilable options. 
 */
void log_message_with_8bit_signed_val(log_system_config_t *p_config,
                                      log_type_t level,
                                      const char *msg,
                                      int8_t val,
                                      format_type_t format);


/**
 * Sends a string, followed by a 16 bit value.
 * @param p_config is a pointer to the log_system config object. Instantiate
 * the config object at the head of each file where logging is required and
 * pass it's address into this function.
 * @param level is the level status of the log message - see log_type_t for
 * available options.
 * @param msg is the message to be logged, enclose it in "" quotation marks.
 * @param val is the numerical value to be logged - Acceptable values 0 -
 * 65,535.
 * @param format is the desired output format of val - see format_type_t for
 * avilable options. 
 */
void log_message_with_16bit_unsigned_val(log_system_config_t *p_config,
                                         log_type_t level,
                                         const char *msg,
                                         uint16_t val,
                                         format_type_t format);


/**
 * Sends a string, followed by a 16 bit value.
 * @param p_config is a pointer to the log_system config object. Instantiate
 * the config object at the head of each file where logging is required and
 * pass it's address into this function.
 * @param level is the level status of the log message - see log_type_t for
 * available options.
 * @param msg is the message to be logged, enclose it in "" quotation marks.
 * @param val is the numerical value to be logged - Acceptable values -32,768
 * to 32,767.
 * @param format is the desired output format of val - see format_type_t for
 * avilable options. 
 */
void log_message_with_16bit_signed_val(log_system_config_t *p_config,
                                       log_type_t level,
                                       const char *msg,
                                       int16_t val,
                                       format_type_t format);


// Temporary ptototype to make something work in the short term. 
void log_message_with_16bit_unsigned_dec_val(log_system_config_t *p_config,
                              log_type_t level,
                              const char *msg,
                              uint16_t val);


/**
 * Sends a string, followed by a 32 bit value.
 * @param p_config is a pointer to the log_system config object. Instantiate
 * the config object at the head of each file where logging is required and
 * pass it's address into this function.
 * @param level is the level status of the log message - see log_type_t for
 * available options.
 * @param msg is the message to be logged, enclose it in "" quotation marks.
 * @param val is the numerical value to be logged - Acceptable values 0 -
 * 4,294,967,295.
 * @param format is the desired output format of val - see format_type_t for
 * avilable options. 
 */
void log_message_with_32bit_unsigned_val(log_system_config_t *p_config,
                                            log_type_t level,
                                            const char *msg,
                                            uint32_t val,
                                            format_type_t format);


/**
 * Sends a string, followed by a 32 bit value.
 * @param p_config is a pointer to the log_system config object. Instantiate
 * the config object at the head of each file where logging is required and
 * pass it's address into this function.
 * @param level is the level status of the log message - see log_type_t for
 * available options.
 * @param msg is the message to be logged, enclose it in "" quotation marks.
 * @param val is the numerical value to be logged - Acceptable values 0 -
 * 4,294,967,295.
 * @param format is the desired output format of val - see format_type_t for
 * avilable options. 
 */
void log_message_with_32bit_signed_val(log_system_config_t *p_config,
                                           log_type_t level,
                                           const char *msg,
                                           int32_t val,
                                           format_type_t format);


/**
 * Sends a string, followed by a 64 bit value.
 * @param p_config is a pointer to the log_system config object. Instantiate
 * the config object at the head of each file where logging is required and
 * pass it's address into this function.
 * @param level is the level status of the log message - see log_type_t for
 * available options.
 * @param msg is the message to be logged, enclose it in "" quotation marks.
 * @param val is the numerical value to be logged - Acceptable values 0 -
 * (1.8446744e+19 - 1).
 * @param format is the desired output format of val - see format_type_t for
 * avilable options. 
 */
void log_message_with_64bit_unsigned_dec_val(log_system_config_t *p_config,
                                            log_type_t level,
                                            const char *msg,
                                            uint64_t val,
                                            format_type_t format);


/**
 * Sends a string, followed by a 64 bit value.
 * @param p_config is a pointer to the log_system config object. Instantiate
 * the config object at the head of each file where logging is required and
 * pass it's address into this function.
 * @param level is the level status of the log message - see log_type_t for
 * available options.
 * @param msg is the message to be logged, enclose it in "" quotation marks.
 * @param val is the numerical value to be logged - Acceptable values 0 -
 * (1.8446744e+19 - 1).
 * @param format is the desired output format of val - see format_type_t for
 * avilable options. 
 */
void log_message_with_64bit_unsigned_dec_val(log_system_config_t *p_config,
                                            log_type_t level,
                                            const char *msg,
                                            uint64_t val,
                                            format_type_t format);




/**
 * Sets maximum output level of logging required, to be used at file scope.
 * @param p_config is a pointer to the log_system config object. Instantiate
 * the config object at the head of each file where logging is required and
 * pass it's address into this function.
 * @param level is the maximum level required - see log_type_t for available
 * options.
 */
void log_set_file_max_output_level(log_system_config_t *p_config,
                                   log_type_t level);


/**
 * Sets maximum output level of logging required, has global effect.
 * @param level is the maximum level required - see log_type_t for available
 * options.
 */
void log_set_global_max_output_level(log_type_t level);


/**
 * Turns logging system on globally.
 */
void log_global_on(void);


/**
 * Turns logging system off globally.
 */
void log_global_off(void);


#endif // LOG_SYSTEM_DOT_H


/*** end of file ***/
