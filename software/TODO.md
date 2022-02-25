- MICOencoder:
	- Clean up constructor
	- func: rewrite Check for transition
	- ENC_DEBOUNCE_TIME needs to be defined
	- needs to be defined ENC_LOOP_CYCLES
	- Figure out "received" - how to get this without pio?
		- received is statea, stateb and time received
	
	
- Make usb midi stuff
	- Make 14 bit midi function
	- Add build flag to make output clamped or bipolar
