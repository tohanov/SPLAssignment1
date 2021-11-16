#include "Action.h"

//class BaseAction{
//public:
//    BaseAction();
//    ActionStatus getStatus() const;
//    virtual void act(Studio& studio)=0;
//    virtual std::string toString() const=0;
//	// added
//	static BaseAction* actionFromCommand(std::istringstream &commandStream);
//protected:
//    void complete();
//    void error(std::string errorMsg);
//    std::string getErrorMsg() const;
//private:
//    std::string errorMsg;
//    ActionStatus status;
//	// added
//	static std::hash<std::string> hasher;
//	static CommandHashPair hashedCommandPairs[];
//};


BaseAction::BaseAction () {
	// TODO
}


string BaseAction::getStatusStr() const {
	return (getStatus() == ActionStatus::COMPLETED) ? "Completed": ("Error: " + getErrorMsg());
}


void BaseAction::error(std::string ba_errorMsg) {
	status = ActionStatus::ERROR;
	errorMsg = ba_errorMsg;
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


void BaseAction::matchFlags(BaseAction *source, BaseAction *destination) { // static
	destination->status = source->status;
	if (source->status == ActionStatus::ERROR){
		destination->errorMsg = source->errorMsg;
	}
}