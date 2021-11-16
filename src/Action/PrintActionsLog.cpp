#include "Action.h"


PrintActionsLog::PrintActionsLog () {

}


void PrintActionsLog::act(Studio& studio) {
	// never results in an error
	const std::vector<BaseAction*>& ref_actions = studio.getActionsLog();

	for (BaseAction* action : ref_actions) {
		cout << (*action).toString() << endl;
	}
	
	complete();
}


std::string PrintActionsLog::toString() const {
	return "log Completed"; // + getStatusStr();
}


BaseAction* PrintActionsLog::duplicate() {

	PrintActionsLog *ptr_printLogAction = new PrintActionsLog();

	BaseAction::matchFlags(this, ptr_printLogAction);

	return ptr_printLogAction;
}