#include "ParentInterface.h"

ParentInterface::ParentInterface() {
	_countries = new Countries();
}

Leds* ParentInterface::getLeds() {
	return _leds;
}

LiquidCrystal* ParentInterface::getLCD() {
	return _lcd;
}

Countries* ParentInterface::getCountries() {
	return _countries;
}

byte ParentInterface::getButton(int button_id) {
	byte state = 0;
	if (button_id < _buttons && button_id >= 0) {
		state = _buttonStates[button_id];
		// mark as "read"
		_buttonStates[button_id] = 0;
	}
	
	return state;
}


int ParentInterface::getNumberOfButtons() {
	return _buttons; 
}

byte* ParentInterface::getButtons() {
	return _buttonStates;
}