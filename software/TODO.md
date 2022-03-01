Bugs:
- Properly clamp values under 0 in the encoder itself.

Features:
- save options in flash: https://github.com/raspberrypi/pico-examples/blob/master/flash/program/flash_program.c
- Set wrap mode per encoder (hold button and wiggle encoder)
- semaphores around usb midi stuff like in arduino_pico?
- Add interpolated random envelope mode

Misc:
- Move encoder stuff to seperate library
- Remove all the microstep leftovers from gpio-encoder
