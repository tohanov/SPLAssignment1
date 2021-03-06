#include "Action.h"


PrintActionsLog::PrintActionsLog () {
}


void PrintActionsLog::act(Studio& studio) {
	// never results in an error
	const vector<BaseAction*>& ref_actions = studio.getActionsLog();

	for (BaseAction* action : ref_actions) {
		cout << action->toString() << endl;
	}
	
	complete();
}


std::string PrintActionsLog::toString() const {
	return "log Completed";
}


BaseAction* PrintActionsLog::duplicate() {
	PrintActionsLog *ptr_printLogAction = new PrintActionsLog();

	return ptr_printLogAction;
}