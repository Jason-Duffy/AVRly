The projects outlined in this repository are intended for "bare metal" AVR programming. That is - compiling, debugging and flashing your application to the target MCU using the AVR crosspack 2 toolchain and an ISP programmer, rather than using the simpler and more user-friendly Arduino framework.

Requirements:

- A code editor (I like Sublime text, but there are plenty of others to choose from).
- The AVR toolchain, AVR crosspack 2 for MacOS.
- An ISP programmer such as an AVRISP MKII, however I just use an Arduino Uno with the "Arduino as ISP" sketch flashed to it, and a simple shield I made. (Though you can achieve the same thing with just some dupont cables).
- A serial terminal program for debugging, I tend to use CoolTerm for MacOS.