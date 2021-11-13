#include "Workout.h"

//enum WorkoutType{
//    ANAEROBIC, MIXED, CARDIO
//};
//
//class Workout{
//public:
//    Workout(int w_id, std::string w_name, int w_price, WorkoutType w_type);
//    int getId() const;
//    std::string getName() const;
//    int getPrice() const;
//    WorkoutType getType() const;
//private:
//	const int id;
//    const std::string name;
//    const int price;
//    const WorkoutType type;
//};



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


const std::string Workout::workoutTypeStrs[] = {"ANAEROBIC", "MIXED", "CARDIO"}; // static property


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


const std::string& Workout::strFromWorkoutType (WorkoutType w_type) {

	return workoutTypeStrs[w_type];
}
