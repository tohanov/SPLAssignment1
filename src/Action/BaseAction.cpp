#include "Action.h"


BaseAction::BaseAction() {
}


BaseAction::~BaseAction() {
}


// get status of in string form
string BaseAction::getStatusStr() const {
	return (getStatus() == ActionStatus::COMPLETED) ? "Completed": ("Error: " + getErrorMsg());
}


void BaseAction::error(std::string ba_errorMsg) {
	status = ActionStatus::ERROR;
	errorMsg = ba_errorMsg;

    cout << "Error: " << errorMsg << endl;
}


void BaseAction::complete() {
	status = ActionStatus::COMPLETED;
}


// status as enum value
ActionStatus BaseAction::getStatus() const {
	return status;
}


std::string BaseAction::getErrorMsg() const {
	return errorMsg;
}


// static public function
// match status and errorMsg between 2 action objects
void BaseAction::matchFlags(const BaseAction *source, BaseAction *destination) {
	destination->status = source->status;

	if (source->status == ActionStatus::ERROR) {
		destination->errorMsg = source->errorMsg;
	}
}