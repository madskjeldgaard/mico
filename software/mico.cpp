#include "bsp/board.h"
#include "hardware/gpio.h"
#include "hardware/interp.h"
#include "hardware/pio.h"
#include "hardware/structs/ioqspi.h"
#include "hardware/structs/sio.h"
#include "libs/encoder-pio/pioencoder.hpp"
#include "mico_midi.h"
#include "micoencoder.hpp"
#include "pico/binary_info.h"
#include "pico/stdlib.h"
#include "tusb.h"
#include <stdio.h>

using namespace pimoroni;
using namespace mico;

auto clipmode = ClipMode::WRAP;
#define LED_PIN PICO_DEFAULT_LED_PIN

// Pins are GPIO pin numbers, not physical pins
PioEncoder enc1(pio0, 2, 3);
PioEncoder enc2(pio1, 4, 5);

// FIXME: These don't work.
MicoEncoder enc4(6, 7);
MicoEncoder enc3(8, 9);

// UART defines
// By default the stdout UART is `uart0`, so we will use the second one
#define UART_ID uart0
#define BAUD_RATE 115200

// Picoboard has a button attached to the flash CS pin, which the bootrom
// checks, and jumps straight to the USB bootcode if the button is pressed
// (pulling flash CS low). We can check this pin in by jumping to some code in
// SRAM (so that the XIP interface is not required), floating the flash CS
// pin, and observing whether it is pulled low.
//
// This doesn't work if others are trying to access flash at the same time,
// e.g. XIP streamer, or the other core.

bool __no_inline_not_in_flash_func(get_bootsel_button)() {
  const uint CS_PIN_INDEX = 1;

  // Must disable interrupts, as interrupt handlers may be in flash, and we
  // are about to temporarily disable flash access!
  uint32_t flags = save_and_disable_interrupts();

  // Set chip select to Hi-Z
  hw_write_masked(&ioqspi_hw->io[CS_PIN_INDEX].ctrl,
                  GPIO_OVERRIDE_LOW << IO_QSPI_GPIO_QSPI_SS_CTRL_OEOVER_LSB,
                  IO_QSPI_GPIO_QSPI_SS_CTRL_OEOVER_BITS);

  // Note we can't call into any sleep functions in flash right now
  for (volatile int i = 0; i < 1000; ++i)
    ;

  // The HI GPIO registers in SIO can observe and control the 6 QSPI pins.
  // Note the button pulls the pin *low* when pressed.
  bool button_state = !(sio_hw->gpio_hi_in & (1u << CS_PIN_INDEX));

  // Need to restore the state of chip select, else we are going to have a
  // bad time when we return to code in flash!
  hw_write_masked(&ioqspi_hw->io[CS_PIN_INDEX].ctrl,
                  GPIO_OVERRIDE_NORMAL << IO_QSPI_GPIO_QSPI_SS_CTRL_OEOVER_LSB,
                  IO_QSPI_GPIO_QSPI_SS_CTRL_OEOVER_BITS);

  restore_interrupts(flags);

  return button_state;
}

bool buttonState;

inline void setup() {

  printf("Setting up Mico.\n");
  buttonState = get_bootsel_button();
  enc1.init();
  enc2.init();
  enc3.init();
  enc4.init();

  // Turn on LED
  gpio_init(LED_PIN);
  gpio_set_dir(LED_PIN, GPIO_OUT);
  gpio_put(LED_PIN, 0);
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

void button_task() {
  auto newState = get_bootsel_button();
  if (buttonState != newState) {
    buttonState = newState;

    // Toggle
    if (buttonState == 1) {
      switch (clipmode) {
      case ClipMode::CLAMP:
        clipmode = ClipMode::WRAP;
        gpio_put(LED_PIN, 0);
        break;
      case ClipMode::WRAP:
        clipmode = ClipMode::CLAMP;
        gpio_put(LED_PIN, 1);
        break;
      }

      printf("Changed clipmode to: %d\n", clipmode);
    }
  }
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

  printf("Starting Mico loop.\n");

  while (true) {
    tud_task(); // tinyusb device task
    button_task();
    midi_task();
    sleep_ms(1);
  }

  return 0;
}
