# Vesuvius First Word Badge Firmware (for Raspberry Pi Pico)

This is the firmware for the Vesuvius First Word Badge (in Rapberry Pi Pico configuration), a badge that displays the first word found
in burnt papyrus scrolls analyzed for the [Vesuvius Challenge](https://scrollprize.substack.com/p/first-word-discovered-in-unopened).

Read more about the hardware of the badge in this [blog post](https://vesuvius.virtual-void.net/blog/2024/01/10/vesuvius-badge-hardware/), and
in the [hardware design repository](https://github.com/jrudolph/vesuvius-badge).

## Building the Firmware

This project depends on the [pico-sdk](https://github.com/raspberrypi/pico-sdk) and downloads the sdk automatically during the cmake build process. If you have
the Pico SDK installed in a different location, you can set the `PICO_SDK_PATH` environment variable to point to the location of the SDK (and avoid
the download).

To build under Linux, you will have to install the toolchain as outlined in [Getting Started with Raspberry Pi Pico (pdf)](https://datasheets.raspberrypi.com/pico/getting-started-with-pico.pdf#%5B%7B%22num%22%3A10%2C%22gen%22%3A0%7D%2C%7B%22name%22%3A%22XYZ%22%7D%2C115%2C629.322%2Cnull%5D)

```bash
$ sudo apt install cmake gcc-arm-none-eabi libnewlib-arm-none-eabi build-essential
```

Then you can build the firmware with

```bash
$ mkdir build
$ cd build
$ cmake ..
$ make -j
```

this should create a `vesuvius-badge.uf2` which you can copy to the Raspberry Pi Pico using the UF2 bootloader.


## Hardware Notes

As outlined in the [blog post]([this blogpost](https://vesuvius.virtual-void.net/blog/2024/01/10/vesuvius-badge-hardware/)) mentioned above, the
badge can be configured with different hardware options.

This firmware assumes that the Pico is soldered to the back of the board, or connected via the break out pins.
- Power:
    - The power lines for the LED driver are connected to the Pico's 3.3V output i.e. reusing the buck/boost converter on the Pico board.
    - Options:
        - Usually (and most easily) powered through the Pico USB port (make sure to use a regular 5V USB power supply, like a mobile phone charger,
          there are some non-standard USB power supplies on the market for bespoke devices with higher voltage that will damage the hardware).
        - Optionally, the battery pin header on the board can be populated and any voltage source between 1.8V and 5.5V can be connected there.
        - **Note**: Do not connect a battery to the battery pin header and USB power at the same time. The USB port is protected via a schottky diode,
        but the battery is not. A battery will be exposed to the 5V from the USB port if connected at the same time, which will damage
        the battery with potentially grave consequences (fire, leakage, etc).
- Data:
    - GPIO pins 16/17 of the Pico will be used for I2C communication with the LED driver.

![Vesuvius Badge x3](https://raw.githubusercontent.com/jrudolph/vesuvius-badge/main/media/vesuvius-badge-3x.webp)