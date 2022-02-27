# Mico - midi controller based on the Raspberry Pi Pico RPI2040

Mico is a small, cheap (~10 euros total) and super precise 14 bit midi controller based on the [Raspberry Pi Pico board](https://www.raspberrypi.com/products/raspberry-pi-pico/).

## Features
- 4 x detentless (smooth) encoders 
- A variety of "clip modes" (cycle through them by pressing the button):
 	- wrap (when the value goes above max, it wraps back to 0) 
 	- clamp (clip at min and max value)
- 14 bit midi (as well as regular 7 bit midi)
- Cheap as chips and open sourced

## BOM

| Quantity | Part | Mouser Number |
|---|---|---|
| 1 | Raspberry Pi Pico rpi2040 | n/a |
| 8 | 0.01uF capacitor, 0603 | Mouser Number |
| 16 | 10k resistors, 1%, 0603 | Mouser Number |
| 4 | Detentless encoders | [652-PEC11R-4015K-N24](https://no.mouser.com/ProductDetail/652-PEC11R-4015K-N24) |


## Uploading the firmware

Download the latest firmware from the release and locate the `mico.uf2` file. While plugging your Pico into your computer, press and hold the "BOOTSEL" button. It will show up as a storage device on your computer. Copy `mico.uf2` to this device. Done.


## Building and uploading the firmware (optional)

If you want to build the code and mess around with it, it is recommended to use a second Pico flashed with the [picoprobe](https://github.com/raspberrypi/picoprobe) firmware.

### Using picoprobe

```bash
cd software
mkdir build
cd build 
cmake ..
make && openocd -f interface/picoprobe.cfg -f target/rp2040.cfg -c "program mico.elf verify reset exit"
```
Debug:
```bash
openocd -f interface/picoprobe.cfg -f target/rp2040.cfg -s tcl
```

## Credits

These projects were a big help and inspiration in making this:
- [pico-example-midi](https://github.com/infovore/pico-example-midi)
- [encoder-pio](https://github.com/pimoroni/pimoroni-pico) is from the pimoroni-pico library. MIT Licensed.
