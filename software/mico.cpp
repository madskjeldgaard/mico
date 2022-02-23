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

constexpr auto pinA = 12;
constexpr auto pinB = 13;
PIO pio = pio0;
Encoder enc1(pio, pinA, pinB);

// UART defines
// By default the stdout UART is `uart0`, so we will use the second one
#define UART_ID uart1
#define BAUD_RATE 9600

// Use pins 4 and 5 for UART1
// Pins can be changed, see the GPIO function select table in the datasheet for
// information on GPIO assignments
#define UART_TX_PIN 4
#define UART_RX_PIN 5

inline void setup(){

  enc1.init();

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
	auto capture = enc1.perform_capture();
	auto count = enc1.get_count();
	// printf("Hello, world!\n");
	printf("count: %d\n", count);
	printf("state a: %d\n", enc1.get_state_a());
	printf("state a: %d\n", enc1.get_state_a());
	// printf("state b: %d", enc1.get_state_b());
	// printf("%d\n", count);
	sleep_ms(100);
  }

  return 0;
}
