#include "micoencoder.hpp"
#include "hardware/irq.h"
#include "hardware/gpio.h"
#include <cstdio>
#include <climits>
#include <math.h>
#include "hardware/structs/systick.h"

#define LAST_STATE(state) ((state)&0b0011)
#define CURR_STATE(state) (((state)&0b1100) >> 2)

namespace mico {

#include "hardware/clocks.h"

#define encoder_wrap_target 0
#define encoder_wrap 10
#define ENC_DEBOUNCE_CYCLES 490
static const uint8_t ENC_LOOP_CYCLES = encoder_wrap - encoder_wrap_target;
static const uint8_t ENC_DEBOUNCE_TIME = ENC_DEBOUNCE_CYCLES / ENC_LOOP_CYCLES;

////////////////////////////////////////////////////////////////////////////////////////////////////
// STATICS
////////////////////////////////////////////////////////////////////////////////////////////////////

// This will hold all instances of the encoder. This is because there is only
// one gpio callback function per core and so this will help sort out which
// encoder caused the interrupt.
MicoEncoder *MicoEncoder::mico_encoders[NUM_BANK0_GPIOS] = {
    nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
    nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
    nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
    nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// TODO: arguments unused
void MicoEncoder::gpio_callback(uint gpio, uint32_t events) {
for (uint8_t encNum = 0; encNum < NUM_BANK0_GPIOS; encNum++) {
    if (mico_encoders[encNum] != nullptr) {
      mico_encoders[encNum]->check_for_transition();
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTORS / DESTRUCTOR
////////////////////////////////////////////////////////////////////////////////////////////////////

// TODO
MicoEncoder::MicoEncoder(uint8_t pinA, uint8_t pinB, uint8_t pinC,
                         float counts_per_revolution, bool count_microsteps,
                         uint16_t freq_divider)
    : pinA(pinA), pinB(pinB), pinC(pinC),
      counts_per_revolution(counts_per_revolution),
      count_microsteps(count_microsteps), freq_divider(freq_divider),
      clocks_per_time(
          (float)(clock_get_hz(clk_sys) / (ENC_LOOP_CYCLES * freq_divider))) {}

////////////////////////////////////////////////////////////////////////////////////////////////////

MicoEncoder::~MicoEncoder() {
  // Clean up our use of the SM associated with this encoder
  const auto index = get_index();
  mico_encoders[index] = nullptr;

}

////////////////////////////////////////////////////////////////////////////////////////////////////
// METHODS
////////////////////////////////////////////////////////////////////////////////////////////////////

// Iterates over the static array containing encoders and sets the member variable this_index to equal the first non-nullptr index in the static encoder array.
void MicoEncoder::set_index(){

  for (size_t i = 0; i < NUM_BANK0_GPIOS; i++) {
	if ( mico_encoders[i] == nullptr) {
	  this_index = i;
	  break;
	}
  }

}

uint MicoEncoder::get_index(){
  return this_index;
}

bool MicoEncoder::init() {
  bool initialised = false;

  // TODO: Should this be mentioned in docs?
  // From: https://forums.raspberrypi.com/viewtopic.php?f=145&t=304201&p=1820770&hilit=Hermannsw+systick#p1822677
  systick_hw->csr = 0x5;
  systick_hw->rvr = 0x00FFFFFF;
  int32_t cycles_now = systick_hw->cvr;
  cycles_last = cycles_now; // Cache for next iteration

  // Are the pins we want to use actually valid?
  if ((pinA < NUM_BANK0_GPIOS) && (pinB < NUM_BANK0_GPIOS)) {
	set_index();

    // Setup Pin A and B
    gpio_init(pinA);
    gpio_init(pinB);
    gpio_set_dir(pinA, GPIO_IN);
    gpio_set_dir(pinB, GPIO_IN);
    gpio_put(pinA, false);
    gpio_put(pinB, false);
    // TODO: Not sure about this:
    gpio_pull_up(pinA);
    gpio_pull_up(pinB);

    // the callback here is universal. Will be called for all pins'
    // interrupt
    gpio_set_irq_enabled_with_callback(
        pinA, // NOTE: Currently ignored by the SDK since the callback is called
              // for all gpio interrupts on this processor
		// TODO: Is this correct?
        GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true,
        &gpio_callback // pio0_interrupt_callback
    );
    gpio_set_irq_enabled_with_callback(
        pinB, // NOTE: Currently ignored by the SDK since the callback is called
              // for all gpio interrupts on this processor
        GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true,
        &gpio_callback // pio0_interrupt_callback
    );

    // If a Pin C was defined, and valid, set it as a GND to pull the other two
    // pins down
    if ((pinC != PIN_UNUSED) && (pinC < NUM_BANK0_GPIOS)) {
      gpio_init(pinC);
      gpio_set_dir(pinC, GPIO_OUT);
      gpio_put(pinC, false);
    }

    auto index = get_index();

    // Keep a record of this encoder for the interrupt callback
    mico_encoders[index] = this;

    // Read the current state of the encoder pins
    stateA = gpio_get(pinA);
    stateB = gpio_get(pinB);

    initialised = true;
  }
  return initialised;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool MicoEncoder::get_state_a() const { return stateA; }

////////////////////////////////////////////////////////////////////////////////////////////////////
bool MicoEncoder::get_state_b() const { return stateB; }

////////////////////////////////////////////////////////////////////////////////////////////////////
int32_t MicoEncoder::get_count() const { return count - count_offset; }

////////////////////////////////////////////////////////////////////////////////////////////////////
float MicoEncoder::get_revolutions() const {
  return (float)get_count() / counts_per_revolution;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float MicoEncoder::get_angle_degrees() const {
  return get_revolutions() * 360.0f;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float MicoEncoder::get_angle_radians() const {
  return get_revolutions() * M_TWOPI;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float MicoEncoder::get_frequency() const {
  return clocks_per_time / (float)time_since;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float MicoEncoder::get_revolutions_per_second() const {
  return get_frequency() / counts_per_revolution;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float MicoEncoder::get_revolutions_per_minute() const {
  return get_revolutions_per_second() * 60.0f;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float MicoEncoder::get_degrees_per_second() const {
  return get_revolutions_per_second() * 360.0f;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float MicoEncoder::get_radians_per_second() const {
  return get_revolutions_per_second() * M_TWOPI;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MicoEncoder::zero_count() { count_offset = count; }

////////////////////////////////////////////////////////////////////////////////////////////////////
Capture MicoEncoder::perform_capture() {
  // Capture the current values
  int32_t captured_count = count;
  int32_t captured_cumulative_time = cumulative_time;
  cumulative_time = 0;

  // Determine the change in counts since the last capture was performed
  int32_t count_change = captured_count - last_captured_count;
  last_captured_count = captured_count;

  // Calculate the average frequency of state transitions
  float average_frequency = 0.0f;
  if (count_change != 0 && captured_cumulative_time != INT_MAX) {
    average_frequency = (clocks_per_time * (float)count_change) /
                        (float)captured_cumulative_time;
  }

  return Capture(captured_count, count_change, average_frequency,
                 counts_per_revolution);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MicoEncoder::microstep_up(int32_t time) {
  count++;
  time_since = time;
  microstep_time = 0;

  if (time + cumulative_time < time) // Check to avoid integer overflow
    cumulative_time = INT_MAX;
  else
    cumulative_time += time;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MicoEncoder::microstep_down(int32_t time) {
  count--;
  time_since = 0 - time;
  microstep_time = 0;

  if (time + cumulative_time < time) // Check to avoid integer overflow
    cumulative_time = INT_MAX;
  else
    cumulative_time += time;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

// TODO

// Check for transition and update count if any
void MicoEncoder::check_for_transition() {

  // stateA = (bool)(received & STATE_A_MASK);
  stateA = (bool)(gpio_get(pinA));
  // stateB = (bool)(received & STATE_B_MASK);
  stateB = (bool)(gpio_get(pinB));

  // Inspired by https://github.com/PaulStoffregen/Encoder/blob/master/Encoder.h#L301
  // uint8_t states = (stateA & stateB);
  states = states & 3;
  if(stateA) states |= 4;
  if(stateB) states |= 8;

  // uint8_t states = (received & STATES_MASK) >> 28;

  // Extract the time (in cycles) it has been since the last received
  int32_t cycles_now = systick_hw->cvr;
  int32_t time_received = ( cycles_now - cycles_last) + ENC_DEBOUNCE_TIME;
  cycles_last = time_received; // Cache for next iteration
  // int32_t time_received = (received & TIME_MASK) + ENC_DEBOUNCE_TIME;

  // TODO: Is this needed?
  // For rotary encoders, only every fourth transition is cared about, causing
  // an inaccurate time value To address this we accumulate the times received
  // and zero it when a transition is counted
  if (!count_microsteps) {
	if (time_received + microstep_time <
	  time_received) // Check to avoid integer overflow
	  time_received = INT32_MAX;
	else
	  time_received += microstep_time;
	microstep_time = time_received;
  }

  switch (states) {
	case 1: case 7: case 8: case 14:
	// 	// A ____|‾‾‾‾
	// 	// B _________
		  // if (count_microsteps)
			microstep_up(time_received);

		  last_travel_dir = COUNTERCLOCK; // Started turning counter-clockwise
		  break;

	// 	// A ‾‾‾‾‾‾‾‾‾
	// 	// B ‾‾‾‾|____
	case 2: case 4: case 11: case 13:
		  // if (count_microsteps)
			microstep_down(time_received);
		  last_travel_dir = COUNTERCLOCK; // Started turning counter-clockwise
		  break;
  	default:
  		break;
  }

  // Determine what transition occurred
 //  switch (LAST_STATE(states)) {
	// //--------------------------------------------------
	// case MICROSTEP_0:
	//   switch (CURR_STATE(states)) {
	// 	// A ____|‾‾‾‾
	// 	// B _________
	// 	case MICROSTEP_1:
	// 	  if (count_microsteps)
	// 		microstep_up(time_received);
	// 	  break;
	//
	// 	// A _________
	// 	// B ____|‾‾‾‾
	// 	case MICROSTEP_3:
	// 	  if (count_microsteps)
	// 		microstep_down(time_received);
	// 	  break;
	//   }
	//   break;
	//
	// //--------------------------------------------------
	// case MICROSTEP_1:
	//   switch (CURR_STATE(states)) {
	// 	// A ‾‾‾‾‾‾‾‾‾
	// 	// B ____|‾‾‾‾
	// 	case MICROSTEP_2:
	// 	  if (count_microsteps || last_travel_dir == CLOCKWISE)
	// 		microstep_up(time_received);
	//
	// 	  last_travel_dir = NO_DIR; // Finished turning clockwise
	// 	  break;
	//
	// 	// A ‾‾‾‾|____
	// 	// B _________
	// 	case MICROSTEP_0:
	// 	  if (count_microsteps)
	// 		microstep_down(time_received);
	// 	  break;
	//   }
	//   break;
	//
	// //--------------------------------------------------
	// case MICROSTEP_2:
	//   switch (CURR_STATE(states)) {
	// 	// A ‾‾‾‾|____
	// 	// B ‾‾‾‾‾‾‾‾‾
	// 	case MICROSTEP_3:
	// 	  if (count_microsteps)
	// 		microstep_up(time_received);
	//
	// 	  last_travel_dir = CLOCKWISE; // Started turning clockwise
	// 	  break;
	//
	// 	// A ‾‾‾‾‾‾‾‾‾
	// 	// B ‾‾‾‾|____
	// 	case MICROSTEP_1:
	// 	  if (count_microsteps)
	// 		microstep_down(time_received);
	//
	// 	  last_travel_dir = COUNTERCLOCK; // Started turning counter-clockwise
	// 	  break;
	//   }
	//   break;
	//
	// //--------------------------------------------------
	// case MICROSTEP_3:
	//   switch (CURR_STATE(states)) {
	// 	// A _________
	// 	// B ‾‾‾‾|____
	// 	case MICROSTEP_0:
	// 	  if (count_microsteps)
	// 		microstep_up(time_received);
	// 	  break;
	//
	// 	// A ____|‾‾‾‾
	// 	// B ‾‾‾‾‾‾‾‾‾
	// 	case MICROSTEP_2:
	// 	  if (count_microsteps || last_travel_dir == COUNTERCLOCK)
	// 		microstep_down(time_received);
	//
	// 	  last_travel_dir = NO_DIR; // Finished turning counter-clockwise
	// 	  break;
	//   }
	//   break;
 //  }

  states = states >> 2;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace mico
