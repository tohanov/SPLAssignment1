#include "Action.h"


// const std::string 				OpenTrainer::strategies[] = {"swt", "chp", "mcl", "fbd"};// static class property
// const string 					BaseAction::statusStrs[] = {"Completed", "Error: "}; // static class property

const hash<string> 		BaseAction::hasher; 					// static class property
const CommandHashPair 	BaseAction::hashedCommandPairs[10] = { 	// static class property
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


BaseAction* BaseAction::actionFromCommand(std::istringstream &commandStream, Studio &ref_studio) { // static 

	string readingStr;
	commandStream >> readingStr; // the first word is the command

	size_t commandTypeHash = hasher(readingStr);

	for (CommandHashPair i : hashedCommandPairs) {
		if (commandTypeHash == i.commandTypeHash) {
 			return (*i.matchingFunction)(commandStream, ref_studio);
		}
	}

	// cout << "[*] reached unreachable code" << endl; // TODO: remove debug line
	return nullptr; // Unreachable code, if the input is valid (which is assumed). This was put here to avoid a warning from the compiler
}


BaseAction* OpenTrainer::actionFromCommand(std::istringstream &commandStream, Studio &ref_studio) { // static
	int trainerId;
	commandStream >> trainerId >> std::ws;

	if ( ! Trainer::isValidTrainerId(trainerId)) {
		return nullptr;
	}

	string customerName;
	string customerStrategy;
	Customer* customer;

	// TODO: maybe should be on stack
	vector<Customer*> customers; // = new vector<Customer*>;

	while ( getline(commandStream, customerName, ',') ) {
		commandStream >> customerStrategy >> std::ws;
		int customerId = ref_studio.getNextCustomerId();

		if (customerStrategy == "swt") {
			customer = new SweatyCustomer(customerName, customerId);
		} else if (customerStrategy == "chp") {
			customer = new CheapCustomer(customerName, customerId);
		} else if (customerStrategy == "mcl") {
			customer = new HeavyMuscleCustomer(customerName, customerId);
		} else { // "fbd" due to correctness of input
			customer = new FullBodyCustomer(customerName, customerId);
		}

		(/* * */customers).push_back(customer);
	}

	// TODO: ask someone about passing customers as a reference like this. causes a memory leak if created on heap
	return (customers.size() == 0) ? nullptr : new OpenTrainer(trainerId, /* * */customers);
}


BaseAction* Order::actionFromCommand(std::istringstream &commandStream, Studio &ref_studio) { // static
	int trainerId;
	commandStream >> trainerId;

	return new Order(trainerId);
}


BaseAction* MoveCustomer::actionFromCommand(std::istringstream &commandStream, Studio &ref_studio) { // static
	int src, dst, customerId;

	commandStream >> src;
	commandStream >> dst;
	commandStream >> customerId;
	
	return new MoveCustomer(src, dst, customerId);
}


BaseAction* Close::actionFromCommand(std::istringstream &commandStream, Studio &ref_studio) { // static
	int trainerId;
	commandStream >> trainerId;
	
	return new Close(trainerId);
}


BaseAction* CloseAll::actionFromCommand(std::istringstream &commandStream, Studio &ref_studio) { // static
	return new CloseAll();
}


BaseAction* PrintWorkoutOptions::actionFromCommand(std::istringstream &commandStream, Studio &ref_studio) { // static
	return new PrintWorkoutOptions();
}


BaseAction* PrintTrainerStatus::actionFromCommand(std::istringstream &commandStream, Studio &ref_studio) { // static
	int trainerId;
	commandStream >> trainerId;

	return (Trainer::isValidTrainerId(trainerId) && ref_studio.getTrainer(trainerId)->getOpenedBefore()) ? new PrintTrainerStatus(trainerId) : nullptr;
}


BaseAction* PrintActionsLog::actionFromCommand(std::istringstream &commandStream, Studio &ref_studio) { // static
	return new PrintActionsLog();
}


BaseAction* BackupStudio::actionFromCommand(std::istringstream &commandStream, Studio &ref_studio) { // static
	return new BackupStudio();
}


BaseAction* RestoreStudio::actionFromCommand(std::istringstream &commandStream, Studio &ref_studio) { // static
	return new RestoreStudio();
}





