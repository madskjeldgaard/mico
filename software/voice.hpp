#pragma once
#include "mico_midi.h"
#include "micoencoder.hpp"
#include "velocity.hpp"

namespace mico {

// Only used in parallel mode
enum Channel {
  NORMAL,
  INVERTED,
  VELOCITY,
  VELOCITYTRIG,
  // SINE, //TODO: Make wavetable
  // EXP, //TODO: Make wavetable
};

// Wraps around an encoder and it's values and helper functions
class MicoVoice {
public:
  MicoVoice(uint8_t gpiopinA, uint8_t gpiopinB, uint8_t ccNum, uint8_t channel,
            ClipMode clipMode)
      : pinA(gpiopinA), pinB(gpiopinB), enc(gpiopinA, gpiopinB), ccnum(ccNum),
        chan(channel), clipmode(clipMode) {}

  void init() {
    enc.init();
    velocity.init();
  }

  void setClipMode(ClipMode newMode){
	clipmode = newMode;
  }

  // Get encoder value, warp it and add velocity before sending it as 14 bit
  // midi
  void update14() {
    count = enc.get_count();
    if (count != old_count) {

      auto deltaval = velocity.next14();
      val += enc.get_direction() * deltaval;
      val = wrap_or_clamp14(val, clipmode);

      printf("Enc on pin %d and %d: ", pinA, pinB);
      printf("%d\n", val);
      printf("Sending to chan %d midicc %d\n\n", chan, ccnum);
      send_all(chan, val, ccnum);

      old_count = count;
    };
  }

private:
  // Send all midi cc data and derivatives
  void send_all(int firstchan, int midi14val, int ccnum) {

    // Normal
    send_cc14(firstchan + Channel::NORMAL, midi14val, ccnum);

#if PARALLEL_CHANNELS
    // Inverted
    send_cc14(firstchan + Channel::INVERTED, maxValue14Bit - midi14val, ccnum);

    // Velocity
    constexpr auto velocity14step = maxValue14Bit / velocity.num_speed_levels;
    const auto velocityval = velocity.speed_level * velocity14step;
    send_cc14(firstchan + Channel::VELOCITY, velocityval,
              ccnum);

    // Velocity trigger
	// TODO: Make it work
	// TODO: Remove magic number (3)
	const auto newTrig = velocity.speed_level > 2;
	if(newTrig != oldTrig) {
	  const auto note = 47 + ccnum;
	  if(newTrig == true){
		// noteon
		send_noteon(firstchan + Channel::VELOCITYTRIG, velocityval, note);
	  } else {
		// noteoff
		send_noteoff(firstchan + Channel::VELOCITYTRIG, note);
	  }

	  oldTrig = newTrig;
	}
#endif
  }

  ClipMode clipmode;
  uint32_t count{0}, old_count{0}, val{0};
  uint8_t pinA, pinB, ccnum, chan;
  GPIOEncoder enc;
  Velocity velocity;

  bool oldTrig{false};
};
} // namespace mico
