---
layout: default
title: Getting Started
permalink: /getting-started/
---

The projects outlined in this repository are intended for "bare metal" AVR programming. That is - compiling, debugging and flashing your application to the target MCU using the AVR crosspack 2 toolchain and an ISP programmer, rather than using the simpler and more user-friendly Arduino framework.

# Requirements:

## A Source Code Editor
I like [Sublime Text][Sublime_Text_URL], but there are plenty of others to choose from, some popular choices are:
- [Sublime Text][Sublime_Text_URL]
- [Visual Studio Code][VS_Code_URL]
- [Codespaces][Codespaces_URL]
- [Atom][Atom_URL]

## The AVR Toolchain
### MacOS
[AVR CrossPack][AVR_Crosspack_URL] Will provide everything you need to develop for AVR on MacOS; the GNU compile suite, C libraries for the AVR, the AVRDUDE uploader and more.
### Linux
#### Debian/Ubuntu distributions
- Its helpful to update all your current installed packages first.

	`sudo apt-get update`

	`sudo apt-get upgrade all`

- Then we can install the required packages.

	`sudo apt-get install avrdude avrdude-doc gcc-avr binutils-avr avr-libc gdb-avr`

#### Red Hat and Fedora distributions
- Its helpful to update all your current installed packages first.

	`sudo yum update`

	`sudo yum upgrade-all`

- Then we can install the required packages.

	`sudo yum install avrdude avr-gcc avr-binutils avr-libc avr-gdb`
### Windows
Windows users can use the official toolchain from the manufacturer, [Microchip Studio][Microchip_Studio_URL]. This is an IDE so it's full of features, but also has steep learning curve - follow their tutorial [here][Microchip_Studio_Tutorial_URL] to get to grips with it.
## A Serial Terminal Program
This is used to send messages between your PC and the target MCU, and you'll find it's a vital debugging tool when coupled with the log_system module. I tend to use [CoolTerm][CoolTerm_URL] which is available on MacOS, Windows and Linux.


# Hardware Required:

## An AVR microcontroller


## An ISP Programmer
Such as an [AVRISP MKII][AVRISP_URL], however I had some compatability issues with this one (on MacOS) so instead I just use an Arduino Uno with the "Arduino as ISP" sketch flashed to it, and a simple shield I made - though you can achieve the same thing with just some dupont cables if you don't want to wait for the shield to come back from fab.

## A USB to Serial Converter
There are many types available, I use one of [these][USB_Serial_URL].

## Various USB cables
It's useful to keep several USB cables, micro, mini, USB-A etc.

## Breadboards
I like [these][Small_Breadboard_URL] ones with the power supply module for small test projects, and [these][Large_Breadboard_URL] ones for larger, more complex projects. For anything beyond that, I would design a development board with lots of connection and expansion flexibility.

## Dupont cables

## An assortment components



[Sublime_Text_URL]: http://www.sublimetext.com/
[VS_Code_URL]: https://code.visualstudio.com/
[Codespaces_URL]: https://github.com/features/codespaces
[Atom_URL]: https://github.com/features/codespaces

[AVR_Crosspack_URL]: https://www.obdev.at/products/crosspack/index.html
[Microchip_Studio_URL]: https://www.microchip.com/en-us/tools-resources/develop/microchip-studio
[Microchip_Studio_Tutorial_URL]: https://www.microchip.com/en-us/tools-resources/develop/microchip-studio#Getting%20Started
[CoolTerm_URL]: https://freeware.the-meiers.org/
[AVRISP_URL]: https://www.amazon.co.uk/Waveshare-Programmer-USB-AVRISP-XPII/dp/B00KM6ZA9I?th=1
[USB_Serial_URL]: https://www.amazon.co.uk/Ccylez-Converter-Adapter-FT232RL-Android-default/dp/B08DV1SXMQ/ref=sr_1_4?crid=8ZN3WET67TSU&keywords=usb+serial+converter+module&qid=1647296288&sprefix=usb+serial+converter+modul%2Caps%2C72&sr=8-4
[Small_Breadboard_URL]: https://www.amazon.co.uk/AZDelivery-Breadboard-Supply-Adapter-Jumkper/dp/B01N4VCYUK/ref=sr_1_20?crid=29EM44FS19IF2&keywords=breadboard%2Bwith%2Bpower%2Bsupply&qid=1647296608&sprefix=breadboard%2Bwith%2Bpower%2Bsupply%2Caps%2C64&sr=8-20&th=1
[Large_Breadboard_URL]: https://www.amazon.co.uk/K-H-RH-74-Solderless-Breadboard/dp/B079H4N8Y4/ref=sr_1_6?crid=18JXJAV0E8H6K&keywords=large+breadboard+electronics&qid=1647296861&sprefix=large+breadboard+electronics%2Caps%2C56&sr=8-6