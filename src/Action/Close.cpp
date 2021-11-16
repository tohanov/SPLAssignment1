#include "Action.h"

// TODO: complete implementation


Close::Close (int id) : trainerId(id) {

}


void Close::act(Studio& studio) {
	// TODO
}


std::string Close::toString() const {
	//TODO
	return "***PLACEHOLDER***";
}


BaseAction* Close::duplicate() {

	Close *ptr_newCloseAction = new Close(this->trainerId);

	BaseAction::matchFlags(this, ptr_newCloseAction);

	return ptr_newCloseAction;
}