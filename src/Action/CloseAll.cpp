#include "Action.h"

// TODO: complete implementation


CloseAll::CloseAll () {

}


void CloseAll::act(Studio& studio) {
	// TODO
}


std::string CloseAll::toString() const {
	//TODO
	return "***PLACEHOLDER***";
}


BaseAction* CloseAll::duplicate() {

	Close *ptr_newCloseAllAction = new CloseAll();

	BaseAction::matchFlags(this, ptr_newCloseAllAction);

	return ptr_newCloseAllAction;
}