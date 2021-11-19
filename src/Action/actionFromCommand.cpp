#include "Action.h"


// const std::string 				OpenTrainer::strategies[] = {"swt", "chp", "mcl", "fbd"};// static class property
// const string 					BaseAction::statusStrs[] = {"Completed", "Error: "}; // static class property
const hash<string> 		BaseAction::hasher;// static class property
const CommandHashPair 	BaseAction::hashedCommandPairs[10] = { // static class property
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

	string readingStr;
	commandStream >> readingStr; // first word in the command

	size_t commandTypeHash = hasher(readingStr);

	for (CommandHashPair i : hashedCommandPairs) {
		if (commandTypeHash == i.commandTypeHash) {
 			return (*i.matchingFunction)(commandStream);
		}
	}

	cout << "[*] reached unreachable code" << endl; // TODO: remove debug line
	return nullptr; // Unreachable code, if the input is valid (which is assumed). This was put here to avoid a warning from the compiler
}


BaseAction* OpenTrainer::actionFromCommand(std::istringstream &commandStream) { // static
	int trainerId;
	// char dummyChar;

	string customerName;
	string customerStrategy;
	Customer* customer;

	// TODO: maybe should be on stack
	vector<Customer*> customers; // = new vector<Customer*>;

	commandStream >> trainerId >> std::ws;
	// commandStream >> dummyChar;

	for (int customerTempId = 0; getline(commandStream, customerName, ','); ++customerTempId) { // static
		commandStream >> customerStrategy >> std::ws;
		
		if (customerStrategy == "swt") {
			customer = new SweatyCustomer(customerName, customerTempId);
		} else if (customerStrategy == "chp") {
			customer = new CheapCustomer(customerName, customerTempId);
		} else if (customerStrategy == "mcl") {
			customer = new HeavyMuscleCustomer(customerName, customerTempId);
		} else { // "fbd" due to correctness of input
			customer = new FullBodyCustomer(customerName, customerTempId);
		}

		(/* * */customers).push_back(customer);
		// commandStream >> dummyChar;
	}

	// ask someone about passing customers as a reference like this. causes a memory leak if created on heap
	return new OpenTrainer(trainerId, /* * */customers);
}


BaseAction* Order::actionFromCommand(std::istringstream &commandStream) { // static
	int trainerId;
	commandStream >> trainerId;

	return new Order(trainerId);
}


BaseAction* MoveCustomer::actionFromCommand(std::istringstream &commandStream) { // static
	int src, dst, customerId;

	commandStream >> src;
	commandStream >> dst;
	commandStream >> customerId;
	
	return new MoveCustomer(src, dst, customerId);
}


BaseAction* Close::actionFromCommand(std::istringstream &commandStream) { // static
	int trainerId;
	commandStream >> trainerId;
	
	return new Close(trainerId);
}


BaseAction* CloseAll::actionFromCommand(std::istringstream &commandStream) { // static
	return new CloseAll();
}


BaseAction* PrintWorkoutOptions::actionFromCommand(std::istringstream &commandStream) { // static
	return new PrintWorkoutOptions();
}


BaseAction* PrintTrainerStatus::actionFromCommand(std::istringstream &commandStream) { // static
	int trainerId;
	commandStream >> trainerId;

	// cout << "[*] inside PrintTrainerStatus::actionFromCommand()" << endl; // TODO: remove debug line
	// cout << "[*] stream.srt() is: " << commandStream.str() << endl;
	// cout << "[*] got trainerId: " << trainerId << endl; // TODO: remove debug line

	return new PrintTrainerStatus(trainerId);
}


BaseAction* PrintActionsLog::actionFromCommand(std::istringstream &commandStream) { // static
	return new PrintActionsLog();
}


BaseAction* BackupStudio::actionFromCommand(std::istringstream &commandStream) { // static
	return new BackupStudio();
}


BaseAction* RestoreStudio::actionFromCommand(std::istringstream &commandStream) { // static
	return new RestoreStudio();
}





