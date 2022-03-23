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
 * @file usart.c
 * @ingroup ccs811
 * @author Jason Duffy
 * @date 15th March 2022
 * @brief Driver file providing core USART communication between the target MCU
 * and your PC.
 * @bug No known bugs. 
 * @see
 */

#include <util/setbaud.h>
#include <avr/io.h>

#include "usart.h"

static void transmit_byte(uint8_t data);
static uint8_t receive_byte(void);


/*
 * Takes the defined BAUD and F_CPU, calculates the bit-clock multiplier,
 * configures the hardware USART.
 */
void init_usart(void)
{
  // defined in setbaud.h
  UBRR0H = UBRRH_VALUE;
  UBRR0L = UBRRL_VALUE;

#if USE_2X
  UCSR0A |= (1 << U2X0);
#else
  UCSR0A &= ~(1 << U2X0);
#endif
  
  // Enable USART transmitter/receiver
  UCSR0B = (1 << TXEN0) | (1 << RXEN0);
  // 8 data bits, 1 stop bit
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

// Utility function to transmit an entire string from RAM.
void print_string(const char myString[])
{
  uint8_t i = 0;
  while (myString[i])
  {
    transmit_byte(myString[i]);
    i++;
  }
}

/*
 * Define a string variable, pass it to this function. The string will contain
 * whatever you typed over serial.
 */
void read_string(char myString[], uint8_t maxLength)
{
  char response;
  uint8_t count = 0;

  while (count < (maxLength - 1))
  {                  
    response = receive_byte();
    transmit_byte(response); // echo

    if (response == '\r') // enter marks the end
    {
      break;
    }

    else
    {
      myString[count] = response; // add in a letter
      ++count;
    }
  }
  myString[count] = 0; // terminal NULL character */
}

// Prints a byte out as its 3-digit ascii equivalent.
void print_byte(uint8_t byte)
{
  // Converts a byte to a string of decimal text, sends it
  transmit_byte('0' + (byte / 100));			// Hundreds
  transmit_byte('0' + ((byte / 10) % 10));   // Tens
  transmit_byte('0' + (byte % 10));			// Ones
}

// Prints a word (16-bits) out as its 5-digit ascii equivalent.
void print_word(uint16_t word)
{
  transmit_byte('0' + (word / 10000));       // Ten-thousands
  transmit_byte('0' + ((word / 1000) % 10)); //  Thousands
  transmit_byte('0' + ((word / 100) % 10));  //  Hundreds
  transmit_byte('0' + ((word / 10) % 10));   //  Tens
  transmit_byte('0' + (word % 10));          //  Ones
}

// Prints a byte out in 1s and 0s.
void print_binary_byte(uint8_t byte)
{
  uint8_t bit;
  for (bit = 7; bit < 255; bit--)
  {
    if (bit_is_set(byte, bit))
    {
      transmit_byte('1');
    }
    else
    {
      transmit_byte('0');
    }
  }
}

// Converts a nibble to a hexadecimal character
char nibble_to_hex_character(uint8_t nibble)
{
  if (nibble < 10)
  {
    return ('0' + nibble);
  }
  else
  {
    return ('A' + nibble - 10);
  }
}

// Prints a byte as its hexadecimal equivalent
void print_hex_byte(uint8_t byte)
{
  uint8_t nibble;
  nibble = (byte & 0b11110000) >> 4;
  transmit_byte(nibble_to_hex_character(nibble));
  nibble = byte & 0b00001111;
  transmit_byte(nibble_to_hex_character(nibble));
}

 // Gets a numerical 0-255 from the serial port, converts string to number.
uint8_t get_number(void)
{
  char hundreds = '0';
  char tens = '0';
  char ones = '0';
  char thisChar = '0';
  do
  {
    hundreds = tens;
    tens = ones;
    ones = thisChar;
    thisChar = receive_byte(); // get a new character
    transmit_byte(thisChar);   // echo
  }
  while (thisChar != '\r'); // until type return

  // TODO: Bracketise this further
  return (100 * (hundreds - '0') + 10 * (tens - '0') + ones - '0');
}

// TODO: Replace these with non-blocking waits
//Blocking transmit and receive functions.
static void transmit_byte(uint8_t data)
{
  // Wait for empty transmit buffer
  loop_until_bit_is_set(UCSR0A, UDRE0);
  // Send Data
  UDR0 = data;
}

static uint8_t receive_byte(void)
{
  // Wait for incoming data
  loop_until_bit_is_set(UCSR0A, RXC0);
  //return register value
  return UDR0;
}


/*** end of file ***/
