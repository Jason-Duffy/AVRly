/*
 @licstart  The following is the entire license notice for the JavaScript code in this file.

 The MIT License (MIT)

 Copyright (C) 1997-2020 by Dimitri van Heesch

 Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 and associated documentation files (the "Software"), to deal in the Software without restriction,
 including without limitation the rights to use, copy, modify, merge, publish, distribute,
 sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all copies or
 substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

 @licend  The above is the entire license notice for the JavaScript code in this file
*/
var NAVTREE =
[
  [ "AVRly - AVR Development Resources", "index.html", [
    [ "Getting-started", "md_avrly_projects_getting_started__getting_started.html", [
      [ "Software Requirements", "md_avrly_projects_getting_started__getting_started.html#autotoc_md0", [
        [ "A Source Code Editor", "md_avrly_projects_getting_started__getting_started.html#autotoc_md1", null ],
        [ "The AVR Toolchain", "md_avrly_projects_getting_started__getting_started.html#autotoc_md2", [
          [ "MacOS", "md_avrly_projects_getting_started__getting_started.html#autotoc_md3", null ],
          [ "Linux", "md_avrly_projects_getting_started__getting_started.html#autotoc_md4", [
            [ "Debian/Ubuntu distributions", "md_avrly_projects_getting_started__getting_started.html#autotoc_md5", null ],
            [ "Red Hat and Fedora distributions", "md_avrly_projects_getting_started__getting_started.html#autotoc_md6", null ]
          ] ],
          [ "Windows", "md_avrly_projects_getting_started__getting_started.html#autotoc_md7", null ]
        ] ],
        [ "A Serial Terminal Program", "md_avrly_projects_getting_started__getting_started.html#autotoc_md8", null ]
      ] ],
      [ "Hardware Required", "md_avrly_projects_getting_started__getting_started.html#autotoc_md9", [
        [ "An AVR microcontroller", "md_avrly_projects_getting_started__getting_started.html#autotoc_md10", null ],
        [ "An ISP Programmer", "md_avrly_projects_getting_started__getting_started.html#autotoc_md11", null ],
        [ "A USB to Serial Converter", "md_avrly_projects_getting_started__getting_started.html#autotoc_md12", null ],
        [ "Various USB cables", "md_avrly_projects_getting_started__getting_started.html#autotoc_md13", null ],
        [ "Breadboards", "md_avrly_projects_getting_started__getting_started.html#autotoc_md14", null ],
        [ "Power Supply (optional)", "md_avrly_projects_getting_started__getting_started.html#autotoc_md15", null ],
        [ "Jumpers/Dupont cables", "md_avrly_projects_getting_started__getting_started.html#autotoc_md16", null ],
        [ "An assortment of components", "md_avrly_projects_getting_started__getting_started.html#autotoc_md17", null ],
        [ "A multimeter", "md_avrly_projects_getting_started__getting_started.html#autotoc_md18", null ]
      ] ],
      [ "Connecting the Hardware", "md_avrly_projects_getting_started__getting_started.html#autotoc_md19", [
        [ "MCU Connections", "md_avrly_projects_getting_started__getting_started.html#autotoc_md20", null ],
        [ "Programmer Connections", "md_avrly_projects_getting_started__getting_started.html#autotoc_md21", null ]
      ] ],
      [ "Configuring the Makefile", "md_avrly_projects_getting_started__getting_started.html#autotoc_md22", [
        [ "MCU, Programmer and Directory variables", "md_avrly_projects_getting_started__getting_started.html#autotoc_md23", [
          [ "MCU", "md_avrly_projects_getting_started__getting_started.html#autotoc_md24", null ],
          [ "F_CPU", "md_avrly_projects_getting_started__getting_started.html#autotoc_md25", null ],
          [ "BAUD", "md_avrly_projects_getting_started__getting_started.html#autotoc_md26", null ],
          [ "LIBDIR", "md_avrly_projects_getting_started__getting_started.html#autotoc_md27", null ],
          [ "PROGRAMMER_TYPE", "md_avrly_projects_getting_started__getting_started.html#autotoc_md28", null ],
          [ "PROGRAMMER_ARGS", "md_avrly_projects_getting_started__getting_started.html#autotoc_md29", null ]
        ] ],
        [ "Fuses", "md_avrly_projects_getting_started__getting_started.html#autotoc_md30", [
          [ "LFUSE", "md_avrly_projects_getting_started__getting_started.html#autotoc_md31", null ],
          [ "HFUSE", "md_avrly_projects_getting_started__getting_started.html#autotoc_md32", null ],
          [ "EFUSE", "md_avrly_projects_getting_started__getting_started.html#autotoc_md33", null ]
        ] ]
      ] ],
      [ "Flashing the Chip", "md_avrly_projects_getting_started__getting_started.html#autotoc_md34", [
        [ "Flash Fuses", "md_avrly_projects_getting_started__getting_started.html#autotoc_md35", null ],
        [ "Flash the Code", "md_avrly_projects_getting_started__getting_started.html#autotoc_md36", [
          [ "Basic Make Commands:", "md_avrly_projects_getting_started__getting_started.html#autotoc_md37", null ],
          [ "Advanced Make Commands:", "md_avrly_projects_getting_started__getting_started.html#autotoc_md38", null ]
        ] ],
        [ "Verify Makefile Settings", "md_avrly_projects_getting_started__getting_started.html#autotoc_md39", null ],
        [ "Style Guide", "md_avrly_projects_getting_started__getting_started.html#autotoc_md40", null ],
        [ "Documentation", "md_avrly_projects_getting_started__getting_started.html#autotoc_md41", null ],
        [ "Coding Standards", "md_avrly_projects_getting_started__getting_started.html#autotoc_md42", null ]
      ] ]
    ] ],
    [ "Anatomy of Embedded Firmware", "md_avrly_projects_anatomy_of_embedded_firmware__anatomy.html", [
      [ "A Word on Doxygen", "md_avrly_projects_anatomy_of_embedded_firmware__anatomy.html#autotoc_md44", null ],
      [ "Formatting", "md_avrly_projects_anatomy_of_embedded_firmware__anatomy.html#autotoc_md45", null ],
      [ "Licence", "md_avrly_projects_anatomy_of_embedded_firmware__anatomy.html#autotoc_md46", null ],
      [ "C Header Files", "md_avrly_projects_anatomy_of_embedded_firmware__anatomy.html#autotoc_md47", null ],
      [ "C Source Files", "md_avrly_projects_anatomy_of_embedded_firmware__anatomy.html#autotoc_md48", null ],
      [ "pin_defines.h", "md_avrly_projects_anatomy_of_embedded_firmware__anatomy.html#autotoc_md49", null ],
      [ "main.c", "md_avrly_projects_anatomy_of_embedded_firmware__anatomy.html#autotoc_md50", null ],
      [ "Makefile", "md_avrly_projects_anatomy_of_embedded_firmware__anatomy.html#autotoc_md51", null ],
      [ "Templates", "md_avrly_projects_anatomy_of_embedded_firmware__anatomy.html#autotoc_md52", null ]
    ] ],
    [ "Contributor's Guide", "md_avrly_projects_contributors_guide__contributors_guide.html", [
      [ "Style Guide", "md_avrly_projects_contributors_guide__contributors_guide.html#autotoc_md54", null ],
      [ "Templates", "md_avrly_projects_contributors_guide__contributors_guide.html#autotoc_md55", null ],
      [ "Submitting a Pull Request", "md_avrly_projects_contributors_guide__contributors_guide.html#autotoc_md56", null ]
    ] ],
    [ "ccs811", "md_avrly_projects_drivers_and_examples_ccs811_sensor_ccs811.html", null ],
    [ "drivers-and-examples", "md_avrly_projects_drivers_and_examples_drivers_and_examples.html", null ],
    [ "hd44780_lcd", "md_avrly_projects_drivers_and_examples_hd44780_lcd_hd44780_lcd.html", null ],
    [ "log_system", "md_avrly_projects_drivers_and_examples_log_system_log_system.html", null ],
    [ "mcp48x2", "md_avrly_projects_drivers_and_examples_mcp4812_dac_mcp48x2.html", null ],
    [ "Modules", "modules.html", "modules" ],
    [ "Classes", "annotated.html", [
      [ "Class List", "annotated.html", "annotated_dup" ],
      [ "Class Index", "classes.html", null ],
      [ "Class Members", "functions.html", [
        [ "All", "functions.html", null ],
        [ "Variables", "functions_vars.html", null ]
      ] ]
    ] ],
    [ "Files", "files.html", [
      [ "File List", "files.html", "files_dup" ],
      [ "File Members", "globals.html", [
        [ "All", "globals.html", null ],
        [ "Functions", "globals_func.html", null ],
        [ "Enumerations", "globals_enum.html", null ],
        [ "Macros", "globals_defs.html", null ]
      ] ]
    ] ]
  ] ]
];

var NAVTREEINDEX =
[
"anatomy-of-embedded-firmware_2layout-and-documentation-examples_2filename_8c.html",
"md_avrly_projects_anatomy_of_embedded_firmware__anatomy.html#autotoc_md50"
];

var SYNCONMSG = 'click to disable panel synchronisation';
var SYNCOFFMSG = 'click to enable panel synchronisation';