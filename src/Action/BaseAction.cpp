#include "Action.h"


BaseAction::BaseAction() {

}


// BaseAction::BaseAction(const BaseAction &ref_otherBaseAction) :  status(status), erroMsg(ref_otherBaseAction.errorMsg){

// }


BaseAction::~BaseAction() {

}


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


ActionStatus BaseAction::getStatus() const {
	return status;
}


std::string BaseAction::getErrorMsg() const {
	return errorMsg;
}


void BaseAction::matchFlags(const BaseAction *source, BaseAction *destination) { // static
	destination->status = source->status;

	if (source->status == ActionStatus::ERROR) {
		destination->errorMsg = source->errorMsg;
	}
}