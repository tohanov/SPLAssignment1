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
    Studio (const Studio &ref_otherStudio); // copy constructor
    Studio (const Studio &&ref_otherStudio); // move constructor
    Studio& operator=(const Studio &ref_otherStudio); // copy assignment operator
    Studio& operator=(const Studio &&ref_otherStudio); // move assignment operator
    virtual ~Studio(); // destructor
    void setClosed(); // notifies the studio that it should close and stop receiving user input
    int getLatestCustomerId() const; // used for customer unique id mechanism
    void notifyCustomersAddition(unsigned int increment); // used for customer unique id mechanism

private:
    bool open;
    std::vector<Trainer*> trainers;
    std::vector<Workout> workout_options;
    std::vector<BaseAction*> actionsLog;
	
	// added
    int latestCustomerId; // used for customer unique id mechanism

	void parseConfigFile(std::fstream &configFile); // parse file line by line
    void deleteVectors(); // used in assignment operators
    void copyPropertiesFrom(const Studio &ref_otherStudio); // used in copy constuctor and copy assignment operator
    void movePropertiesFrom(const Studio *ptr_otherStudio); // used in move constuctor and move assignment operator
};

#endif
