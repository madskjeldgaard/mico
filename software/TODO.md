Bugs:
- Button hole in enclosure
- debug hole in enclosure
- Properly clamp values under 0 in the encoder itself.

Features:
- VelocityTrigger
- Inverse on adjacent midi channel. So if enc1 is high on midi channel 0, then send inverse of that to 1 on channel 1
- Set wrap mode per encoder (hold button and wiggle encoder)
- Interpolation / lag
- Add interpolated random envelope mode
- save options in flash: https://github.com/raspberrypi/pico-examples/blob/master/flash/program/flash_program.c

Misc:
- Move encoder stuff to seperate library
- Remove all the microstep leftovers from gpio-encoder
- semaphores around usb midi stuff like in arduino_pico?
