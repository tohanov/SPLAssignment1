#ifndef STUDIO_H_
#define STUDIO_H_

#include <iostream>
#include <vector>
#include <string>
#include "Workout.h"
#include "Trainer.h"
#include "Action.h"

//using namespace std;


enum ConfigSection {
	numOfTrainers,
	trainersCapacities,
	workoutOptions
};


class Studio{		
public:
	Studio();
    Studio(const std::string &configFilePath);
    void start();
    int getNumOfTrainers() const;
    Trainer* getTrainer(int tid);
	const std::vector<BaseAction*>& getActionsLog() const; // Return a reference to the history of actions
    std::vector<Workout>& getWorkoutOptions();
	//TODO: rule of 5 (has trainers, workout_options?, actionsLog)
private:
    bool open;
    std::vector<Trainer*> trainers;
    std::vector<Workout> workout_options;
    std::vector<BaseAction*> actionsLog;
	
	// mine
	 std::vector<CommandHashPair> hashedCommandPairs;
	void parseConfigFile(std::fstream &configFile);
};

#endif
