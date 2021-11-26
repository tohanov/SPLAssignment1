#include "Action.h"


// .cpp file of static functions and class properties, made for parsing user input

// static
const hash<string> 		BaseAction::hasher;
// static
const CommandHashPair 	BaseAction::hashedCommandPairs[10] = {
	{ hasher("order"), 		Order::actionFromCommand },
	{ hasher("move"), 		MoveCustomer::actionFromCommand },
	{ hasher("close"), 		Close::actionFromCommand },
	{ hasher("open"), 		OpenTrainer::actionFromCommand },
	{ hasher("closeall"), 	CloseAll::actionFromCommand },
	{ hasher("workout_options"), PrintWorkoutOptions::actionFromCommand },
	{ hasher("status"), 	PrintTrainerStatus::actionFromCommand },
	{ hasher("log"), 		PrintActionsLog::actionFromCommand },
	{ hasher("backup"), 	BackupStudio::actionFromCommand },
	{ hasher("restore"), 	RestoreStudio::actionFromCommand }
};


// static
BaseAction* BaseAction::actionFromCommand(std::istringstream &commandStream, Studio &ref_studio) {
	string readingStr;
	commandStream >> readingStr; // the first word is the command

	size_t commandTypeHash = hasher(readingStr);

	for (CommandHashPair i : hashedCommandPairs) {
		if (commandTypeHash == i.commandTypeHash) {
 			return (*i.matchingFunction)(commandStream, ref_studio);
		}
	}
	
	return nullptr;
}


// static
BaseAction* OpenTrainer::actionFromCommand(std::istringstream &commandStream, Studio &ref_studio) {
	int trainerId;
	commandStream >> trainerId >> std::ws;
	
	vector<Customer*> customers;

	string customerName;
	string customerStrategy;
	Customer* customer;

	for (int customerId = ref_studio.getLatestCustomerId() + 1; getline(commandStream, customerName, ','); ++customerId ) {
		commandStream >> customerStrategy >> std::ws;

		if (customerStrategy == "swt") {
			customer = new SweatyCustomer(customerName, customerId);
		} else if (customerStrategy == "chp") {
			customer = new CheapCustomer(customerName, customerId);
		} else if (customerStrategy == "mcl") {
			customer = new HeavyMuscleCustomer(customerName, customerId);
		} else { // "fbd" due to correctness of input
			customer = new FullBodyCustomer(customerName, customerId);
		}

		customers.push_back(customer);
	}

	return (customers.size() == 0) ? nullptr : new OpenTrainer(trainerId, customers);
}


// static
BaseAction* Order::actionFromCommand(std::istringstream &commandStream, Studio &ref_studio) { 
	int trainerId;
	commandStream >> trainerId;

	return new Order(trainerId);
}


// static
BaseAction* MoveCustomer::actionFromCommand(std::istringstream &commandStream, Studio &ref_studio) { 
	int src, dst, customerId;

	commandStream >> src;
	commandStream >> dst;
	commandStream >> customerId;
	
	return new MoveCustomer(src, dst, customerId);
}


// static
BaseAction* Close::actionFromCommand(std::istringstream &commandStream, Studio &ref_studio) { 
	int trainerId;
	commandStream >> trainerId;
	
	return new Close(trainerId);
}


// static
BaseAction* CloseAll::actionFromCommand(std::istringstream &commandStream, Studio &ref_studio) { 
	return new CloseAll();
}


// static
BaseAction* PrintWorkoutOptions::actionFromCommand(std::istringstream &commandStream, Studio &ref_studio) { 
	return new PrintWorkoutOptions();
}


// static
BaseAction* PrintTrainerStatus::actionFromCommand(std::istringstream &commandStream, Studio &ref_studio) { 
	int trainerId;
	commandStream >> trainerId;

	return (Trainer::isValidTrainerId(trainerId) &&
		ref_studio.getTrainer(trainerId)->getOpenedBefore()) ?
			new PrintTrainerStatus(trainerId) :
			nullptr;
}


// static
BaseAction* PrintActionsLog::actionFromCommand(std::istringstream &commandStream, Studio &ref_studio) { 
	return new PrintActionsLog();
}


// static
BaseAction* BackupStudio::actionFromCommand(std::istringstream &commandStream, Studio &ref_studio) { 
	return new BackupStudio();
}


// static
BaseAction* RestoreStudio::actionFromCommand(std::istringstream &commandStream, Studio &ref_studio) { 
	return new RestoreStudio();
}