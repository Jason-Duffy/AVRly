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
 * @file log_system.h
 * \ingroup ccs811
 * @author Jason Duffy
 * @date 15th March 2022
 * @brief Driver file providing logging functionality over USART, to print
 * debug messages and values to a teminal program on your PC. 
 * @bug No known bugs. 
 * @see
 */

#ifndef LOG_SYSTEM_DOT_H
#define LOG_SYSTEM_DOT_H

enum eLogLevel {NONE, INFO, DEBUG, VERBOSE_DEBUG, WARNING, ERROR};

// Initialisation routine
void init_log_system(void);

// Sends only a string message
void log_message(const char *p_tag, enum eLogLevel level, const char *msg);

// Sends a string, followed by a value in decimal format
void log_message_with_dec_val(const char *p_tag, enum eLogLevel level, const char *msg, uint8_t val);

void log_message_with_16bit_dec_val(const char *p_tag, enum eLogLevel level, const char *msg, uint16_t val);

// Sends a string, followed by a value in binary format
void log_message_with_bin_val(const char *p_tag, enum eLogLevel level, const char *msg, uint8_t val);

// Sends a string, followed by a value in hexadecimal format
void log_message_with_hex_val(const char *p_tag, enum eLogLevel level, const char *msg, uint8_t val);

// Sets level of logging required
void log_set_output_level(const char *p_tag, enum eLogLevel level);

// Turns logging system on globally
void log_global_on(void);

// Turns logging system off globally
void log_global_off(void);

#endif // LOG_SYSTEM_DOT_H

/*** end of file ***/
