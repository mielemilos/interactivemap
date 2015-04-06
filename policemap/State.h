/*
  State.h - state base class
  Created by Michiel Bodewes, oktober 15, 2013
  Released into the public domain.
*/
#ifndef State_h
#define State_h

#include "Arduino.h"
#include "ParentInterface.h"

class State
{
  public:
    State(ParentInterface *parent);
    ParentInterface* getParent(); 

    // virtual 
    virtual void doUpdate() = 0;

  private:
  	// store as a pointer because we can init it here
  	// it is set by the constructor so null references should not occour
  	ParentInterface* _parent;
};

#endif
