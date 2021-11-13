#include "Action.h"

// TODO: complete implementation

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


ActionStatus BaseAction::getStatus() const {
	return status;
}


std::string BaseAction::getErrorMsg() const {
	return errorMsg;
}
