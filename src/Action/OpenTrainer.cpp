#include "Action.h"


OpenTrainer::OpenTrainer(int id, std::vector<Customer *> &customersList) : trainerId(id), customers(customersList) {
	// TODO: ?expects the vector of customers to be fresh without anyone sharing the same pointers?
}


void OpenTrainer::act(Studio &studio) {
    Trainer* t1=studio.getTrainer(trainerId);

    if(t1== nullptr || t1->isOpen()) {
        error("Workout session does not exist or is already open");
        return;
    }

    if (t1->getCustomers().size()+customers.size()>t1->getCapacity()){
        error("Trainer's capacity is not enough!");
        return;
    }

    t1->openTrainer();

    for (int i = 0; i < customers.size(); ++i) {
        t1->addCustomer(customers[i]);
    }

    complete();
}


std::string OpenTrainer::toString() const {
	// TODO: concatenation operation should be faster
	ostringstream iss;

	iss << "open " << this->trainerId;

	for (Customer *ptr_customer : customers) {
		iss << " " << ptr_customer->toString();
	}

	iss << " " << getStatusStr() << endl;

	return iss.str();
}


BaseAction* OpenTrainer::duplicate() {
	// TODO: sync with how the copying of customers happens in the constructor
	vector<Customer *> newCustomers;
	for (Customer *ptr_customer : this->customers) {
		newCustomers.push_back(ptr_customer->duplicate());
	}

	OpenTrainer* ptr_newOpenTrainerAction = new OpenTrainer(this->trainerId, newCustomers);
	
    BaseAction::matchFlags(this, ptr_newOpenTrainerAction);

	return ptr_newOpenTrainerAction;
}