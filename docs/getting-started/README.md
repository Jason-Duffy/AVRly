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

## The AVR toolchain
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
## A serial terminal program
This is used to send messages between your PC and the target MCU, and you'll find it's a vital debugging tool when coupled with the log_system module. I tend to use [CoolTerm][CoolTerm_URL] which is available on MacOS, Windows and Linux.



# Hardware required:

## An ISP programmer
Such as an AVRISP MKII, however I just use an Arduino Uno with the "Arduino as ISP" sketch flashed to it, and a simple shield I made. (Though you can achieve the same thing with just some dupont cables).





[Sublime_Text_URL]: http://www.sublimetext.com/
[VS_Code_URL]: https://code.visualstudio.com/
[Codespaces_URL]: https://github.com/features/codespaces
[Atom_URL]: https://github.com/features/codespaces

[AVR_Crosspack_URL]: https://www.obdev.at/products/crosspack/index.html
[Microchip_Studio_URL]: https://www.microchip.com/en-us/tools-resources/develop/microchip-studio
[Microchip_Studio_Tutorial_URL]: https://www.microchip.com/en-us/tools-resources/develop/microchip-studio#Getting%20Started
[CoolTermURL]: https://freeware.the-meiers.org/