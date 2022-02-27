# Mico Encoder
A library for reading quadrature encoders on the Raspberry Pi Pico's GPIO pins. Uses the GPIO interrupt capability to check the encoders states on edge high/low. All GPIO pins share the same callback function in the interrupt handler, so this library blocks you from using the GPIO interrupt for anything else.

## Credits
By Mads Kjeldgaard 2022. MIT Licensed.

Based on Quadrature Encoder reader using PIO originally made by Christopher (@ZodiusInfuser) Parrott / Pimoroni. MIT LICENSE. Original source: https://github.com/pimoroni/pimoroni-pico/blob/encoder-pio/drivers/encoder-pio/encoder.pio

As well as some inspiration from Paul Stoffregen's encoder lib: https://github.com/PaulStoffregen/Encoder/blob/master/Encoder.h#L301
