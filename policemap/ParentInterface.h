/* ParentInterface.h */

#ifndef ParentInterface_h
#define ParentInterface_h

#include "Arduino.h"
#include "Leds.h"
#include "Countries.h"
#include <LiquidCrystal.h>

class ParentInterface
{
  public:
  	ParentInterface();
  	Leds* getLeds();
	LiquidCrystal* getLCD();
	Countries* getCountries();

	byte getButton(int button_id);
	byte* getButtons();
	int getNumberOfButtons();
	
	
  protected:
  	Leds* _leds;
  	LiquidCrystal* _lcd;
  	Countries* _countries;
  	byte _buttonStates[];
	int _number_of_buttons;
	int _speaker_pin;
	int _buttons;
 
};
#endif