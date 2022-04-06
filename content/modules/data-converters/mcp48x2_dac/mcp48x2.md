@ingroup mcp48x2

## Introduction
The MCP48x2 series from Microchip are dual buffered output [Digital to Analog converters][DAC_URL] available in 8 bit, 10 bit and 12 bit resolutions. These devices operate from a single 2.7V to 5.5V supply and an [SPI][SPI_URL] interface, and can be used for sensor calibration, hardware self-testing, op-amp control, programmable voltage reference and  more.

This module was tested on an MCP4812 10 bit DAC, but should also work with the other models if configured correctly. The datasheet for all 3 devices can be found [here][MCP48x2_Datasheet_URL].

## Hookup
The host MCU sends data to the DAC using the SPI (Serial Peripheral Interface) protocol. For a quick guide on SPI communication, take a look at the module [here][SPI_Module_URL].


## API Reference

Before initialising the DAC for use, you'll need to instantiate a dac_config_t object, and set the configuration values you'd like.

```C
dac_config_t dac_config =
{
	.model = mcp4812,
	.sync_manually = false,

	.channel_a.gain_low = false,
	.channel_a.active = true,
	.channel_a.level = 0,

	.channel_b.gain_low = false,
	.channel_b.active = true,
	.channel_b.level = 0,
};
```
### Members
- model: Valid selections are mcp4802, mcp4812 or mcp4822.
- sync_manually: true = manual sync, false = sync automatically.


[DAC_URL]: https://en.wikipedia.org/wiki/Digital-to-analog_converter
[SPI_URL]: https://en.wikipedia.org/wiki/Serial_Peripheral_Interface
[MCP48x2_Datasheet_URL]: https://ww1.microchip.com/downloads/en/DeviceDoc/20002249B.pdf