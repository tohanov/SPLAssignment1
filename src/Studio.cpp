#include <fstream>		// for std::fstream
#include <sstream>      // for std::istringstream
#include <limits>		// for numeric_limits<streamsize>::max()
//#include <cctype>		// for isspace()
#include "Studio.h"

//class Studio{
//public:
//	Studio();
//    Studio(const std::string &configFilePath);
//    void start();
//    int getNumOfTrainers() const;
//    Trainer* getTrainer(int tid);
//	const std::vector<BaseAction*>& getActionsLog() const; // Return a reference to the history of actions
//    std::vector<Workout>& getWorkoutOptions();
//
//private:
//    bool open;
//    std::vector<Trainer*> trainers;
//    std::vector<Workout> workout_options;
//    std::vector<BaseAction*> actionsLog;
//};

using namespace std;

Studio::Studio() {
	std::hash<std::string> hasher;

	hashedCommandPairs = {
		{hasher("open"), openActionFromCommand},
		{hasher("order"), orderActionFromCommand},
		{hasher("close"), moveActionFromCommand},
		{hasher("closeall"), closeActionFromCommand},
		{hasher("workout_options"), closeallActionFromCommand},
		{hasher("status"), workout_optionsActionFromCommand},
		{hasher("log"), logActionFromCommand},
		{hasher("backup"), backupActionFromCommand},
		{hasher("restore"), restoreActionFromCommand}
	};
}

Studio::Studio(const std::string &configFilePath) {

	fstream configFile;
	configFile.open(configFilePath, ios::in);

	if(configFile.is_open()) { //checking whether the file is open
		Studio::parseConfigFile(configFile);
	}
	else {
		// TODO: correct the error message and handling
		cout << "ERROR: file wasn't opened." << endl;
	}

	configFile.close(); //close the file object.
}


void Studio::start() {
	std::cout << "Studio is now open!" << std::endl;
	string command; // for storing current user input

	do {
		cout << "action> ";
		cin >> command;

		BaseAction* actionPtr = actionFromCommand(command, hashedCommandPairs);
		actionPtr->act(*this);

		actionsLog.push_back(actionPtr);
	} while(command.compare("closeall") != 0);
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


void Studio::parseConfigFile(fstream &configFile) {
	// parse file line by line
	// TODO: consider performing the parsing via c++11 built in regex capability instead
	// TODO: account for all kinds of whitespace

	istringstream inputStreamFromStr;
	string configLine;
	string readingStr;
	string workoutType;

	size_t numOfTrainers = 0;
	ConfigSection currentConfigSection = ConfigSection::numOfTrainers;

	while( std::getline(configFile, configLine) ) { //read data from file object and put it into string.
		cout << "configLine is: " << configLine << endl; // TODO: remove debug line
		inputStreamFromStr.str(configLine);
		inputStreamFromStr.clear(); // clearing potentially set flags like EOF

		if (configLine[0] == '#') { // ignoring comment lines
			continue;
		}
		else if (configLine.length() == 0) { // full line of whitespace is going to be read as empty if read using >> operator
			//configLine[0] == '\0' || configLine[0] == '\n' || configLine[0] == '\n' || configLine[0] == '\t') {
			// TODO: maybe need to loop, maybe can get away with using a istringstream and one input instruction
			continue;
		}
		else {
			if (currentConfigSection == ConfigSection::numOfTrainers) {
				inputStreamFromStr >> numOfTrainers;
				
				// TODO: remove debug line
				cout << "at config section 'numOfTrainers' got int: '" << numOfTrainers << "'" << endl;

				currentConfigSection = ConfigSection::trainersCapacities;
			}
			else if (currentConfigSection == ConfigSection::trainersCapacities) {
				int capacity;

				for (int i = 0; i < numOfTrainers; ++i) {
					inputStreamFromStr >> capacity;
					inputStreamFromStr.ignore(numeric_limits<streamsize>::max(), ','); // ignores everything upto and including the next comma character

					// TODO: remove debug line
					cout << "at config section 'trainersCapacities' got capacity: '" << capacity << "'" << endl;
					trainers.push_back(new Trainer(capacity));
				}
			
				currentConfigSection = ConfigSection::workoutOptions;
			}
			else { // currentConfigSection == ConfigSection::workoutOptions
				int cost;
				std::getline(inputStreamFromStr, readingStr, ','); // TODO: trim potential spaces of ends of strings
				std::getline(inputStreamFromStr, workoutType, ',');
				inputStreamFromStr >> cost;


				// TODO: remove debug line
				cout << "at config section 'workoutOptions' got str: '" << readingStr << " ::: " << workoutType << " ::: " << cost << "'" << endl;

				//TODO: add parsed options to 
			}
		}
	}
}


