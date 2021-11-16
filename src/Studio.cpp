#include <fstream>		// for std::fstream
#include <sstream>      // for std::istringstream
#include <limits>		// for numeric_limits<streamsize>::max()
#include "Studio.h"


extern Studio* backup;


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
	// TODO: ???
}

Studio::~Studio() {
	// TODO
}


Studio::Studio (const Studio &ref_otherStudio) {
	// never results in an error

	// TODO
	// need copies of 
	// std::vector<Trainer*> trainers;
	// std::vector<Workout> workout_options;
	// std::vector<BaseAction*> actionsLog;

	copyPropertiesFrom(ref_otherStudio);
 }


 
Studio& Studio::operator= (const Studio &ref_otherStudio) {
	// TODO
	// guarding from self assignment
	if (this == &ref_otherStudio) {
		return *this;
	}

	// TODO: for vectors of elements with copy assignmets, if length of vector is smaller than given vector 

	// workout_options shouldn't change if already exists, which it does since this is inside assignment operator
	workout_options.clear();
	trainers.erase(trainers.begin());
	actionsLog.erase(actionsLog.begin());
	copyPropertiesFrom(ref_otherStudio);

	return *this;
}


void Studio::copyPropertiesFrom(const Studio &ref_otherStudio) {
	// workout_options = ref_otherStudio.workout_options; // copy assignment

	open = ref_otherStudio.open;

	for (Workout workout : ref_otherStudio.workout_options) {
		workout_options.push_back(Workout(workout));
	}

	for (Trainer* ptr_trainer : ref_otherStudio.trainers) {
		trainers.push_back(new Trainer(*ptr_trainer));
	}

	for (BaseAction* ptr_action : ref_otherStudio.actionsLog) {
		actionsLog.push_back(ptr_action->duplicate());
	}
}


Studio::Studio(const std::string &configFilePath) {

	fstream configFile;
	configFile.open(configFilePath, ios::in);

	// supposedly we can assume the config file exists
	// if(configFile.is_open()) {
		Studio::parseConfigFile(configFile);
	// }
	// else {
	// 	// TODO: correct the error message and handling
	// 	cout << "ERROR: file wasn't opened." << endl;
	// }

	configFile.close(); //close the file object.
}


void Studio::start() {
	std::istringstream commandStream;
	std::cout << "Studio is now open!" << std::endl;
	string command; // for storing current user input

	do {
		// cout << "action> "; // TODO: see if need to remove this for automatic checks to pass
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
	} while(command != "closeall"); // command.compare("closeall") != 0
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
	ConfigSection currentConfigSection = ConfigSection::NUM_OF_TRAINERS;

	while( std::getline(configFile, configLine) ) { //read data from file object and put it into string.
		// cout << "[*] configLine is: " << configLine << endl; // TODO: remove debug line
		inputStreamFromStr.str(configLine);
		inputStreamFromStr.clear(); // clearing potentially set flags like EOF

		if (configLine[0] == '#') { // TODO: ask on forums if can be whitespace before the #
			continue;
		}
		else if (configLine.find_first_not_of(typeOfWhitespaces) == string::npos) {
			continue;
		}
		else {
			if (currentConfigSection == ConfigSection::NUM_OF_TRAINERS) {
				inputStreamFromStr >> numOfTrainers;
				
				// TODO: remove debug line
				// cout << "[*] at config section 'numOfTrainers' got int: '" << numOfTrainers << "'" << endl;

				currentConfigSection = ConfigSection::TRAINERS_CAPACITIES;
			}
			else if (currentConfigSection == ConfigSection::TRAINERS_CAPACITIES) {
				int capacity;

				for (int i = 0; i < numOfTrainers; ++i) {
					inputStreamFromStr >> capacity;
					inputStreamFromStr.ignore(numeric_limits<streamsize>::max(), ','); // ignores everything upto and including the next comma character

					// TODO: remove debug line
					// cout << "[*] at config section 'trainersCapacities' got capacity: '" << capacity << "'" << endl;
					trainers.push_back(new Trainer(capacity));
				}
			
				currentConfigSection = ConfigSection::WORKOUT_OPTIONS;
			}
			else { // currentConfigSection == ConfigSection::WORKOUT_OPTIONS
				int cost;
				std::getline(inputStreamFromStr, readingStr, ',');
				trim(readingStr, typeOfWhitespaces);
				std::getline(inputStreamFromStr, workoutType, ',');
				trim(workoutType, typeOfWhitespaces);
				inputStreamFromStr >> cost;


				// TODO: remove debug line
				// cout << "[*] at config section 'workoutOptions' got str: '" << readingStr << "' ::: '" << workoutType << "' ::: '" << cost << "'" << endl;
				
				workout_options.push_back(Workout(workout_options.size(), readingStr, cost, Workout::workoutTypeFromStr(workoutType)));
			}
		}
	}
}


void trim (string &str, const char* typeOfWhitespaces) {
	str.erase(str.find_last_not_of(typeOfWhitespaces) + 1); // TODO: see if this kind of indexing might throw an error
	str.erase(0,str.find_first_not_of(typeOfWhitespaces));
}
