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
    [ "Getting Started with Blink", "index.html", [
      [ "Software Requirements", "index.html#autotoc_md0", [
        [ "A Source Code Editor", "index.html#autotoc_md1", null ],
        [ "The AVR Toolchain", "index.html#autotoc_md2", [
          [ "MacOS", "index.html#autotoc_md3", null ],
          [ "Linux", "index.html#autotoc_md4", [
            [ "Debian/Ubuntu distributions", "index.html#autotoc_md5", null ],
            [ "Red Hat and Fedora distributions", "index.html#autotoc_md6", null ]
          ] ],
          [ "Windows", "index.html#autotoc_md7", null ]
        ] ],
        [ "A Serial Terminal Program", "index.html#autotoc_md8", null ]
      ] ],
      [ "Hardware Required", "index.html#autotoc_md9", [
        [ "An AVR microcontroller", "index.html#autotoc_md10", null ],
        [ "An ISP Programmer", "index.html#autotoc_md11", null ],
        [ "A USB to Serial Converter", "index.html#autotoc_md12", null ],
        [ "Various USB cables", "index.html#autotoc_md13", null ],
        [ "Breadboards", "index.html#autotoc_md14", null ],
        [ "Power Supply (optional)", "index.html#autotoc_md15", null ],
        [ "Jumpers/Dupont cables", "index.html#autotoc_md16", null ],
        [ "An assortment of components", "index.html#autotoc_md17", null ],
        [ "A multimeter", "index.html#autotoc_md18", null ]
      ] ],
      [ "Connecting the Hardware", "index.html#autotoc_md19", [
        [ "MCU Connections", "index.html#autotoc_md20", null ],
        [ "Programmer Connections", "index.html#autotoc_md21", null ]
      ] ],
      [ "Configuring the Makefile", "index.html#autotoc_md22", [
        [ "MCU, Programmer and Directory variables", "index.html#autotoc_md23", [
          [ "MCU", "index.html#autotoc_md24", null ],
          [ "F_CPU", "index.html#autotoc_md25", null ],
          [ "BAUD", "index.html#autotoc_md26", null ],
          [ "LIBDIR", "index.html#autotoc_md27", null ],
          [ "PROGRAMMER_TYPE", "index.html#autotoc_md28", null ],
          [ "PROGRAMMER_ARGS", "index.html#autotoc_md29", null ]
        ] ],
        [ "Fuses", "index.html#autotoc_md30", [
          [ "LFUSE", "index.html#autotoc_md31", null ],
          [ "HFUSE", "index.html#autotoc_md32", null ],
          [ "EFUSE", "index.html#autotoc_md33", null ]
        ] ]
      ] ],
      [ "Flashing the Chip", "index.html#autotoc_md34", [
        [ "Flash Fuses", "index.html#autotoc_md35", null ],
        [ "Flash the Code", "index.html#autotoc_md36", [
          [ "Basic Make Commands:", "index.html#autotoc_md37", null ],
          [ "Advanced Make Commands:", "index.html#autotoc_md38", null ]
        ] ],
        [ "Verify Makefile Settings", "index.html#autotoc_md39", null ],
        [ "Style Guide", "index.html#autotoc_md40", null ],
        [ "Documentation", "index.html#autotoc_md41", null ],
        [ "Coding Standards", "index.html#autotoc_md42", null ]
      ] ]
    ] ],
    [ "Anatomy of Embedded Firmware", "md_content_anatomy_of_embedded_firmware__anatomy.html", [
      [ "A Word on Doxygen", "md_content_anatomy_of_embedded_firmware__anatomy.html#autotoc_md44", null ],
      [ "Formatting", "md_content_anatomy_of_embedded_firmware__anatomy.html#autotoc_md45", null ],
      [ "Licence", "md_content_anatomy_of_embedded_firmware__anatomy.html#autotoc_md46", null ],
      [ "C Header Files", "md_content_anatomy_of_embedded_firmware__anatomy.html#autotoc_md47", null ],
      [ "C Source Files", "md_content_anatomy_of_embedded_firmware__anatomy.html#autotoc_md48", null ],
      [ "pin_defines.h", "md_content_anatomy_of_embedded_firmware__anatomy.html#autotoc_md49", null ],
      [ "main.c", "md_content_anatomy_of_embedded_firmware__anatomy.html#autotoc_md50", null ],
      [ "Makefile", "md_content_anatomy_of_embedded_firmware__anatomy.html#autotoc_md51", null ],
      [ "Templates", "md_content_anatomy_of_embedded_firmware__anatomy.html#autotoc_md52", null ]
    ] ],
    [ "Contributor's Guide", "md_content_contributors_guide__contributors_guide.html", [
      [ "Style Guide", "md_content_contributors_guide__contributors_guide.html#autotoc_md54", null ],
      [ "Templates", "md_content_contributors_guide__contributors_guide.html#autotoc_md55", null ],
      [ "Submitting a Pull Request", "md_content_contributors_guide__contributors_guide.html#autotoc_md56", null ]
    ] ],
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
"index.html#autotoc_md8"
];

var SYNCONMSG = 'click to disable panel synchronisation';
var SYNCOFFMSG = 'click to enable panel synchronisation';