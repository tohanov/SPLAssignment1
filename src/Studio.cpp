#include <fstream>		// for std::fstream
#include <sstream>      // for std::istringstream
#include <limits>		// for numeric_limits<streamsize>::max()
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
		cout << "action> "; // TODO: see if need to remove this for automatic checks to pass
		getline(cin, command);
		
		commandStream.str(command);
		commandStream.clear();	// clearing set flags

		// cout << "[*] inside Studio::start()" << endl; // TODO: remove debug line
		// cout << "[*] got command: " << command << endl; // TODO: remove debug line
		// cout << "[*] stream.str() is: " << commandStream.str() << endl; // TODO: remove debug line

		BaseAction* actionPtr = BaseAction::actionFromCommand(commandStream);

//		cout << "after actionFromCommand()" << endl; // TODO: remove debug line
		actionPtr->act(*this);

//		cout << "after act()" << endl; // TODO: remove debug line

		actionsLog.push_back(actionPtr);
	} while(command.compare("closeall") != 0); // TODO: maybe == operator is better
}


int Studio::getNumOfTrainers() const {
	return trainers.size();
}


Trainer* Studio::getTrainer(int tid) {

	// cout << "[*] inside Studio::getTrainer()" << endl; // TODO: remove debug line
	// cout << "[*] trying to get trainer #" << tid << endl; // TODO: remove debug line
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
		cout << "[*] configLine is: " << configLine << endl; // TODO: remove debug line
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
				cout << "[*] at config section 'numOfTrainers' got int: '" << numOfTrainers << "'" << endl;

				currentConfigSection = ConfigSection::trainersCapacities;
			}
			else if (currentConfigSection == ConfigSection::trainersCapacities) {
				int capacity;

				for (int i = 0; i < numOfTrainers; ++i) {
					inputStreamFromStr >> capacity;
					inputStreamFromStr.ignore(numeric_limits<streamsize>::max(), ','); // ignores everything upto and including the next comma character

					// TODO: remove debug line
					cout << "[*] at config section 'trainersCapacities' got capacity: '" << capacity << "'" << endl;
					trainers.push_back(new Trainer(capacity));
				}
			
				currentConfigSection = ConfigSection::workoutOptions;
			}
			else { // currentConfigSection == ConfigSection::workoutOptions
				int cost;
				std::getline(inputStreamFromStr, readingStr, ',');
				trim(readingStr, typeOfWhitespaces);
				std::getline(inputStreamFromStr, workoutType, ',');
				trim(workoutType, typeOfWhitespaces);
				inputStreamFromStr >> cost;


				// TODO: remove debug line
				cout << "[*] at config section 'workoutOptions' got str: '" << readingStr << "' ::: '" << workoutType << "' ::: '" << cost << "'" << endl;
				
				workout_options.push_back(Workout(workout_options.size(), readingStr, cost, Workout::workoutTypeFromStr(workoutType)));
			}
		}
	}
}


void trim (string &str, const char* typeOfWhitespaces) {
	str.erase(str.find_last_not_of(typeOfWhitespaces) + 1); // TODO: see if this kind of indexing might throw an error
	str.erase(0,str.find_first_not_of(typeOfWhitespaces));
}
