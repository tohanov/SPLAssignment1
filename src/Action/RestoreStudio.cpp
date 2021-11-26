#include "Action.h"


// static
const string RestoreStudio::commonErrorMessage = "No backup available";


RestoreStudio::RestoreStudio() {
}


void RestoreStudio::act(Studio& studio) {
	if (backup == nullptr) {
		error(commonErrorMessage);
		return;
	}

	studio = *backup; // copy assignment

	complete();
}


std::string RestoreStudio::toString() const {
	return "restore " + getStatusStr();
}


BaseAction* RestoreStudio::duplicate() {
	RestoreStudio *ptr_restoreAction = new RestoreStudio();

	return ptr_restoreAction;
}