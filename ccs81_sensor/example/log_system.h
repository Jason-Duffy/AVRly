/******************************************************************************
  FileName    [ log_system.h ]
  PackageName [ logsystem ]
  Description [ Logging subsystem to send debug messages to PC via USB serial
                adapter ]
  Author      [ Jason Duffy ]
  Copyright   [  ]
  Revision    [ v0.0.1
******************************************************************************/

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
