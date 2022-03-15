

The projects outlined in this repository are intended for ["bare metal"][Bare_Metal_URL] AVR programming. That is - compiling, debugging and flashing your application without an underlying operating system, directly to the target MCU using the AVR crosspack 2 toolchain and an ISP programmer, rather than using the simpler and more user-friendly Arduino framework.

# Requirements

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


# Hardware Required

## An AVR microcontroller
An [ATmega328P-PU][ATmega328_URL] is a good place to start - It's a DIP package so fits nicely in a breadboard or an IC socket. If you want something SMD with more GPIO's interrupts and timers, an [ATmega2560][ATmega2560_URL] has plenty to offer. It's worth noting that this family of AVR's is now listed as "Not reccommended for new designs" which means they are being phased out of production in favour of the newer AVR families. Most of the functionality and methodology should be essentially the same with the newer chips, but they will likely have a different pinout and subset of registers so code and hookup will need to be ported. 


## An ISP Programmer
Such as an [AVRISP MKII][AVRISP_URL], however I had some compatability issues with this one (on MacOS) so instead I just use an Arduino Uno with the "Arduino as ISP" sketch flashed to it, and [a simple shield I made][Uno_ISP_Shield_URL] - though you can achieve the same thing with some dupont cables if you don't want to wait for the shield to come back from fab.
![uno_isp_3d_render.png](./images/uno_isp_3d_render.png)

## A USB to Serial Converter
There are many types available, I use one of [these][USB_Serial_URL].

## Various USB cables
It's useful to keep several USB cables, micro, mini, USB-A etc.

## Breadboards
I like [these][Small_Breadboard_URL] ones with the power supply module for small test projects, and [these][Large_Breadboard_URL] ones for larger, more complex projects. For anything beyond that, I would design a development PCB with lots of connection and expansion flexibility.

## Jumpers/Dupont cables
A set of [breadboard jumper cables][Breadboard_Jumpers_URL] is handy to keep your close wiring neat and tidy, then a set of various lengths and connection types of [dupont cables][Dupont_Cables_URL] is useful to connect to other peripherals.

## An assortment of components
A kit like [this one][Components_Kit_URL] is a frugal way to source many of the components and accessories needed. You will certainly need a selection of resistors, capacitors, LEDs etc. 

## A multimeter
A multimeter like [this one][Multimeter_URL] will help with debugging when hardware is involved. An [oscilloscope][Oscilloscope_URL] gives an extra dimension of insight into your circuits and applications, but they are an expensive piece of kit so a little out of reach for beginners.



# Connecting the Hardware






[Bare_Metal_URL]: https://en.wikipedia.org/wiki/Bare_machine
[Sublime_Text_URL]: http://www.sublimetext.com/
[VS_Code_URL]: https://code.visualstudio.com/
[Codespaces_URL]: https://github.com/features/codespaces
[Atom_URL]: https://github.com/features/codespaces

[AVR_Crosspack_URL]: https://www.obdev.at/products/crosspack/index.html
[Microchip_Studio_URL]: https://www.microchip.com/en-us/tools-resources/develop/microchip-studio
[Microchip_Studio_Tutorial_URL]: https://www.microchip.com/en-us/tools-resources/develop/microchip-studio#Getting%20Started
[CoolTerm_URL]: https://freeware.the-meiers.org/
[AVRISP_URL]: https://www.amazon.co.uk/Waveshare-Programmer-USB-AVRISP-XPII/dp/B00KM6ZA9I?th=1
[Uno_ISP_Shield_URL]: /Uno_ISP_Shield
[USB_Serial_URL]: https://www.amazon.co.uk/Ccylez-Converter-Adapter-FT232RL-Android-default/dp/B08DV1SXMQ/ref=sr_1_4?crid=8ZN3WET67TSU&keywords=usb+serial+converter+module&qid=1647296288&sprefix=usb+serial+converter+modul%2Caps%2C72&sr=8-4
[Small_Breadboard_URL]: https://www.amazon.co.uk/AZDelivery-Breadboard-Supply-Adapter-Jumkper/dp/B01N4VCYUK/ref=sr_1_20?crid=29EM44FS19IF2&keywords=breadboard%2Bwith%2Bpower%2Bsupply&qid=1647296608&sprefix=breadboard%2Bwith%2Bpower%2Bsupply%2Caps%2C64&sr=8-20&th=1
[Large_Breadboard_URL]: https://www.amazon.co.uk/K-H-RH-74-Solderless-Breadboard/dp/B079H4N8Y4/ref=sr_1_6?crid=18JXJAV0E8H6K&keywords=large+breadboard+electronics&qid=1647296861&sprefix=large+breadboard+electronics%2Caps%2C56&sr=8-6
[ATmega328_URL]: https://www.amazon.co.uk/Atmel-ATMega328-PU-ATMEL-Microcontroller-Chip/dp/B071Y4YF5X/ref=sr_1_5?crid=564N7F4OE3JE&keywords=atmega328&qid=1647299808&sprefix=atmega328%2Caps%2C62&sr=8-5
[ATmega2560_URL]: https://www.amazon.co.uk/1pcs-lot-ATMEGA2560-16AU-ATMEGA2560-QFP-100/dp/B09SZGJS7C/ref=sr_1_5?crid=3R3LG8NF0EER8&keywords=atmega2560&qid=1647299857&sprefix=atmega256%2Caps%2C76&sr=8-5
[Breadboard_Jumpers_URL]: https://www.amazon.co.uk/WANTOUTH-Preformed-Breadboard-Solderless-Prototyping/dp/B08QS6961R/ref=sr_1_5?crid=36KPWIVO59605&keywords=breadboard+jumpers&qid=1647300367&sprefix=breadboard+jumpers%2Caps%2C245&sr=8-5
[Dupont_Cables_URL]: https://www.amazon.co.uk/YXPCARS-Solderless-Breadboard-Multicolored-Arduino/dp/B08HQ7K6M7/ref=sr_1_27?crid=1GQC7DDTANB5H&keywords=dupont+cables+set&qid=1647301269&sprefix=dupont+cables+set%2Caps%2C71&sr=8-27
[Components_Kit_URL]: https://www.amazon.co.uk/Freenove-Ultimate-Compatible-Programming-Electronics/dp/B08B4D5MV5/ref=sr_1_17_sspa?crid=YI7I2MN0COCC&keywords=arduino+components+kit&qid=1647301388&sprefix=arduino+components%2Caps%2C75&sr=8-17-spons&psc=1&spLa=ZW5jcnlwdGVkUXVhbGlmaWVyPUEzTjY0QVFGTEZHREVNJmVuY3J5cHRlZElkPUEwNjU1Mzk4MkRCS1c5UFBaMUI2QiZlbmNyeXB0ZWRBZElkPUEwMDEyMzQxM1NSUDZWS1RPM1Q2SCZ3aWRnZXROYW1lPXNwX210ZiZhY3Rpb249Y2xpY2tSZWRpcmVjdCZkb05vdExvZ0NsaWNrPXRydWU=
[MULTIMETER_URL]: https://www.ebay.co.uk/itm/373974464011?epid=23040427421&_trkparms=ispr%3D1&hash=item57129d760b:g:ecgAAOSwcvJhM~1Y&amdata=enc%3AAQAGAAACoPYe5NmHp%252B2JMhMi7yxGiTJkPrKr5t53CooMSQt2orsSafTQYbq3L7RBVAMi0K9cw1RWXBpCryIDtHtQ%252FwGGrM5qNRo2BcdEvJNXURbFcGIieFzIjcYyayBhlA94swn2TTvs028l2IF1Z7kkPlAkTOZau7i64BOsAJM5jtEUKTzYuTAksI%252B6wqVDHXCmc%252BbqVJWdWCtN%252FedfWrLz22fV7JfFf3r%252BndQy6pgUf%252B0CqyxVpLGK%252FtsA2WoJN66265Nsb%252Biz2cPGbaMohOx96MSBAMI556eVyZ1Jt%252FgLkiIOgy%252F4LEQX%252B3foG6Ptb%252BN9ZmnQkdg5oCnRE0hxlFfAD5SOzEzmtg9%252BIE2HDfbFvLsU0Z0%252BZ2IQwJohjr5c6NdN3ax%252B0NkAFl5TKriVBAerlTCklJ%252BeOmn4DGytxPaRs%252B7VYCtZf8PXhxRmWn89GJw9Xt%252FCGpH1hvp9DXVNVCjJBMZeRVIKV3LmmgTdNnj9a%252FAUNwyB5qnSZWNkYEvX0swcp0PJU6qoVXYAEBLx2T03VucnyJ6R8Ja2NbFUVIPLPL4f4hHTUcR5hxbe0v9ux4iwgbiJLIPIXDKfDovdqX%252BUgBKJiLOUzGZKey7I7PeEDHsw5vr1KEHBd6%252B3Cw0FN0asmNY2XUmwd9LrLf401Wo4ovba%252FjznpyXfGfjHaobMVxQzN%252FAPIdxhcaODHy%252Bku4xgVEgZaD8n58JPn%252Fz0u75IwCzYoV%252FHGCX7zUgjd0Flsw5CiQpHVdB4eqGaKKP97ct2rRUEtd4t5YZJJi7KbHlJxs3Kr4KxuyQ2Xfk4nbZhpRPStSf%252FrLNa%252FxQudCxW2vnABZJayi8xGYlqFq%252BZYczELbh3%252BIyYls%252FmPtJgL%252F0yOiQgmVnId%252BTVMf1Q7taqp1w%252FN0AaMA%253D%253D%7Cclp%3A2334524%7Ctkp%3ABFBMlsihrvFf
[Oscilloscope_URL]: https://telonic.co.uk/product/rigol-ds1054z-50mhz-digital-oscilloscope/