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

#define ARRAY_SIZE    20
#define INVALID_TYPE  9


/**
 * File/System tag with file level scope. This is used for the log system to
 * report which file the message came from. 
 */
static const char *p_system_tag = "log_system";


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
static log_type_t global_max_output_level = ERROR;


char *p_tag_array[20];
log_type_t log_type_array[20];


// Forward declaration - private helper functions. 
void print_tag_and_log_level(const char *p_tag, log_type_t level);
log_type_t get_file_max_level_from_tag(void);


/*
 * Initialisation routine - call this function once at startup before using
 * other functions. Log system will then be turned on by default - call
 * log_global_off() if you do not wish it to be.
 */
void init_log_system(void)
{
  init_usart();

  // Initialise array with highest debug output level as default. 
  for (uint8_t index = 0; index < ARRAY_SIZE; ++index)
  {
    log_type_array[index] = VERBOSE_DEBUG;
  }

  log_global_on();
  log_message(p_system_tag, INFO, "Log system initialised");
};


/*
 * Sends only the system tag, log level and message string.
 * @param p_tag is the calling file's tag - declare and define as a const char
 * at the top of the file and pass in a pointer to it. 
 * @param level is the level status of the log message - see log_type_t for
 * available options.
 * @param msg is the message to be logged, enclose it in "" quotation marks.
 */
void log_message(const char *p_tag, log_type_t level, const char *msg)
{
  if (log_system_enabled)
  {
    if (level <= global_max_output_level)
    {
      print_tag_and_log_level(p_tag, level);
      usart_print_string(msg);
    }
  }
}


/*
 * Sends a string, followed by an 8 bit value in decimal format.
 * @param p_tag is the calling file's tag - declare and define as a const char
 * at the top of the file and pass in a pointer to it. 
 * @param level is the level status of the log message - see log_type_t for
 * available options.
 * @param msg is the message to be logged, enclose it in "" quotation marks.
 * @param val is the numerical value to be logged - Acceptable values 0 - 255.
 */
void log_message_with_dec_val(const char *p_tag,
                                 log_type_t level,
                                 const char *msg,
                                 uint8_t val)
{
  if (log_system_enabled)
  {
    print_tag_and_log_level(p_tag, level);
    usart_print_string(msg);
    usart_print_string(" ");
    usart_print_byte(val);
  }
}


/*
 * Sends a string, followed by an 8 bit value in binary format.
 * @param p_tag is the calling file's tag - declare and define as a const char
 * at the top of the file and pass in a pointer to it. 
 * @param level is the level status of the log message - see log_type_t for
 * available options.
 * @param msg is the message to be logged, enclose it in "" quotation marks.
 * @param val is the numerical value to be logged - Acceptable values 0 - 255.
 */
void log_message_with_bin_val(const char *p_tag,
                              log_type_t level,
                              const char *msg,
                              uint8_t val)
{
  if (log_system_enabled)
  {
    print_tag_and_log_level(p_tag, level);
    usart_print_string(msg);
    usart_print_string(" ");
    usart_print_binary_byte(val);
  }
}


/*
 * Sends a string, followed by an 8 bit value in hexadecimal format.
 * @param p_tag is the calling file's tag - declare and define as a const char
 * at the top of the file and pass in a pointer to it. 
 * @param level is the level status of the log message - see log_type_t for
 * available options.
 * @param msg is the message to be logged, enclose it in "" quotation marks.
 * @param val is the numerical value to be logged - Acceptable values 0 - 255.
 */
void log_message_with_hex_val(const char *p_tag,
                              log_type_t level,
                              const char *msg,
                              uint8_t val)
{
  if (log_system_enabled)
  {
    print_tag_and_log_level(p_tag, level);
    usart_print_string(msg);
    usart_print_string(" ");
    usart_print_hex_byte(val);
  }
}


/*
 * Sets maximum output level of logging required, to be used at file scope.
 * @param p_tag is the calling file's tag - declare and define as a const char
 * at the top of the file and pass in a pointer to it.
 * @param level is the maximum level required - see log_type_t for available
 * options.
 */
void log_set_file_max_output_level(const char *p_tag, log_type_t level)
{

}


/*
 * Sets maximum output level of logging required, has global effect (will
 * override file level settings).
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

  if (level == INFO)
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

  else if (level == WARNING)
  {
    usart_print_string(", WARNING: ");
  }

  else if (level == ERROR)
  {
    usart_print_string(", ERROR: ");
  }

  else
  {
    usart_print_string(", INVALID_LOG_LEVEL: ");
  }
}

log_type_t get_file_max_level_from_tag(const char *p_tag)
{
  char *p_compare;
  uint8_t index = 0;

  /*
   * Search the array til a match is found, use that index to return the
   * corresponding value in the log type array. 
   */
  while ((p_compare != p_tag) && (index < ARRAY_SIZE))
  {
    p_compare = p_tag_array[index];

    if (p_compare == p_tag)
    {
      return log_type_array[index];
    }
    ++index;
  }
  
  // If no match is found, return an error code.
  if ((p_compare != p_tag) && (index > ARRAY_SIZE))
  {
    return INVALID_TYPE;
  }
}

/*** end of file ***/
