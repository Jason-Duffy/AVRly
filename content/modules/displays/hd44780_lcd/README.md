@ingroup hd44780_lcd

## Introduction

The Hitachi HD44780 LCD (Liquid Crystal Display) controller is an extremely popular IC (Integrated Circuit) in use since the 1980's. It can drive upto two lines of 8 characters each, and can be addressed using either an 8 bit of 4 bit parallel data bus, plus some control pins. This driver and example application was written from the datasheet, which can be found [here][HD44780_Datasheet_URL].

This example is for a 16x2 LCD module, with the HD44780 LCD controller IC on board. 


## Interface

For this example, we will use the controller in 4 bit mode, it uses fewer precious GPIO's, but takes twice as long for each character or instruction to be written to the display. The pins and their uses are shown below, note that pins D0 - D3 can be left unconnected in 4 bit mode. As we are not using the display in read mode, we can just tie the RW pin to ground, freeing up a GPIO pin on the host MCU. 

| Pin      | Function            |
| -------- | -------------       |
| VSS	   | Ground Connection   |
| VDD      | +5V Connection      |
| VO       | Contrast Adjust     |
| RS       | Register Select     |
| RW       | Read/Write Select   |
| E        | Enable (Latch)      |
| D0       | Data Pin 0          |
| D1       | Data Pin 1          |
| D2       | Data Pin 2          |
| D3       | Data Pin 3          |
| D4       | Data Pin 4          |
| D5       | Data Pin 5          |
| D6       | Data Pin 6          |
| D7       | Data Pin 7          |
| A/LED+   | Backlight+ (Annode) |
| K/LED-   | Backlight- (Cathode)|


The connections are to be made as shown in the schematic below. Note the variable voltage control on pins VO and LED+; if you don't have trim pots to hand, you can just make 2 simple voltage dividers for the contrast and backlight adjustment using fixed value resistors. 

![16x2 LCD Hookup Schematic](./images/16x2_hookup_schem.png)

This can easily be built on a breadboard as shown below with the AVRly Dev Kit. 

![16x2 LCD Breadboard Example](./images/16x2_breadboard_example.jpg)


## Example Application



[HD44780_Datasheet_URL]: https://pdf1.alldatasheet.com/datasheet-pdf/view/63673/HITACHI/HD44780.html