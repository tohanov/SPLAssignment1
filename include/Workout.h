#ifndef WORKOUT_H_
#define WORKOUT_H_

#include <string>


enum WorkoutType{
    ANAEROBIC, MIXED, CARDIO
};


class Workout{
public:
    Workout(int w_id, std::string w_name, int w_price, WorkoutType w_type);
    int getId() const;
    std::string getName() const;
    int getPrice() const;
    WorkoutType getType() const;
	
	// added
    Workout (const Workout &ref_otherWorkout); // copy constructor
    // from string to workout type
	static WorkoutType workoutTypeFromStr (const std::string &workoutTypeStr);
    // from workout type to string
	static const std::string& strFromWorkoutType (WorkoutType w_type);
private:
	const int id;
    const std::string name;
    const int price;
    const WorkoutType type;

	// added
    // used in strFromWorkoutType
	static const std::string workoutTypeStrs[];
};

#endif
