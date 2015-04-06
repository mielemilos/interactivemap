#include "Button.h"
/**
0 = nothing
1 = normal click
2 = dubble click?
3 = hold
4 = "long" hold

*/
Button::Button(int button_pin) {
    // pin to use
    _button_pin = button_pin;
    
    // init the button state
    _last_button_state = BUTTON_STATE_NONE;

    // timing settings
    _debounce_ms = 25;          // ms debounce period to prevent flickering when pressing or releasing the button
    _doubleclick_gap_ms = 250;  // max ms between clicks for a double click event
    _hold_time_ms = 2000;       // ms hold period: how long to wait for press+hold event
    _long_hold_time_ms = 4000;  // ms long hold period: how long to wait for press+hold event

    // Button variables init
    _last_button_value = LOW;  // buffered value of the button's previous state
    _is_dc_waiting = false;     // whether we're waiting for a double click (down)
    _dc_on_up = false;             // whether to register a double click on next release, or whether to wait and click
    _is_single_ok = true;            // whether it's OK to do a single click
    _downtime = -1;              // time the button was pressed down
    _uptime = -1;                // time the button was released
    _ignore_up = false;           // whether to ignore the button release because the click+hold was triggered
    _wait_for_up = false;          // when held, whether to wait for the up event
    _hold_past_event = false;      // whether or not the hold event happened already
    _hold_past_event_long = false;  // whether or not the long hold event happened already
    
    //timing
    _prefcheck = 0;
}

void Button::update() {

    // get the current timing
    unsigned long milliseconds = millis();

    // presume the last state
    int button_state = BUTTON_STATE_NONE;
    
    // read the current pin value
    int currentButtonValue = digitalRead(_button_pin);

    // Button pressed down
    if (currentButtonValue == HIGH && _last_button_value == LOW && (milliseconds - _uptime) > _debounce_ms) {
        
        _downtime = milliseconds;
        _ignore_up = _hold_past_event_long = _wait_for_up = _hold_past_event = false;
        _is_single_ok = true;
        
        if ((milliseconds-_uptime) < _doubleclick_gap_ms && _dc_on_up == false && _is_dc_waiting == true) {
            _dc_on_up = true;  
        } 
        else {
            _dc_on_up = false;
        }

        _is_dc_waiting = false;
    }
    // Button released check dubble clicks
    else if (currentButtonValue == LOW && _last_button_value == HIGH && (milliseconds - _downtime) > _debounce_ms) {        
        if (!_ignore_up) {
            _uptime = milliseconds;
            if (_dc_on_up == false) {
                _is_dc_waiting = true;
            } else {
                button_state = BUTTON_STATE_DUBBLE_CLICK;

                _dc_on_up = false;
                _is_dc_waiting = false;
                _is_single_ok = false;
            }
        }
    }
    // Test for normal click event: _doubleclick_gap_ms expired
    if ( currentButtonValue == LOW && // button now released
            (milliseconds-_uptime) >= _doubleclick_gap_ms && // not in double-click gap
             _is_dc_waiting == true && _dc_on_up == false && _is_single_ok == true  // all other states ok
             && button_state != BUTTON_STATE_DUBBLE_CLICK) // and not in double-click state?
    {
        button_state = BUTTON_STATE_CLICK;
        _is_dc_waiting = false;
    }
    // Test for hold
    if ( currentButtonValue == HIGH && (milliseconds - _downtime) >= _hold_time_ms) {
        // Trigger "normal" hold
        if (! _hold_past_event)
        {
            button_state = BUTTON_STATE_HOLD;
            _dc_on_up = _is_dc_waiting = false;
            _wait_for_up = _ignore_up = _hold_past_event = true;
        }
        // Trigger "long" hold
        if ((milliseconds - _downtime) >= _long_hold_time_ms)
        {
            if (! _hold_past_event_long)
            {
                button_state = BUTTON_STATE_HOLD_LONG;
                _hold_past_event_long = true;
            }
        }
    } 

    // prefent sending out "NONE" when on "hold"
    if (currentButtonValue == HIGH && // we are still down
                        button_state != BUTTON_STATE_HOLD && button_state != BUTTON_STATE_HOLD_LONG  &&
                        (_last_button_state == BUTTON_STATE_HOLD || _last_button_state == BUTTON_STATE_HOLD_LONG )) {

        button_state = _last_button_state;
    }
    
    _last_button_value = currentButtonValue;
    _last_button_state = button_state;

}

int Button::getState() {
    return _last_button_state;
}

int Button::getButtonPin() {
    return _button_pin;
}