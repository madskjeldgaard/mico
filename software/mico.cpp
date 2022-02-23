// #include "hardware/clocks.h"
// #include "hardware/divider.h"
#include "hardware/gpio.h"
#include "hardware/interp.h"
// #include "hardware/pio.h"
// #include "hardware/timer.h"
// #include "hardware/uart.h"
// #include "hardware/watchdog.h"
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include <stdio.h>
#include "libs/encoder-pio/encoder.hpp"

using namespace pimoroni;

#define LED_PIN PICO_DEFAULT_LED_PIN

// Pins are GPIO pin numbers, not physical pins
// PIO pio = pio0;
Encoder enc1(pio0, 2, 3);
Encoder enc2(pio1, 4, 5);

// FIXME: These don't work. NEEDZ MORE PIO
Encoder enc3(pio1, 6, 7);
Encoder enc4(pio1, 8, 9);

// UART defines
// By default the stdout UART is `uart0`, so we will use the second one
#define UART_ID uart1
#define BAUD_RATE 9600

// Use pins 4 and 5 for UART1
// Pins can be changed, see the GPIO function select table in the datasheet for
// information on GPIO assignments
#define UART_TX_PIN 14
#define UART_RX_PIN 5

inline void setup(){

  enc1.init();
  enc2.init();
  enc3.init();
  enc4.init();

  // Turn on LED
  gpio_init(LED_PIN);
  gpio_set_dir(LED_PIN, GPIO_OUT);
  gpio_put(LED_PIN, 1);

}

int main() {
  stdio_init_all();
  setup();

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
	auto count1 = enc1.get_count();
	auto count2 = enc2.get_count();
	auto count3 = enc3.get_count();
	auto count4 = enc4.get_count();

	printf("count1: %d\n", count1);
	printf("count2: %d\n", count2);
	printf("count3: %d\n", count3);
	printf("count4: %d\n", count4);

	sleep_ms(200);
  }

  return 0;
}
