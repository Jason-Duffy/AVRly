@ingroup usart

## Introduction

USART is a form of serial communication protocol, and stands for Universal Synchronous/Asynchronous Receiver/Transmitter)Transmitter. This protocal provides the option of synchronous or asynchronous modes (meaning with or without a clock signal line).

You may also see the term UART around (Universal Asynchronous Receiver/Transmitter) which refers to a system which only has the option of an agreed baud rate. The system featured in AVR microcontrollers is USART, however we will be using it in it's asynchronous mode here.

## Interface

In this example, we will be using a [USB to serial converter][USB_SERIAL_CONVERTER_URL] to communicate between a PC and the AVR MCU. The connections should be made as shown in the schematic below. Note that the RX and TX (Receive and Transmit) pins are crossed over - RX on the host MCU is connected to TX on the adapter and vice versa.

![USB to Serial Adapter Schematic](./images/USB_serial_adapter_schem.png)


## Data Transmission


## API Reference


[USB_SERIAL_CONVERTER_URL]: https://www.amazon.co.uk/Ccylez-Converter-Adapter-FT232RL-Android-default/dp/B08DV1SXMQ/ref=sr_1_4?crid=8ZN3WET67TSU&keywords=usb+serial+converter+module&qid=1647296288&sprefix=usb+serial+converter+modul%2Caps%2C72&sr=8-4
