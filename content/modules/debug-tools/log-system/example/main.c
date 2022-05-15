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
 * @file main.c
 * @ingroup log_system
 * @author Jason Duffy
 * @date 1st March 2022
 * @brief Main routine for log_system example application.
 * @bug No known bugs. 
 */

#include <util/delay.h>
#include "log_system.h"

#define DELAY_TIME      1000
#define INCREMENT_VAL   1


/**
 * Instantiation of log_system config object. 
 */
log_system_config_t main_log =
{
  .p_system_tag = "Main",
  .file_log_level = DEBUG,
};

/**
 * Example variable to be output to log_system.
 */
uint8_t example_variable = 59;


/**
 * Main routine for example application. 
 */ 
int main()
{
    // Setup
    init_log_system();
    log_message(&main_log, INFO, "Hello, World!");
    _delay_ms(DELAY_TIME);

    // Loop forever
    while(1)
    {
        /*
         * This message is NOT printed, as the level is above that specified in
         * main_log.file_log_level
         */
        log_message(&main_log, VERBOSE_DEBUG, "Verbose Debug Message.");
        _delay_ms(DELAY_TIME);

        // This message IS printed. 
        log_message_with_bin_val(&main_log, DEBUG,
                    "The binary format value of example_variable is: ",
                    example_variable);

        // As is this one. 
        log_message_with_dec_val(&main_log, DEBUG,
                    "The decimal format value of example_variable is: ",
                    example_variable);

        // And this one. 
        log_message_with_hex_val(&main_log, DEBUG,
                    "The hexadecimal format value of example_variable is: ",
                    example_variable);

        // Edit variable value. 
        example_variable += INCREMENT_VAL;
        _delay_ms(DELAY_TIME);
    }

    return 0;
}