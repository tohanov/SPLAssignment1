#ifndef STUDIO_H_
#define STUDIO_H_

#include <iostream>
#include <vector>
#include <string>
#include "Workout.h"
#include "Trainer.h"
#include "Action.h"


// begin added
enum ConfigSection {
	NUM_OF_TRAINERS,
	TRAINERS_CAPACITIES,
	WORKOUT_OPTIONS
};

void trim (std::string &str, const char* typeOfWhitespaces);
// end added


class Studio{		
public:
	Studio();
    Studio(const std::string &configFilePath);
    void start();
    int getNumOfTrainers() const;
    Trainer* getTrainer(int tid);
	const std::vector<BaseAction*>& getActionsLog() const; // Return a reference to the history of actions
    std::vector<Workout>& getWorkoutOptions();

    // added
	//TODO: need rule of 5 (has trainers, actionsLog)
    Studio (const Studio &ref_otherStudio); // copy constructor
    Studio (const Studio &&ref_otherStudio); // move constructor
    Studio& operator=(const Studio &ref_otherStudio); // TODO: copy assignment operator
    Studio& operator=(const Studio &&ref_otherStudio); // TODO: move assignment operator
    virtual ~Studio(); // TODO: destructor
    void setClosed();
private:
    bool open;
    std::vector<Trainer*> trainers;
    std::vector<Workout> workout_options;
    std::vector<BaseAction*> actionsLog;
	
	// added
	void parseConfigFile(std::fstream &configFile);
    void deleteVectors ();
    void copyPropertiesFrom(const Studio &ref_otherStudio);
    void movePropertiesFrom(const Studio *ptr_otherStudio);
};

#endif
