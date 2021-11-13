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
	std::istringstream commandStream;
	std::cout << "Studio is now open!" << std::endl;
	string command; // for storing current user input

	do {
		cout << "action> ";
		cin >> command;
		
		commandStream.str(command);
		commandStream.clear();	// clearing set flags

		BaseAction* actionPtr;// = BaseAction::actionFromCommand(commandStream);
		//actionPtr->act(*this);

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

	istringstream inputStreamFromStr;
	string configLine;
	string readingStr;
	string workoutType;

	const char* typeOfWhitespaces = " \t\n\r\f\v";
	size_t numOfTrainers = 0;
	ConfigSection currentConfigSection = ConfigSection::numOfTrainers;

	while( std::getline(configFile, configLine) ) { //read data from file object and put it into string.
		cout << "configLine is: " << configLine << endl; // TODO: remove debug line
		inputStreamFromStr.str(configLine);
		inputStreamFromStr.clear(); // clearing potentially set flags like EOF

		if (configLine[0] == '#') { // ignoring comment lines
			continue;
		}
		else if (configLine.find_first_not_of(typeOfWhitespaces) == string::npos) {
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
				std::getline(inputStreamFromStr, readingStr, ',');
				trim(readingStr);
				std::getline(inputStreamFromStr, workoutType, ',');
				trim(workoutType);
				inputStreamFromStr >> cost;


				// TODO: remove debug line
				cout << "at config section 'workoutOptions' got str: '" << readingStr << "' ::: '" << workoutType << "' ::: '" << cost << "'" << endl;
				
				workout_options.push_back(Workout(workout_options.size(), readingStr, cost, workoutTypeFromStr(workoutType)));
			}
		}
	}
}


void trim (string &str) {
	const char* typeOfWhitespaces = " \t\n\r\f\v";
	str.erase(str.find_last_not_of(typeOfWhitespaces) + 1);
	str.erase(0,str.find_first_not_of(typeOfWhitespaces));
}


WorkoutType workoutTypeFromStr (const std::string &workoutTypeStr) { // assuming workoutTypeStr is trimmed

	switch(workoutTypeStr[0]){
		case 'A':
			return WorkoutType::ANAEROBIC;
		case 'M':
			return WorkoutType::MIXED;
		default: // 'C'
			return WorkoutType::CARDIO;
	}
}
