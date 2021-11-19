#include "Action.h"


PrintWorkoutOptions::PrintWorkoutOptions () {

}


void PrintWorkoutOptions::act(Studio& studio) {
	// never results in an error
	const string COMMA = ", ";
	
	// TODO: see if there are assignments of references to objects, and fix (should be reference to reference)
	const std::vector<Workout>& refWorkoutOptions = studio.getWorkoutOptions();

	for (Workout wo : refWorkoutOptions) {
		cout << wo.getName() << COMMA << Workout::strFromWorkoutType(wo.getType()) << COMMA << wo.getPrice() << endl;
	}

	complete();
}


std::string PrintWorkoutOptions::toString() const {
	return "workout_options Completed";// + getStatusStr();
}


BaseAction* PrintWorkoutOptions::duplicate() {

	PrintWorkoutOptions *ptr_printWorkoutAction = new PrintWorkoutOptions();

	BaseAction::matchFlags(this, ptr_printWorkoutAction);

	return ptr_printWorkoutAction;
}