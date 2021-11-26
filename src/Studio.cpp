#include <fstream>		// for std::fstream
#include <sstream>      // for std::istringstream
#include <limits>		// for numeric_limits<streamsize>::max()
#include "Studio.h"


extern Studio* backup;
using namespace std;


Studio::Studio() : latestCustomerId(-1) {
}


//Destructor
Studio::~Studio() {
	deleteVectors();
}


// Copy constructor
Studio::Studio (const Studio &ref_otherStudio) {
	copyPropertiesFrom(ref_otherStudio);
 }


// Move constructor
Studio::Studio(const Studio &&ref_otherStudio) {
	movePropertiesFrom(&ref_otherStudio);
}


// Copy Assignment operator
Studio& Studio::operator=(const Studio &ref_otherStudio) {
	// guarding from self assignment
	if (this == &ref_otherStudio) {
		return *this;
	}

	this->deleteVectors();

	copyPropertiesFrom(ref_otherStudio);

	return *this;
}


// Move Assignment operator
Studio& Studio::operator=(const Studio &&ref_otherStudio) {
	this->deleteVectors();

	movePropertiesFrom(&ref_otherStudio);

	return *this;
}


// used in assignment operators
void Studio::deleteVectors() {
	workout_options.clear(); // will call destructors

	for (Trainer *ptr_trainer : this->trainers) {
		delete ptr_trainer;
	}

	for (BaseAction *ptr_action : this->actionsLog) {
		delete ptr_action;
	}

	trainers.clear();
	actionsLog.clear();
}


// used in copy constuctor and copy assignment operator
void Studio::copyPropertiesFrom(const Studio &ref_otherStudio) {
	this->open = ref_otherStudio.open;
	this->latestCustomerId = ref_otherStudio.latestCustomerId;

	// deep copies
	for (Workout workout : ref_otherStudio.workout_options) {
		workout_options.push_back(Workout(workout));
	}

	for (Trainer* ptr_trainer : ref_otherStudio.trainers) {
		trainers.push_back(new Trainer(*ptr_trainer));
	}

	for (BaseAction* ptr_action : ref_otherStudio.actionsLog) {
		BaseAction* ptr_duplicateAction = ptr_action->duplicate();

		BaseAction::matchFlags(ptr_action, ptr_duplicateAction);

		actionsLog.push_back(ptr_duplicateAction);
	}
}


// used in move constuctor and move assignment operator
void Studio::movePropertiesFrom(const Studio *ptr_otherStudio) {
	this->open = ptr_otherStudio->open;
	this->latestCustomerId = ptr_otherStudio->latestCustomerId;

	// shallow copies because moving
	for (Workout workout : ptr_otherStudio->workout_options) {
		this->workout_options.push_back(workout);
	}
	for (Trainer *ptr_trainer : ptr_otherStudio->trainers) {
		this->trainers.push_back(ptr_trainer);
	}
	for (BaseAction *ptr_action : ptr_otherStudio->actionsLog) {
		this->actionsLog.push_back(ptr_action);
	}
}


Studio::Studio(const std::string &configFilePath) : latestCustomerId(-1) {
	fstream configFile;
	
	configFile.open(configFilePath, ios::in);

	// supposedly we can assume the config file exists
	if(configFile.is_open()) {
		Studio::parseConfigFile(configFile);
	}
	else {
		// TODO: remove?
		cout << "[*] ERROR: file wasn't opened." << endl;
	}

	configFile.close(); // close the file object.
}


void Studio::start() {
	istringstream commandStream;
	string command; // for storing current user input

	this->open = true;
	cout << "Studio is now open!" << endl;

	do {
		getline(cin, command);
		
		commandStream.str(command);
		commandStream.clear();	// clearing set flags

		BaseAction* actionPtr = BaseAction::actionFromCommand(commandStream, *this);
		
		if (actionPtr != nullptr) {
			actionPtr->act(*this);
			actionsLog.push_back(actionPtr);
		}

	} 	while(this->open);
}


int Studio::getNumOfTrainers() const {
	return trainers.size();
}


Trainer* Studio::getTrainer(int tid) {
	return trainers[tid];
}


const std::vector<BaseAction*>& Studio::getActionsLog() const { // Return a reference to the history of actions
	return actionsLog;
}


std::vector<Workout>& Studio::getWorkoutOptions() {
	return workout_options;
}


// parse file line by line
void Studio::parseConfigFile(fstream &configFile) {
	istringstream inputStreamFromStr;
	string configLine;
	string readingStr;
	string workoutType;

	const char* typeOfWhitespaces = " \t\n\r\f\v";

	size_t numOfTrainers = 0;
	// for tracking which section of config we're in
	ConfigSection currentConfigSection = ConfigSection::NUM_OF_TRAINERS;

	// read line of data from file stream into a string
	while( getline(configFile, configLine) ) {
		inputStreamFromStr.str(configLine);
		// clearing potentially set flags like EOF
		inputStreamFromStr.clear();

		// ignoring comments in config
		if (configLine[0] == '#') {
			continue;
		}
		else if (configLine.find_first_not_of(typeOfWhitespaces) == string::npos) {
			continue;
		}
		else {
			if (currentConfigSection == ConfigSection::NUM_OF_TRAINERS) {
				inputStreamFromStr >> numOfTrainers;

				currentConfigSection = ConfigSection::TRAINERS_CAPACITIES;
			}
			else if (currentConfigSection == ConfigSection::TRAINERS_CAPACITIES) {
				int capacity;

				for (size_t i = 0; i < numOfTrainers; ++i) {
					inputStreamFromStr >> capacity;
					// ignores everything upto and including the next comma character
					inputStreamFromStr.ignore(numeric_limits<streamsize>::max(), ',');

					trainers.push_back(new Trainer(capacity));
				}
			
				currentConfigSection = ConfigSection::WORKOUT_OPTIONS;
			}
			else { // currentConfigSection == ConfigSection::WORKOUT_OPTIONS
				int cost;
				// reading workout name
				getline(inputStreamFromStr, readingStr, ',');
				trim(readingStr, typeOfWhitespaces);
				// reading workout type
				getline(inputStreamFromStr, workoutType, ',');
				trim(workoutType, typeOfWhitespaces);
				// reading cost of workout
				inputStreamFromStr >> cost;
				
				workout_options.push_back(Workout(workout_options.size(), readingStr, cost, Workout::workoutTypeFromStr(workoutType)));
			}
		}
	}
}


// notifies the studio that it should close and stop receiving user input
void Studio::setClosed() {
	open = false;
}


// trim whitespace from beginning and end of the given string
void trim (string &str, const char* typeOfWhitespaces) {
	str.erase(str.find_last_not_of(typeOfWhitespaces) + 1);
	str.erase(0,str.find_first_not_of(typeOfWhitespaces));
}


// used for customer unique id mechanism
int Studio::getLatestCustomerId() const {
	return latestCustomerId;
}


// used for customer unique id mechanism
void Studio::notifyCustomersAddition(unsigned int increment) {
	latestCustomerId += increment;
}