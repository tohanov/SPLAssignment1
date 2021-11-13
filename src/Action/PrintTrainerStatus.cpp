#include "Action.h"

// TODO: complete implementation


//class PrintWorkoutOptions : public BaseAction {
//public:
//    PrintWorkoutOptions();
//    void act(Studio &studio);
//    std::string toString() const;
//	// added
//	static BaseAction* actionFromCommand(std::istringstream &commandStream);
//private:
//};


PrintTrainerStatus::PrintTrainerStatus (int id) : trainerId(id) {

}


void PrintTrainerStatus::act(Studio& studio) {
	// TODO
}


std::string PrintTrainerStatus::toString() const {
	//TODO
	return "***PLACEHOLDER***";
}
