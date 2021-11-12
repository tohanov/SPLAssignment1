#include <sstream>      // for std::istringstream
//#include <functional>
#include <string>
#include <unordered_map>
#include "Action.h"

//enum ActionStatus{
//    COMPLETED, ERROR
//};
//
////Forward declaration
//class Studio;
//
//class BaseAction{
//public:
//    BaseAction();
//    ActionStatus getStatus() const;
//    virtual void act(Studio& studio)=0;
//    virtual std::string toString() const=0;
//protected:
//    void complete();
//    void error(std::string errorMsg);
//    std::string getErrorMsg() const;
//private:
//    std::string errorMsg;
//    ActionStatus status;
//};

using namespace std;

// TODO: merge all of this functionality with constructors for different Actions
BaseAction* actionFromCommand(const std::string &command, std::vector<CommandHashPair> (&commandHashPairs)) {
	std::istringstream commandStream(command);
	std::string readingStr;
	
	std::hash<std::string> hasher;

	commandStream >> readingStr;
	size_t commandTypeHash = hasher(readingStr);

	for (CommandHashPair i : commandHashPairs) {
		if (commandTypeHash == i.commandTypeHash) {
 			return (*i.matchingFunction)(commandStream);
		}
	}
}


//open order move close closeall workout_options status log backup restore

BaseAction* openActionFromCommand(std::istringstream &commandStream) {
	int trainerId;
	int customerTempId = 0;
	string customerName;
	string customerStrategy;
	vector<Customer*> customers;
	Customer* customer;
	commandStream >> trainerId;

	while (getline(commandStream, customerName, ',')) {
		if (customerStrategy == "swt") {
			customer = new SweatyCustomer(customerName, customerTempId);
		} else if (customerStrategy == "chp") {
			customer = new CheapCustomer(customerName, customerTempId);
		} else if (customerStrategy == "mcl") {
			customer = new HeavyMuscleCustomer(customerName, customerTempId);
		} else { // "fbd" due to correctness of input
			customer = new FullBodyCustomer(customerName, customerTempId);
		}
		customers.push_back(customer);
		++customerTempId;
	}

	return new OpenTrainer(trainerId, customers);
}

BaseAction* orderActionFromCommand(std::istringstream &commandStream) {
	int trainerId;
	commandStream >> trainerId;

	return new Order(trainerId);
}


BaseAction* moveActionFromCommand(std::istringstream &commandStream) {
	int src, dst, customerId;

	commandStream >> src;
	commandStream >> dst;
	commandStream >> customerId;
	
	return new MoveCustomer(src, dst, customerId);
}

BaseAction* closeActionFromCommand(std::istringstream &commandStream) {
	int trainerId;
	commandStream >> trainerId;
	
	return new Close(trainerId);
}


BaseAction* closeallActionFromCommand(std::istringstream &commandStream) {
	return new CloseAll();
}


BaseAction* workout_optionsActionFromCommand(std::istringstream &commandStream) {
	return new PrintWorkoutOptions();
}


BaseAction* statusActionFromCommand(std::istringstream &commandStream) {
	int trainerId;
	commandStream >> trainerId;

	return new PrintTrainerStatus(trainerId);
}


BaseAction* logActionFromCommand(std::istringstream &commandStream) {
	return new PrintActionsLog();
}


BaseAction* backupActionFromCommand(std::istringstream &commandStream) {
	return new BackupStudio();
}


BaseAction* restoreActionFromCommand(std::istringstream &commandStream) {
	return new RestoreStudio();
}









