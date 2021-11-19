#include "Action.h"


Close::Close (int id) : trainerId(id) {

}


void Close::act(Studio &studio) {
    const string errMsg = "Trainer does not exist or is not open";
    
    if(trainerId<0 || trainerId >= studio.getNumOfTrainers()) {
        error(errMsg);
        return;
    }

    Trainer *t1=studio.getTrainer(trainerId);

    if(!t1->isOpen()) {
        error(errMsg);
        return;
    }

    t1->closeTrainer();



    cout <<"Trainer "+ to_string(trainerId)+" closed. Salary "+ to_string(t1->getSalary())+"NIS"<<std::endl;

    complete();
}


std::string Close::toString() const {
	return "close " + to_string(trainerId) + " " + getStatusStr();
}


BaseAction* Close::duplicate() {

	Close *ptr_newCloseAction = new Close(this->trainerId);

	BaseAction::matchFlags(this, ptr_newCloseAction);

	return ptr_newCloseAction;
}