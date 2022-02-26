#include "hardware/gpio.h"
#include "hardware/interp.h"
#include "hardware/pio.h"
#include "libs/encoder-pio/pioencoder.hpp"
#include "mico_midi.h"
#include "pico/stdlib.h"
#include <stdio.h>

#include "bsp/board.h"
#include "pico/binary_info.h"
#include "tusb.h"

using namespace pimoroni;
using namespace mico;

constexpr auto clipmode = ClipMode::WRAP;
#define LED_PIN PICO_DEFAULT_LED_PIN

// Pins are GPIO pin numbers, not physical pins
PioEncoder enc1(pio0, 2, 3);
PioEncoder enc2(pio1, 4, 5);

// FIXME: These don't work. NEEDZ MORE PIO
PioEncoder enc4(pio0, 6, 7);
PioEncoder enc3(pio1, 8, 9);

// UART defines
// By default the stdout UART is `uart0`, so we will use the second one
#define UART_ID uart0
#define BAUD_RATE 115200

// Use pins 1 and 5 for UART1
// Pins can be changed, see the GPIO function select table in the datasheet for
// information on GPIO assignments
// FIXME: Will this work ? Is it neceassry?
// #define UART_TX_PIN 1
// #define UART_RX_PIN 2

inline void setup() {

  printf("Setting up Mico.\n");

  enc1.init();
  enc2.init();
  enc3.init();
  enc4.init();

  // Turn on LED
  gpio_init(LED_PIN);
  gpio_set_dir(LED_PIN, GPIO_OUT);
  gpio_put(LED_PIN, 1);
}

int32_t old_count1{0}, old_count2{0}, old_count3{0}, old_count4{0};

void midi_task(void) {
  // TODO: This whole function is terribly ugly... oh well.
  auto chan = 0;

  auto count1 = enc1.get_count();
  if (count1 != old_count1) {
    old_count1 = count1;

    auto ccnum = 1;
    auto val = wrap_or_clamp14(count1, clipmode);

    printf("enc1: ");
    printf("%d\n", val);
    send_cc14(chan, val, ccnum);
  };

  auto count2 = enc2.get_count();
  if (count2 != old_count2) {
    old_count2 = count2;

    auto ccnum = 2;
	auto val = wrap_or_clamp14(count2, clipmode);

    printf("enc2: ");
    printf("%d\n", val);

    send_cc14(chan, val, ccnum);
  };

  auto count3 = enc3.get_count();
  if (count3 != old_count3) {
    old_count3 = count3;

    auto ccnum = 3;
	auto val = wrap_or_clamp14(count3, clipmode);

    printf("enc3: ");
    printf("%d\n", val);

    send_cc14(chan, val, ccnum);
  };

  auto count4 = enc4.get_count();
  if (count4 != old_count4) {
    old_count4 = count4;

    auto ccnum = 4;
	auto val = wrap_or_clamp14(count4, clipmode);

    printf("enc4: ");
    printf("%d\n", val);

    send_cc14(chan, val, ccnum);
  };
}

int main() {
  printf("Starting Mico main loop.\n");
  // TODO: Is this already done by Pico sdk?
  board_init();
  // Set up our UART
  uart_init(UART_ID, BAUD_RATE);
  stdio_init_all();
  tusb_init();
  setup();
  // Set the TX and RX pins by using the function select on the GPIO
  // Set datasheet for more information on function select
  // gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
  // gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

  // GPIO initialisation.
  // We will make this GPIO an input, and pull it up by default
  // gpio_init(GPIO);
  // gpio_set_dir(GPIO, GPIO_IN);
  // gpio_pull_up(GPIO);

  printf("Starting Mico loop.\n");
  while (true) {
    tud_task(); // tinyusb device task
    midi_task();
    sleep_ms(1);
  }

  return 0;
}
