#include "State.h"

State::State(ParentInterface *parent) {
	//pointer to parent
	_parent = parent;
}

ParentInterface* State::getParent() {
	
	return _parent;
}