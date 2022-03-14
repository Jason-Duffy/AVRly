---
layout: default
title: Getting Started
permalink: /getting-started/
---

The projects outlined in this repository are intended for "bare metal" AVR programming. That is - compiling, debugging and flashing your application to the target MCU using the AVR crosspack 2 toolchain and an ISP programmer, rather than using the simpler and more user-friendly Arduino framework.

## Requirements:

#### A Text Editor
I like [Sublime Text][Sublime_Text_URL], but there are plenty of others to choose from, some popular choices are:
- [Sublime Text][Sublime_Text_URL]
- [Visual Studio Code][VS_Code_URL]
- [Codespaces][Codespaces_URL]
- [Atom][Atom_URL]
#### The AVR toolchain
###### MacOS
[AVR CrossPack][AVR_Crosspack_URL] Will provide everything you need to develop for AVR on MacOS; the GNU compile suite, C libraries for the AVR, the AVRDUDE uploader and more. 
#### An ISP programmer such as an AVRISP MKII, however I just use an Arduino Uno with the "Arduino as ISP" sketch flashed to it, and a simple shield I made. (Though you can achieve the same thing with just some dupont cables).
#### A serial terminal program for debugging, I tend to use CoolTerm for MacOS.






[Sublime_Text_URL]: [http://www.sublimetext.com/]
[VS_Code_URL]: [https://code.visualstudio.com/]
[Codespaces_URL]: https://github.com/features/codespaces
[Atom_URL]: https://github.com/features/codespaces

[AVR_Crosspack_URL]: https://www.obdev.at/products/crosspack/index.html