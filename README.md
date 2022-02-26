# Mico - a matchbox sized midi controller based on the Raspberry Pi Pico RPI2040

## BOM

| Quantity | Part | Mouser Number |
|---|---|---|
| 1 | Raspberry Pi Pico rpi2040 | n/a |
| 8 | 0.01uF capacitor, 0603 | Mouser Number |
| 16 | 10k resistors, 1%, 0603 | Mouser Number |
| 4 | Detentless encoders | [652-PEC11R-4015K-N24](https://no.mouser.com/ProductDetail/652-PEC11R-4015K-N24) |


## Building the firmware

### Using picoprobe

```bash
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
