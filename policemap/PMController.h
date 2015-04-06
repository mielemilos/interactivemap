/*
  PMController.h - Library for controlling everything ;)
  Created by Michiel Bodewes, december 28, 2013
  Released into the public domain.
*/
#ifndef PMController_h
#define PMController_h

#include "Arduino.h"
#include <LiquidCrystal.h>
#include "Leds.h"
#include "State.h"
#include "MainState.h"
#include "ParentInterface.h"

class PMController : public ParentInterface
{	
  public:
	PMController(int buttons, Leds *leds, LiquidCrystal *lcd, int speaker_pin);
	void doLoop();
	void setButton(int number, int state);

  private:
	State* currentState;
};

#endif
