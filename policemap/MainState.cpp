#include "MainState.h"
//ParentInterface& parent
MainState::MainState(ParentInterface *parent) : State(parent){
	_timeout = 1000;
	_lasttick = 0;
	_ledCounter = 0;
}

void MainState::doUpdate() {

	if (getParent()->getButton(0) == 1) {
		getParent()->getLeds()->allOn();

	} else if (getParent()->getButton(1) == 1) {
		getParent()->getLeds()->allOff();
		_ledCounter--;
		if(_ledCounter < 0)
			_ledCounter = 40;
		getParent()->getLeds()->setLed(_ledCounter, 1);

		getParent()->getLCD()->clear();
		getParent()->getLCD()->setCursor(0,0);
		getParent()->getLCD()->print(getParent()->getCountries()->getCityById(_ledCounter));
		getParent()->getLCD()->setCursor(0,1);
		getParent()->getLCD()->print(_ledCounter);

	} else if (getParent()->getButton(2) == 1) {
		getParent()->getLeds()->allOff();	
		_ledCounter++;
		if (_ledCounter > 40)
			_ledCounter = 0;
		getParent()->getLeds()->setLed(_ledCounter, 1);

		getParent()->getLCD()->clear();
		getParent()->getLCD()->setCursor(0,0);
		getParent()->getLCD()->print(getParent()->getCountries()->getCityById(_ledCounter));
		getParent()->getLCD()->setCursor(0,1);
		getParent()->getLCD()->print(_ledCounter);
	
	} else if (getParent()->getButton(3) == 1) {
		getParent()->getLCD()->setCursor(0,0);
		getParent()->getLCD()->print("Politiekaart van");
		getParent()->getLCD()->setCursor(0,1);

		getParent()->getLCD()->print("Teije en Wester");
	}

	long current = millis();
	if (!( (current - _lasttick) > _timeout) ) {
		return;
	}
	_lasttick = current;

	/*getParent()->getLCD()->clear();
	getParent()->getLCD()->setCursor(0,0);
	getParent()->getLCD()->print(getParent()->getButton(0));
	getParent()->getLCD()->setCursor(5,0);
	getParent()->getLCD()->print(getParent()->getButton(1));
	getParent()->getLCD()->setCursor(0,1);
	getParent()->getLCD()->print(getParent()->getButton(2));
	getParent()->getLCD()->setCursor(5,1);
	getParent()->getLCD()->print(getParent()->getButton(3));
	*/
	return;
}
