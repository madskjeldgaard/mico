#pragma once
#include "mico_midi.h"
#include "micoencoder.hpp"
#include "velocity.hpp"

namespace mico {
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

  // Get encoder value, warp it and add velocity before sending it as 14 bit midi
  void update14() {
    count = enc.get_count();
    if (count != old_count) {

      auto deltaval = velocity.next14();
      val += enc.get_direction() * deltaval;
      val = wrap_or_clamp14(val, clipmode);

      printf("enc on pin %d and %d:", pinA, pinB);
      printf("%d\n", val);

      send_cc14(chan, val, ccnum);

      old_count = count;
    };
  }

private:
  ClipMode clipmode;
  uint32_t count{0}, old_count{0}, val{0};
  uint8_t pinA, pinB, ccnum, chan;
  GPIOEncoder enc;
  Velocity velocity;
};
} // namespace mico
