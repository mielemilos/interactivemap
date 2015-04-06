#include "Leds.h"

Leds::Leds(unsigned int chips, unsigned int dataPin, unsigned int clockPin, unsigned int latchPin)
{
	// max 10 chips to keep memory usage down
	if (chips > 10) 
		chips = 10;
		
	// set the vars
	_chips = chips;
	_dataPin = dataPin;
	_clockPin = clockPin;
	_latchPin = latchPin;
	
	// init other variables
	_usedpinleds = 0;

	// init array
	for (int a = 0; a < 10; a++)
		_currentState[a] = 0x000000;
}

void Leds::init() {
	// init the pin modes
	pinMode(_latchPin, OUTPUT);
	// these where inside the function _shiftOut, but why?
	pinMode(_clockPin, OUTPUT);
	pinMode(_dataPin, OUTPUT);
	// set the init flag
	__init = true;
	// set all to off
	allOff();
}

byte Leds::addPinLed(byte pin) {
	int number = (_chips * 8) + (_usedpinleds + 1);
	if (number > (_chips * 9)) { // max 8 pinleds
		return 0;
	}
	// set the pinmode to output
	pinMode(13, OUTPUT);
	// register
	_pinleds[_usedpinleds] = pin;
	// increment pinleds used
	_usedpinleds++;
	// return current number of pinleds
	return _usedpinleds;
}

void Leds::setLed(unsigned int led, bool on) {
	_setLed(led, on);
	_writeCurrent();
}

void Leds::setLeds(unsigned int* leds, bool on) {
	int n = (sizeof(leds) / sizeof(leds[0]));

	for (unsigned int a = 0; a < n; a++)
		_setLed(leds[a], on);
	
	_writeCurrent();
}

void Leds::allOn() {
	for (int a = 0; a <= _chips; a++)
		_currentState[a] = 255;
	_writeCurrent();
}

void Leds::allOff() {
	for (int a = 0; a <= _chips; a++)
		_currentState[a] = 0;
	_writeCurrent();
}

void Leds::startWalk() {
	_walkStep = 0;
}

void Leds::stepWalk() {
	if (_walkStep < 0) 
		return;
			
	// clear all but wait for writing
	for (int a = 0; a < _chips; a++)
		_currentState[a] = 0;
	
	setLed(_walkStep, true);
	
	_walkStep++;
	
	if(_walkStep >= (_chips*8))
		_walkStep = -1;
}


void Leds::stopWalk() {
	_walkStep = -1;
}

void Leds::_setLed(unsigned int led, bool on) {
	// first get the chips to use,
	// it works backwards (last chip is first)
	int chip = (_chips - int(led / 8)) - 1;
	if (chip < 0) {
		// it a "pin-led", move to last
		chip = _chips;
	}

	// get the byte value of the led by shifting
	// it to the correct position using remainder 
	// which is the pin on the chip
	int bitled = 1 << (led % 8);
	int c = _currentState[chip];
	// get the current of/off value
	if (on != ((c & bitled) == bitled)) {
		if (on)
			 _currentState[chip] = c + bitled;
		else
			_currentState[chip] = c - bitled;
	}

	// write out
	_writeCurrent();
}

bool Leds::getLed(unsigned int led) {
	// get the byte value of the led by shifting
	// it to the correct position using remainder 
	// which is the pin on the chip
	int bitled = 1 << (led % 8);
	// get the current of/off value from the chips to use,
	// it works backwards (last chip is first)
	return bool((_currentState[_chips - int(led / 8)] & bitled) == bitled);
}

byte* Leds::getCurrentState() {
	return _currentState;
}

void Leds::_writeCurrent() {
	/* set "extra" leds */
	// todo: check if this correct
	byte extraState = _currentState[_chips];
	for(int a = 1; a <= _usedpinleds; a++) {
		bool status = ((extraState & a) == a);
		digitalWrite(_pinleds[a-1], status);		
	}

	// init write
	digitalWrite(_latchPin, 0);
    //move 'em out
    for (int a = 0; a < _chips; a++) {
		_shiftOut(_currentState[a]);
	}
	// exit write
	digitalWrite(_latchPin, 1);
	// small delay, needed?
	//delay(10);

}
	
/*
  function _shiftOut
  Sets the "current_chip" to the values represented by the byte
  
  @param: byte 
*/
void Leds::_shiftOut(byte dataOut) {
  // This shifts 8 bits out MSB first, 
  //  on the rising edge of the clock,
  //  clock idles low

  int i=0;
  int pinState;
 
  // Clear everything out just in case to
  // Prepare shift register for bit shifting
  digitalWrite(_dataPin, 0);
  digitalWrite(_clockPin, 0);

  // For each bit in the byte myDataOut:
  // NOTICE THAT WE ARE COUNTING DOWN in our for loop
  // This means that %00000001 or "1" will go through such
  // that it will be pin Q0 that lights. 
  for (i=7; i>=0; i--)  {
    digitalWrite(_clockPin, 0);

    //if the value passed to myDataOut and a bitmask result 
    // true then... so if we are at i=6 and our value is
    // %11010100 it would the code compares it to %01000000 
    // and proceeds to set pinState to 1.
    if ( dataOut & (1<<i) ) {
      pinState= 1;
    }
    else {	
      pinState= 0;
    }
    // Sets the pin to HIGH or LOW depending on pinState
    digitalWrite(_dataPin, pinState);
    // Register shifts bits on upstroke of clock pin  
    digitalWrite(_clockPin, 1);
    // Zero the data pin after shift to prevent bleed through
    digitalWrite(_dataPin, 0);
  }

  //stop shifting
  digitalWrite(_clockPin, 0);
}
