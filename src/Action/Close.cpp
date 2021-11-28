#include "Action.h"


// static property
const string Close::commonErrorMessage = "Trainer does not exist or is not open";


Close::Close (int id) : trainerId(id) {
}


void Close::act(Studio &studio) {
    if( ! Trainer::isValidTrainerId(trainerId)) {
        error(commonErrorMessage);
        return;
    }

    Trainer *t1 = studio.getTrainer(trainerId);

    if ( ! t1->isOpen()) {
        error(commonErrorMessage);
        return;
    }

    bool isEmpty=t1->getCustomers().empty();
    t1->closeTrainer();

    if(!isEmpty)
        cout <<"Trainer " + to_string(trainerId) + " closed. Salary " + to_string(t1->getSalary()) + "NIS"<<std::endl;

    complete();
}


std::string Close::toString() const {
	return "close " + to_string(trainerId) + ' ' + getStatusStr();
}


BaseAction* Close::duplicate() {
	Close *ptr_newCloseAction = new Close(this->trainerId);

	return ptr_newCloseAction;
}