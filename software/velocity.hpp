#pragma once
#ifndef VEL
#define VEL

namespace mico{
class Velocity {
public:
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
  uint32_t t2{0}, t1{0};
  // Generate a value suitable for increasing/decreasing a 14 bit value based on a time delta between two different times of polling that value. Expects microseconds. Use `time_us_32()`
  uint32_t update(){
	t1 = time_us_32();
	const auto time_delta = t1 - t2;
	t2 = t1;
	printf("time delta: %d\n", time_delta);
	return time_delta;
  }

  uint32_t get_delta_value14(uint32_t time_delta) {
	constexpr auto ultrafast = 2500;
	constexpr auto superfast = 5000;
	constexpr auto fast = 10000;
	constexpr auto mediumfast = 20000;
	constexpr auto medium = 50000;
	constexpr auto lowspeed = 100000;

	if (time_delta < superfast) {
	  return 150;
	} else if (time_delta > ultrafast && time_delta < superfast) {
	  return 100;
	} else if (time_delta > superfast && time_delta < fast) {
	  return 50;
	} else if (time_delta > fast && time_delta < mediumfast) {
	  return 25;
	} else if (time_delta > mediumfast && time_delta < medium) {
	  return 10;
	} else if (time_delta > medium && time_delta < lowspeed) {
	  return 5;
	} else {
	  return 1;
	}
  }
};

}

#endif
