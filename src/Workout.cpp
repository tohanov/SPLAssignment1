#include "Workout.h"


Workout::Workout(int w_id, std::string w_name, int w_price, WorkoutType w_type) : id(w_id), name(w_name), price(w_price), type(w_type) {
}


int Workout::getId() const {
	return id;
}


std::string Workout::getName() const {
	return name;
}


int Workout::getPrice() const {
	return price;
}


WorkoutType Workout::getType() const {
	return type;
}


Workout::Workout (const Workout &ref_otherWorkout) : id(ref_otherWorkout.id), name(ref_otherWorkout.name), price(ref_otherWorkout.price), type(ref_otherWorkout.type) {
}


// from string to workout type
WorkoutType Workout::workoutTypeFromStr (const std::string &workoutTypeStr) { // assuming workoutTypeStr is trimmed

	switch(workoutTypeStr[0]){
		case 'A':
			return WorkoutType::ANAEROBIC;
		case 'M':
			return WorkoutType::MIXED;
		default: // 'C'
			return WorkoutType::CARDIO;
	}
}


// static
// used in strFromWorkoutType
const std::string Workout::workoutTypeStrs[] = {"ANAEROBIC", "MIXED", "CARDIO"};


// from workout type to string
const std::string& Workout::strFromWorkoutType (WorkoutType w_type) {

	return workoutTypeStrs[w_type];
}
