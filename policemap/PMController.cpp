#include "PMController.h"

PMController::PMController(int number_of_buttons, Leds *leds, LiquidCrystal *lcd, int speaker_pin) {
	_buttons = number_of_buttons;
	// init tihe buttons to 0
	for (int a = 0; a < _buttons; a++)
		_buttonStates[a] = 0;
	
	// set the pointers to the lcd and leds
	_leds = leds;
	_lcd = lcd;

	// speaker pin
	_speaker_pin = speaker_pin;

	// set the current state to the mainstate as default
	currentState = new MainState(this);
	
}

void PMController::doLoop() {
	currentState->doUpdate();
}

void PMController::setButton(int button_id, int state) {
	// check length
	if (button_id < _buttons) {
		_buttonStates[button_id] = state;
	}
}