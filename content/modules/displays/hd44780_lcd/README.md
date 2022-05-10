@ingroup hd44780_lcd

## Introduction

The Hitachi HD44780 LCD (Liquid Crystal Display) controller is an extremely popular IC (Integrated Circuit) in use since the 1980's. It can drive upto two lines of 8 characters each, and can be addressed using either an 8 bit of 4 bit parallel data bus, plus some control pins. This driver and example application was written from the datasheet, which can be found [here][HD44780_Datasheet_URL].

This example is for a 16x2 LCD module, with the HD44780 LCD controller IC on board. 


## Interface

For this example, we will use the controller in 4 bit mode, it uses fewer precious GPIO's, but takes twice as long for each character or instruction to be written to the display. The connections required are shown below. 

| Pin      | Function          |
| -------- | -------------     |
| RS       | Register Select   |
| RW       | Read/Write Select |
| E        | Enable (Latch)    |



## Example Application



[HD44780_Datasheet_URL]: https://pdf1.alldatasheet.com/datasheet-pdf/view/63673/HITACHI/HD44780.html