#include "hardware/gpio.h"
#include "hardware/interp.h"
#include "hardware/pio.h"
#include "libs/encoder-pio/pioencoder.hpp"
#include "pico/stdlib.h"
#include <stdio.h>

#include "bsp/board.h"
#include "pico/binary_info.h"
#include "tusb.h"

using namespace pimoroni;

#define LED_PIN PICO_DEFAULT_LED_PIN

// Pins are GPIO pin numbers, not physical pins
PioEncoder enc1(pio0, 2, 3);
PioEncoder enc2(pio1, 4, 5);

// FIXME: These don't work. NEEDZ MORE PIO
PioEncoder enc4(pio0, 6, 7);
PioEncoder enc3(pio1, 8, 9);

// UART defines
// By default the stdout UART is `uart0`, so we will use the second one
#define UART_ID uart1
#define BAUD_RATE 9600

// Use pins 4 and 5 for UART1
// Pins can be changed, see the GPIO function select table in the datasheet for
// information on GPIO assignments
// FIXME: Will this work ? Is it neceassry?
#define UART_TX_PIN 14
#define UART_RX_PIN 15

inline void setup() {

  enc1.init();
  enc2.init();
  enc3.init();
  enc4.init();

  // Turn on LED
  gpio_init(LED_PIN);
  gpio_set_dir(LED_PIN, GPIO_OUT);
  gpio_put(LED_PIN, 1);
}

// Creates a 4 byte midi buffer and sends it as a control change midi message.
// channel is midi channel. 0 = channel 1.
// value is the midi value
// ccnum is control change number
// cable_num is MIDI jack associated with USB endpoint
// Inspired by
// https://github.com/arduino-libraries/MIDIUSB/blob/master/examples/MIDIUSB_write/MIDIUSB_write.ino
void send_cc(uint8_t channel, uint8_t value, uint8_t ccnum,
             uint8_t cable_num = 0) {
  constexpr auto size = 4;
  // First parameter is the event type (0x0B = control change).
  // Second parameter is the event type, combined with the channel.
  // Third parameter is the control number number (0-119).
  // Fourth parameter is the control value (0-127).
  // TODO: Should this be a struct instead? Would that be more compiler
  // friendly?
  const uint8_t ccbuffer[size] = {0x0B, static_cast<uint8_t>(0xB0 | channel),
                                  ccnum, value};
  tud_midi_stream_write(cable_num, ccbuffer, size);
}

void send_cc14(uint8_t channel, uint8_t value, uint8_t ccnum,
               uint8_t cable_num = 0) {
  // TODO
}

int32_t old_count1{0}, old_count2{0}, old_count3{0}, old_count4{0};

void midi_task(void) {
  // TODO: This whole function is terribly ugly... oh well.
  auto chan = 0;

  auto count1 = enc1.get_count();
  if (count1 != old_count1) {
    old_count1 = count1;

    auto ccnum = 1;
    auto val = (count1 < 0)? 0 : count1 % 127;

    send_cc(chan, val, ccnum);
  };

  auto count2 = enc2.get_count();
  if (count2 != old_count2) {
    old_count2 = count2;

    auto ccnum = 2;
    auto val = count2 % 127;
    send_cc(chan, val, ccnum);
  };

  auto count3 = enc3.get_count();
  if (count3 != old_count3) {
    old_count3 = count3;

    auto ccnum = 3;
    auto val = count3 % 127;
    send_cc(chan, val, ccnum);
  };

  auto count4 = enc4.get_count();
  if (count4 != old_count4) {
    old_count4 = count4;

    auto ccnum = 4;
    auto val = count4 % 127;
    send_cc(chan, val, ccnum);
  };
}

int main() {
  stdio_init_all();
  tusb_init();
  setup();
  // TODO: Is this already done by Pico sdk?
  board_init();

  // Set up our UART
  // uart_init(UART_ID, BAUD_RATE);
  // Set the TX and RX pins by using the function select on the GPIO
  // Set datasheet for more information on function select
  // gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
  // gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

  // GPIO initialisation.
  // We will make this GPIO an input, and pull it up by default
  // gpio_init(GPIO);
  // gpio_set_dir(GPIO, GPIO_IN);
  // gpio_pull_up(GPIO);

  while (true) {
    tud_task(); // tinyusb device task
    midi_task();
    sleep_ms(1);
  }

  return 0;
}
