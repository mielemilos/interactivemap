/*
  MainState.h - Default state for the main machine
  Created by Michiel Bodewes, januari 1, 2014
  Released into the public domain.
*/
#ifndef MainState_h
#define MainState_h

#include "Arduino.h"
#include "State.h"
#include "ParentInterface.h"
#include "Countries.h"

class MainState : public State
{
  public:
  	MainState(ParentInterface *parent);
  	void doUpdate();
	
	
  private:
    unsigned int _a;
  	ParentInterface* _parent;
    char _currentLCDLine1_TEXT[20]; 
    char _currentLCDLine2_TEXT[20];
    long _timeout;
    long _lasttick;
    int _ledCounter;
    Countries* _countries;
};
#endif