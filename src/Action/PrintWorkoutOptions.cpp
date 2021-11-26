#include "Action.h"


PrintWorkoutOptions::PrintWorkoutOptions () {
}


void PrintWorkoutOptions::act(Studio& studio) {
	// never results in an error
	const string COMMA = ", ";
	const vector<Workout>& refWorkoutOptions = studio.getWorkoutOptions();

	for (Workout wo : refWorkoutOptions) {
		cout << wo.getName() << COMMA << 
			Workout::strFromWorkoutType(wo.getType()) << COMMA << 
			wo.getPrice() << endl;
	}

	complete();
}


std::string PrintWorkoutOptions::toString() const {
	return "workout_options Completed";
}


BaseAction* PrintWorkoutOptions::duplicate() {
	PrintWorkoutOptions *ptr_printWorkoutAction = new PrintWorkoutOptions();

	return ptr_printWorkoutAction;
}