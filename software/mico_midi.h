/*
 * This header wraps some of the tinyusb functions and makes them slightly more
 * convenient as well as a bunch of convenience functions for 14 bit midi etc.
 *
 */
#pragma once

#ifndef MICOMIDI
#define MICOMIDI

#include "tusb.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h> /* abs */

namespace mico {
const uint8_t buffer_size = 4;
uint8_t ccbuffer[buffer_size];

typedef struct {
  uint8_t header;
  uint8_t byte1;
  uint8_t byte2;
  uint8_t byte3;
} midiEventPacket_t;

constexpr auto maxValue14Bit = pow(2, 14);

enum class ClipMode { WRAP, CLAMP };

// Clamp value between 0 and maximum 14 bit value
inline int clamp14(int inVal) {
  if (inVal < 0) {
    return 0;
  } else if (inVal > maxValue14Bit) {
    return maxValue14Bit;
  } else {
    return inVal;
  }
}

// Wrap value between 0 and maximum 14 bit value
inline int wrap14(int in) {
  constexpr auto max = maxValue14Bit;
  const auto min = 0;
  if (in > max) {
    in = min + (in - max);
    return in;
  } else if (in < min) {
    in = max - std::abs(min - in);
    return in;
  } else {
    return in;
  }
}

// Wraps or clamps a 14 bit midi value
int wrap_or_clamp14(int inVal, ClipMode datamode) {
  switch (datamode) {
  case ClipMode::WRAP:
    return wrap14(inVal);
    break;
  case ClipMode::CLAMP:
    return clamp14(inVal);
    break;
  default:
    return 0;
    break;
  };
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
  // First parameter is the event type (0x0B = control change).
  // Second parameter is the event type, combined with the channel.
  // Third parameter is the control number number (0-119).
  // Fourth parameter is the control value (0-127).
  // TODO: Should this be a struct instead? Would that be more compiler
  // friendly?
  ccbuffer[0] = 0x0B;
  ccbuffer[1] = static_cast<uint8_t>(0xB0 | channel);
  ccbuffer[2] = ccnum;
  ccbuffer[3] = value;

  tud_midi_stream_write(cable_num, ccbuffer, buffer_size);
}

// Send a 14 bit midi message.
// CC numbers are ccnum for lower bit and ccnum+32 for higher bit.
void send_cc14(uint8_t channel, uint16_t value, uint8_t ccnum,
               uint8_t cable_num = 0) {

  // Lower 7 bits of signal
  const auto lowBitVal = value & 0x7F;

  // Upper 7 bits of signal
  const auto highBitVal = (value >> 7) & 0x7F;

  send_cc(channel, lowBitVal, ccnum + 32, cable_num);
  send_cc(channel, highBitVal, ccnum, cable_num);
}

}; // namespace mico

#endif /* !MICOMIDI */
