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
 * @file log_system.c
 * @ingroup log_system
 * @author Jason Duffy
 * @date 1st March 2022
 * @brief Driver file providing logging functionality over USART, to print
 * debug messages and values to a teminal program on your PC. 
 * @bug No known bugs. 
 */

#include <stdbool.h>

#include "usart.h"
#include "log_system.h"


/**
 * Instantiation of log system config object, pass it's address into logging
 * functions. 
 */
log_system_config_t log_system_log =
{
  .p_system_tag = "Log_System",
  .file_log_level = INFO,
};


/**
 * Flag to determine whether logging output is turned on or off globally. The
 * flag itself however is at file scope only. 
 */
static bool log_system_enabled = false;


/**
 * Variable to store the preferred maximum level of logging with global effect.
 * Maximum level available by default. Call log_set_global_max_output_level()
 * to change this value.  
 */
static log_type_t global_max_output_level = VERBOSE_DEBUG;


// Forward declaration - private helper functions. 
void print_tag_and_log_level(const char *p_tag, log_type_t level);
bool log_message_preference_check(log_system_config_t *p_config,
                                  log_type_t level);


/*
 * Initialisation routine - call this function once at startup before using
 * other functions. Log system will then be turned on by default - call
 * log_global_off() if you do not wish it to be.
 */
void init_log_system(void)
{
  init_usart();
  log_global_on();
  log_message(&log_system_log, INFO, "Log system initialised");
};


/*
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
                 const char *msg)
{
  // If all test expressions evaluate true, log message.
  if (log_message_preference_check(p_config, level))
  {
    print_tag_and_log_level(p_config->p_system_tag, level);
    usart_print_string(msg);
   }
}


/*
 * Sends a string, followed by an 8 bit value in decimal format.
 * @param p_config is a pointer to the log_system config object. Instantiate
 * the config object at the head of each file where logging is required and
 * pass it's address into this function.
 * @param level is the level status of the log message - see log_type_t for
 * available options.
 * @param msg is the message to be logged, enclose it in "" quotation marks.
 * @param val is the numerical value to be logged - Acceptable values 0 - 255.
 */
void log_message_with_dec_val(log_system_config_t *p_config,
                                 log_type_t level,
                                 const char *msg,
                                 uint8_t val)
{
  // If all test expressions evaluate true, log message.
  if (log_message_preference_check(p_config, level))
  {
    print_tag_and_log_level(p_config->p_system_tag, level);
    usart_print_string(msg);
    usart_print_string(" ");
    usart_print_byte(val); 
  }
}


/*
 * Sends a string, followed by an 8 bit value in binary format.
 * @param p_config is a pointer to the log_system config object. Instantiate
 * the config object at the head of each file where logging is required and
 * pass it's address into this function.
 * @param level is the level status of the log message - see log_type_t for
 * available options.
 * @param msg is the message to be logged, enclose it in "" quotation marks.
 * @param val is the numerical value to be logged - Acceptable values 0 - 255.
 */
void log_message_with_bin_val(log_system_config_t *p_config,
                              log_type_t level,
                              const char *msg,
                              uint8_t val)
{
  // If all test expressions evaluate true, log message.
  if (log_message_preference_check(p_config, level))
  {
    print_tag_and_log_level(p_config->p_system_tag, level);
    usart_print_string(msg);
    usart_print_string(" ");
    usart_print_binary_byte(val);
  }
}


/*
 * Sends a string, followed by an 8 bit value in hexadecimal format.
 * @param p_config is a pointer to the log_system config object. Instantiate
 * the config object at the head of each file where logging is required and
 * pass it's address into this function.
 * @param level is the level status of the log message - see log_type_t for
 * available options.
 * @param msg is the message to be logged, enclose it in "" quotation marks.
 * @param val is the numerical value to be logged - Acceptable values 0 - 255.
 */
void log_message_with_hex_val(log_system_config_t *p_config,
                              log_type_t level,
                              const char *msg,
                              uint8_t val)
{
  // If all test expressions evaluate true, log message.
  if (log_message_preference_check(p_config, level))
  {
    print_tag_and_log_level(p_config->p_system_tag, level);
    usart_print_string(msg);
    usart_print_string(" ");
    usart_print_hex_byte(val);
  }
}


/*
 * Sets maximum output level of logging required, to be used at file scope.
 * @param p_config is a pointer to the log_system config object. Instantiate
 * the config object at the head of each file where logging is required and
 * pass it's address into this function.
 * @param level is the maximum level required - see log_type_t for available
 * options.
 */
void log_set_file_max_output_level(log_system_config_t *p_config,
                                   log_type_t level)
{
  p_config->file_log_level = level;
}


/*
 * Sets maximum output level of logging required, has global effect.
 * @param level is the maximum level required - see log_type_t for available
 * options.
 */
void log_set_global_max_output_level(log_type_t level)
{
  global_max_output_level = level;
}


/*
 * Turns logging system on globally.
 */
void log_global_on(void)
{
  log_system_enabled = true;
}


/*
 * Turns logging system off globally.
 */
void log_global_off(void)
{
  log_system_enabled = false;
}


// ------------------------------------------------------------------------- //
// ------------------------ Private Helper Functions ----------------------- //
// ------------------------------------------------------------------------- //

/**
 * Utility function to print labels over serial.
 */
void print_tag_and_log_level(const char *p_tag, log_type_t level)
{
  if (level == NONE)
  {

  }
  usart_print_string("\n");
  usart_print_string(p_tag);

  if (level == ERROR)
  {
    usart_print_string(", ERROR: ");
  }

  else if (level == WARNING)
  {
    usart_print_string(", WARNING: ");
  }

  else if (level == INFO)
  {
    usart_print_string(", INFO: ");
  }

  else if (level == DEBUG)
  {
    usart_print_string(", DEBUG: ");
  }

  else if (level == VERBOSE_DEBUG)
  {
    usart_print_string(", VERBOSE_DEBUG: ");
  }

  else
  {
    usart_print_string(", INVALID_LOG_LEVEL: ");
  }
}


/**
 * Utility function to test if the log message level meets the preferences set.
 */
bool log_message_preference_check(log_system_config_t *p_config,
                                  log_type_t level)
{
  // Test if log_system is enabled globally, if not then do nothing. 
  if (log_system_enabled)
  {
    // Test if the level of this log message meets global log preferences. 
    if (level <= global_max_output_level)
    {
      // Test if the level of this log message meets file level preferences.
      if (level <= p_config->file_log_level)
      {
        return true;
      }
    }
  }
  // If any of the above conditionals evaluate to false, return false. 
  return false;
}

/*** end of file ***/
