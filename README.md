# Raspberry Pi Oscilloscope


This project aims at developing a bare metal digital oscilloscope software tool that the uses Raspberry Pi bare metal environment [circle-stdlib](https://github.com/smuehlst/circle-stdlib) which is based on [circle](https://github.com/rsta2/circle).

The GUI is being developed using [LittlevGL](https://littlevgl.com) which is an open-source embedded GUI library.

For measuring voltage signals I have used an ADC ([TLC2543](http://www.ti.com/product/TLC2543) from Texas Instruments).

The simulation for GUI is done using the pc simulator provided by LittlevGL community. The simulation codes are available [here](https://github.com/Ashreya12/DSO-GUI).