### Interfacing ADC with Raspberry Pi

This directory contains code for reading data from ADC over SPI protocol. The code reads the sampled data and displays it on the screen as an 12-bit integer (0 to 4095).

Some technical specifications of ADC TLC2543:

 - 12-bit resolution
 - 11 input channels
 - Sampling rate upto 66 kSPS

For more information visit the [product page](http://www.ti.com/product/TLC2543) on Texas Instruments website.
#### Pin Connections
| Raspberry Pi | TLC2543 |
|--------------|---------|
|SCLK (GPIO11)| I/O Clock (18) |
|MOSI (GPIO10)| Data In (17) |
|MISO (GPIO9)|Data Out (16)|
|CE0 (GPIO8)|CS (15)|

**Note :**  Raspberry Pi works on 3.3 volts, so it is advised to use the ADC with the same voltage level of 3.3 volts. If higher voltage is used make sure that the above communication pins are connected via a voltage translator. Do not forget to connect REF+ and REF- pins to VCC and GND respectively.

