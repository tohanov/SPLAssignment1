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
	// TODO
	const string COMMA = ", ";
	const std::vector<Workout>& refWorkoutOptions = studio.getWorkoutOptions();

	for (Workout wo : refWorkoutOptions) {
		cout << wo.getName() << COMMA << Workout::strFromWorkoutType(wo.getType()) << COMMA << wo.getPrice() << endl;
	}
}


std::string PrintWorkoutOptions::toString() const {
	//TODO
	return "***PLACEHOLDER***";
}
