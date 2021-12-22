/*
	Button - a small library for Arduino to handle button debouncing

	MIT licensed.
*/

#ifndef Button_h
#define Button_h
#include "Arduino.h"

class Button
{
public:
	Button(uint8_t pin, uint8_t debounce_ms = 100);
	void begin();
	bool read();
	bool toggled();
	bool pressed();
	bool released();
	bool has_changed();

	const static bool PRESSED = LOW;
	const static bool RELEASED = HIGH;

private:
	bool _state : 1;
	bool _has_changed : 1;
	uint8_t _pin;
	uint8_t _delay_init;
	uint8_t _delay;
};

#endif
