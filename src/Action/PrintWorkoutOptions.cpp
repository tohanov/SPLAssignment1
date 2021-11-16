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


//class PrintWorkoutOptions : public BaseAction {
//public:
//    PrintWorkoutOptions();
//    void act(Studio &studio);
//    std::string toString() const;
//	// added
//	static BaseAction* actionFromCommand(std::istringstream &commandStream);
//private:
//};


PrintWorkoutOptions::PrintWorkoutOptions () {

}


void PrintWorkoutOptions::act(Studio& studio) {
	// never results in an error
	const string COMMA = ", ";
	
	// TODO: see if there are assignments of references to objects, and fix (should be reference to reference)
	const std::vector<Workout>& refWorkoutOptions = studio.getWorkoutOptions();

	for (Workout wo : refWorkoutOptions) {
		cout << wo.getName() << COMMA << Workout::strFromWorkoutType(wo.getType()) << COMMA << wo.getPrice() << endl;
	}

	complete();
}


std::string PrintWorkoutOptions::toString() const {
	return "workout_options Completed";// + getStatusStr();
}


BaseAction* PrintWorkoutOptions::duplicate() {

	PrintWorkoutOptions *ptr_printWorkoutAction = new PrintWorkoutOptions();

	BaseAction::matchFlags(this, ptr_printWorkoutAction);

	return ptr_printWorkoutAction;
}