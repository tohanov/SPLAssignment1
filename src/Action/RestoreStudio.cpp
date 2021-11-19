#include "Action.h"

// TODO: complete implementation


RestoreStudio::RestoreStudio() {

}


void RestoreStudio::act(Studio& studio) {
	// TODO
	if (backup == nullptr) {
		error("No backup available");
		return;
	}

	// delete &studio;
	studio = *backup; // should copy (not move)

	complete();
}


std::string RestoreStudio::toString() const {
	return "restore " + getStatusStr();
}


BaseAction* RestoreStudio::duplicate() {
	RestoreStudio *ptr_restoreAction = new RestoreStudio();

	BaseAction::matchFlags(this, ptr_restoreAction);

	return ptr_restoreAction;
}