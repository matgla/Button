/*
	Button - a small library for Arduino to handle button debouncing

	MIT licensed.
*/

#include "Button.h"
#include <Arduino.h>

Button::Button(uint8_t pin, uint8_t debounce_ms)
	: _state(HIGH), _has_changed(false), _pin(pin), _delay_init(debounce_ms), _delay(_delay_init)
{
}

void Button::begin()
{
	pinMode(_pin, INPUT_PULLUP);
}

//
// public methods
//

bool Button::read()
{
	// ignore pin changes until after this delay time
	if (_delay != 0)
	{
		--_delay;
		// ignore any changes during this period
	}

	// pin has changed
	else if (digitalRead(_pin) != _state)
	{
		_delay = _delay_init;
		_state = !_state;
		_has_changed = true;
	}

	return _state;
}

// has the button been toggled from on -> off, or vice versa
bool Button::toggled()
{
	read();
	return has_changed();
}

// mostly internal, tells you if a button has changed after calling the read() function
bool Button::has_changed()
{
	if (_has_changed)
	{
		_has_changed = false;
		return true;
	}
	return false;
}

// has the button gone from off -> on
bool Button::pressed()
{
	return (read() == PRESSED && has_changed());
}

// has the button gone from on -> off
bool Button::released()
{
	return (read() == RELEASED && has_changed());
}
