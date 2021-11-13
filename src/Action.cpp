#include <sstream>      // for std::istringstream
//#include <functional>
#include <string>
#include <unordered_map>
#include "Action.h"

using namespace std;
std::string OpenTrainer::strategies[] = {"swt", "chp", "mcl", "fbd"};// static class property
std::hash<std::string> BaseAction::hasher;// static class property
CommandHashPair BaseAction::hashedCommandPairs[] = { // static class property
	{hasher("open"), 	OpenTrainer::actionFromCommand},
	{hasher("order"), 	Order::actionFromCommand},
	{hasher("move"), 	MoveCustomer::actionFromCommand},
	{hasher("close"), 	Close::actionFromCommand},
	{hasher("closeall"), CloseAll::actionFromCommand},
	{hasher("workout_options"), PrintWorkoutOptions::actionFromCommand},
	{hasher("status"), 	PrintTrainerStatus::actionFromCommand},
	{hasher("log"), 	PrintActionsLog::actionFromCommand},
	{hasher("backup"), 	BackupStudio::actionFromCommand},
	{hasher("restore"), RestoreStudio::actionFromCommand}
};

BaseAction* BaseAction::actionFromCommand(std::istringstream &commandStream) { // static 

	std::string readingStr;
	size_t commandTypeHash = hasher(readingStr);

	commandStream >> readingStr; // first word in the command

	for (CommandHashPair i : hashedCommandPairs) {
		if (commandTypeHash == i.commandTypeHash) {
 			return (*i.matchingFunction)(commandStream);
		}
	}
}


//open order move close closeall workout_options status log backup restore

BaseAction* OpenTrainer::actionFromCommand(std::istringstream &commandStream) {
	int trainerId;

	string customerName;
	string customerStrategy;
	Customer* customer;

	// TODO: maybe should be on stack
	vector<Customer*> *customers = new vector<Customer*>;

	commandStream >> trainerId;

	for (int customerTempId = 0; getline(commandStream, customerName, ','); ++customerTempId) {
		commandStream >> customerStrategy;
		
		if (customerStrategy == strategies[0]) {
			customer = new SweatyCustomer(customerName, customerTempId);
		} else if (customerStrategy == strategies[1]) {
			customer = new CheapCustomer(customerName, customerTempId);
		} else if (customerStrategy == strategies[2]) {
			customer = new HeavyMuscleCustomer(customerName, customerTempId);
		} else { // "fbd" due to correctness of input
			customer = new FullBodyCustomer(customerName, customerTempId);
		}
		(*customers).push_back(customer);
	}

	return new OpenTrainer(trainerId, *customers);
}

BaseAction* Order::actionFromCommand(std::istringstream &commandStream) {
	int trainerId;
	commandStream >> trainerId;

	return new Order(trainerId);
}


BaseAction* MoveCustomer::actionFromCommand(std::istringstream &commandStream) {
	int src, dst, customerId;

	commandStream >> src;
	commandStream >> dst;
	commandStream >> customerId;
	
	return new MoveCustomer(src, dst, customerId);
}

BaseAction* Close::actionFromCommand(std::istringstream &commandStream) {
	int trainerId;
	commandStream >> trainerId;
	
	return new Close(trainerId);
}


BaseAction* CloseAll::actionFromCommand(std::istringstream &commandStream) {
	return new CloseAll();
}


BaseAction* PrintWorkoutOptions::actionFromCommand(std::istringstream &commandStream) {
	return new PrintWorkoutOptions();
}


BaseAction* PrintTrainerStatus::actionFromCommand(std::istringstream &commandStream) {
	int trainerId;
	commandStream >> trainerId;

	return new PrintTrainerStatus(trainerId);
}


BaseAction* PrintActionsLog::actionFromCommand(std::istringstream &commandStream) {
	return new PrintActionsLog();
}


BaseAction* BackupStudio::actionFromCommand(std::istringstream &commandStream) {
	return new BackupStudio();
}


BaseAction* RestoreStudio::actionFromCommand(std::istringstream &commandStream) {
	return new RestoreStudio();
}





