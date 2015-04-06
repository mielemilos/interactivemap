/* Button.h */

#ifndef Button_h
#define Button_h

#include "Arduino.h"

class Button
{
  public:
	Button(int button_pin);
  	void update();
  	int getState();
  	int getButtonPin();
  	static const int BUTTON_STATE_NONE = 0;
  	//static const int BUTTON_STATE_DOWN = 1;  // started but not yet "hold" (notification)
  	static const int BUTTON_STATE_CLICK = 1;  // clicked
  	static const int BUTTON_STATE_DUBBLE_CLICK = 2; // double click
  	static const int BUTTON_STATE_HOLD = 3; // holded for min _hold_time_ms 
	static const int BUTTON_STATE_HOLD_LONG = 4; // holded for min _long_hold_time_ms

	
  private:
  	int _button_pin;

  	// Button timing variables
	int _debounce_ms;  			// ms debounce period to prevent flickering when pressing or releasing the button
	int _doubleclick_gap_ms;    // max ms between clicks for a double click event
	int _hold_time_ms;       	// ms hold period: how long to wait for press+hold event
	int _long_hold_time_ms;   	// ms long hold period: how long to wait for press+hold event

	// Button variables
	bool _last_button_value; 	// buffered value of the button's previous state
	bool _is_dc_waiting;  	 	// whether we're waiting for a double click (down)
	bool _dc_on_up;     	 	// whether to register a double click on next release, or whether to wait and click
	bool _is_single_ok;    	 	// whether it's OK to do a single click
	bool _ignore_up;   		 	// whether to ignore the button release because the click+hold was triggered
	bool _wait_for_up;       	// when held, whether to wait for the up event
	bool _hold_past_event;   	// whether or not the hold event happened already
	bool _hold_past_event_long;	// whether or not the long hold event happened already

	// button-press-timings
	unsigned long _prefcheck;
	unsigned long _downtime;         	// time the button was pressed down
	unsigned long _uptime;           	// time the button was released

	// last button state updated
	int _last_button_state;
	
 
};
#endif