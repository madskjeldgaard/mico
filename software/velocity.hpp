/*
*
* TODO:
* - This whole business is probably overcomplicated somewhat. Clean it up and simplify it!
*
*/
#pragma once
#ifndef VEL
#define VEL

namespace mico{

enum Speed {
  SLOWEST=100000,
  SLOW=50000,
  MEDIUM=30000,
  FAST=20000,
  SUPERFAST=10000,
  FASTEST=5000,
};

// std::array<int, Speed::NUM_SPEEDS> deltaValues = {
//   1000,
//   500,
//   250,
//   50,
//   10,
//   5,
//   1,
// };

class Velocity {
public:
  // This is used outside of the class to figure out what level of velocity we are at.
  int speed_level{1};
  static const int num_speed_levels{7};

  void init(){
	t2 = time_us_32();
	update();
  }

  // Update clocks and return the delta value (velocity applied to 14 bit midi value range)
  uint32_t next14(){
	auto deltaval = update();
	return get_delta_value14(deltaval);
  }
private:
  uint32_t t2{1}, t1{1};
  // Generate a value suitable for increasing/decreasing a 14 bit value based on a time delta between two different times of polling that value. Expects microseconds. Use `time_us_32()`
  uint32_t update(){
	t1 = time_us_32();
	const auto time_delta = t1 - t2;
	t2 = t1;
	printf("time delta: %d\n", time_delta);
	return time_delta;
  }

  uint32_t get_delta_value14(uint32_t time_delta) {
	constexpr auto ultrafast = 5000;
	constexpr auto superfast = 10000;
	constexpr auto fast = 20000;
	constexpr auto mediumfast = 30000;
	constexpr auto medium = 50000;
	constexpr auto lowspeed = 100000;

	if (time_delta < superfast && time_delta > 0) {
	  speed_level = 7;
	  return 1000;
	} else if (time_delta > ultrafast && time_delta < superfast) {
	  speed_level = 6;
	  return 500;
	} else if (time_delta > superfast && time_delta < fast) {
	  speed_level = 5;
	  return 250;
	} else if (time_delta > fast && time_delta < mediumfast) {
	  speed_level = 4;
	  return 50;
	} else if (time_delta > mediumfast && time_delta < medium) {
	  speed_level = 3;
	  return 10;
	} else if (time_delta > medium && time_delta < lowspeed) {
	  speed_level = 2;
	  return 5;
	} else {
	  speed_level = 1;
	  return 1;
	}
  }
};

}

#endif
