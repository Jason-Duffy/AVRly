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

/*
 * @file log_system.c
 * @ingroup ccs811
 * @author Jason Duffy
 * @date 15th March 2022
 * @brief Driver file providing logging functionality over USART, to print
 * debug messages and values to a teminal program on your PC. 
 * @bug No known bugs. 
 * @see
 */

#include <stdbool.h>

#include "usart.h"
#include "log_system.h"

static const char *p_system_tag = "log_system";

static bool log_system_enabled = false;

// Forward declaration
void print_tag_and_log_level(const char *p_tag, enum eLogLevel level);

// Initialisation routine
void init_log_system(void)
{
  init_usart();
  log_global_on();
  log_message(p_system_tag, INFO, "Log system initialised");
};

// Sends only a string message
void log_message(const char *p_tag, enum eLogLevel level, const char *msg)
{
  print_tag_and_log_level(p_tag, level);
  print_string(msg);
}

// Sends a string, followed by an integer (3 ASCII digits)
void log_message_with_dec_val(const char *p_tag, enum eLogLevel level, const char *msg, uint8_t val)
{
  print_tag_and_log_level(p_tag, level);
  print_string(msg);
  print_string(" ");
  print_byte(val);
}

// Sends a string, followed by an integer (5 ASCII digits)
void log_message_with_16bit_dec_val(const char *p_tag, enum eLogLevel level, const char *msg, uint16_t val)
{
  print_tag_and_log_level(p_tag, level);
  print_string(msg);
  print_string(" ");
  print_word(val);
}

// Sends a string, followed by a binary byte (in 1's and 0's)
void log_message_with_bin_val(const char *p_tag, enum eLogLevel level, const char *msg, uint8_t val)
{
  print_tag_and_log_level(p_tag, level);
  print_string(msg);
  print_string(" ");
  print_binary_byte(val);
}

// Sends a string, followed by an integer
void log_message_with_hex_val(const char *p_tag, enum eLogLevel level, const char *msg, uint8_t val)
{
  print_tag_and_log_level(p_tag, level);
  print_string(msg);
  print_string(" ");
  print_hex_byte(val);
}

// Sets level of logging required
void log_set_output_level(const char *p_tag, enum eLogLevel level)
{

}

// Turns logging system on globally
void log_global_on(void)
{
  log_system_enabled = true;
}

// Turns logging system off globally
void log_global_off(void)
{
  log_system_enabled = false;
}

// Utility function to print labels over serial. 
void print_tag_and_log_level(const char *p_tag, enum eLogLevel level)
{
  if (level == NONE)
  {

  }
  print_string("\n");
  print_string(p_tag);

  if (level == INFO)
  {
    print_string(", INFO: ");
  }

  else if (level == DEBUG)
  {
    print_string(", DEBUG: ");
  }

  else if (level == VERBOSE_DEBUG)
  {
    print_string(", VERBOSE_DEBUG: ");
  }

  else if (level == WARNING)
  {
    print_string(", WARNING: ");
  }

  else if (level == ERROR)
  {
    print_string(", ERROR: ");
  }

  // TODO: Throw exception here to be caught at compile time
  else
  {
    print_string(", INVALID_LOG_LEVEL: ");
  }
}

/*** end of file ***/
