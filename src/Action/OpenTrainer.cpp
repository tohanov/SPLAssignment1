#include "Action.h"

// TODO: complete implementation


OpenTrainer::OpenTrainer(int id, std::vector<Customer *> &customersList) : trainerId(id), customers(customersList) {
	// ?expects the vector of customers to be fresh without anyone sharing the same pointers?
}


void OpenTrainer::act(Studio& studio) {
	// TODO
}


std::string OpenTrainer::toString() const {
	//TODO
	return "***PLACEHOLDER***";
}


BaseAction* OpenTrainer::duplicate() {
	// TODO sync with how the copying of customers happens in the constructor
	vector<Cutomer *> newCustomers;
	for (Customer *ptr_customer : this->customers) {
		newCustomers.push_back(new Customer(*ptr_customer));
	}

	Order* ptr_newOpenTrainerAction = new OpenTrainer(this->trainerId, newCustomers);
	
    void matchFlags(this, ptr_newOpenTrainerAction);

	return ptr_newOpenTrainerAction;
}