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
#include "velocity.hpp"
#include "voice.hpp"
#include "timeralarm.hpp"
#include <stdio.h>

// Change this to true to enable parallel channel mode
#define PARALLEL_CHANNELS false

using namespace pimoroni;
using namespace mico;

auto clipmode = ClipMode::WRAP;
constexpr int channel = 1;
constexpr int numEncoders = 4;
#define LED_PIN PICO_DEFAULT_LED_PIN
bool buttonState;

// A voice is an encoder with midi sender, encoder class, velocity etc.
MicoVoice voices[numEncoders]{
  MicoVoice(4, 5, 14, channel, clipmode),
  MicoVoice(2, 3, 15, channel, clipmode),
  MicoVoice(8, 9, 16, channel, clipmode),
  MicoVoice(6, 7, 17, channel, clipmode),
};

void changeClipmodes(ClipMode newMode){
  for (size_t i = 0; i < numEncoders; i++) {
	voices[i].setClipMode(newMode);
  }
}

pico_arduino::TimerAlarmRepeating miditimer;

// UART defines
// By default the stdout UART is `uart0`, so we will use the second one
#define UART_ID uart0
#define BAUD_RATE 115200

// Device mounting callbacks
void tud_mount_cb(void) {
  printf("Mico mounted\n");
} // Invoked when device is mounted
void tud_umount_cb(void) {
  printf("Mico unmounted\n");
} // Invoked when device is unmounted
void tud_suspend_cb(bool remote_wakeup_en) {
  printf("Mico suspended\n");
} // Invoked when usb bus is suspended
void tud_resume_cb(void) {
  printf("Mico resumed\n");
} // Invoked when usb bus is resumed

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

void midi_task(void) {
  for (size_t voiceNum = 0; voiceNum < numEncoders; voiceNum++) {
    voices[voiceNum].update14();
  }
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

	  changeClipmodes(clipmode);
      printf("Changed clipmode to: %d\n", clipmode);
    }
  }
}

static bool loopTask(repeating_timer_t *rt){
  tud_task(); // tinyusb device task
  button_task();
  midi_task();
  return true;
}

inline void setup() {

  printf("Setting up Mico.\n");
  buttonState = get_bootsel_button();

  for (size_t voiceNum = 0; voiceNum < numEncoders; voiceNum++) {
    voices[voiceNum].init();
  }

  // Turn on LED
  gpio_init(LED_PIN);
  gpio_set_dir(LED_PIN, GPIO_OUT);
  gpio_put(LED_PIN, 0);

  printf("Starting midi timer\n");
  miditimer.start(loopTask, 10);
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
    // sleep_ms(1);
  }

  return 0;
}
