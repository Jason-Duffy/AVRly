@ingroup spi

## Introduction

SPI (Serial Peripheral Interface) is a syncronous communication interface specification popular in embedded systems. It's a form of serial communication - meaning the 'bits' of data are sent one after the other (rather than several at the same time as seen in parallel communication). The "syncronous" part means that there is a clock signal to provide timing for all the devices on the bus, rather than using an agreed baud rate.

## Terminology

As this interface was developed in the mid 1980's, some of the language and terminology used is now quite dated. The specification uses the terms "Master" and "Slave" to mean the controlling device and the peripheral device respectively, however for obvious reasons casual and unnecessary references to slavery should no longer be used. This can be a little confusing as there are still many datasheets, application notes and tutorials around using the original terms, including the ATmega datasheets. 

Throughout the guides on this site we will use the original acronyms MOSI (Master Out, Slave In), and MISO (Master In, Slave Out) so as not to cause confusion by straying too far from the datasheet terminology, but will refrain from using the terms "Master" and "Slave". Instead, the words "Controller" and "Peripheral" will be used. In addition to this, the acronym SS (Slave Select) is only used when referring to the SS pin on the ATmega MCU; when referring to the select pin on any other device we will use the term CS (Chip Select).

Many manufacturers are now making these changes in their documentation, and I would encourage you to make the effort to do the same in your own software. The Open Source Hardware Association (OSHWA) have come up with [a resolution for the naming of these pins][OSHWA_Resolution_URL], summarised below. 

For single-role hardware, the terms SDO and SDI (Serial Data Out/In) can be used, while for devices than can be either the controller or the peripheral, PICO and POCI (Peripheral In, Controller Out and vice versa) can be used.

The Pin Name SS (Slave Select) is also deprecated, to be replaced by CS (Chip Select), while SCK (Serial Clock) remains unchanged.  

## Interface




[OSHWA_Resolution_URL]: https://www.oshwa.org/a-resolution-to-redefine-spi-signal-names/