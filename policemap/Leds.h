/*
  leds.h - Library for using shiftout leds
  Created by Michiel Bodewes, oktober 8, 2013
  Released into the public domain.
*/
#ifndef Leds_h
#define Leds_h

#include "Arduino.h"

class Leds
{
  public:
  	Leds(unsigned int chips, unsigned int dataPin, unsigned int clockPin, unsigned int latchPin);
    
    byte addPinLed(byte pin);
    void setLed(unsigned int led, bool on);
    void setLeds(unsigned int* leds, bool on);
    void init();
    void allOn();
    void allOff();
  	void startWalk();
  	void stepWalk();
  	void stopWalk();
  	bool getLed(unsigned int led);
  	byte* getCurrentState();
  	
  private:
  	byte _pinleds[16];
  	byte _usedpinleds;
  	bool __init;
  	byte _currentState[10];	
    unsigned int _chips;
    unsigned int _dataPin;
    unsigned int _clockPin;
    unsigned int _latchPin;
    unsigned int _walkStep;
    
  	void _shiftOut(byte dataOut);
  	void _writeCurrent();
  	void _setLed(unsigned int led, bool on);
	
};

#endif
