#include "Action.h"


OpenTrainer::OpenTrainer(int id, std::vector<Customer *> &customersList) : trainerId(id), customers(customersList) {
	// TODO: ?expects the vector of customers to be fresh without anyone sharing the same pointers?
}


void OpenTrainer::act(Studio &studio) {

	const string errMsg = "Workout session does not exist or is already open";

    if(trainerId<0 || trainerId >= studio.getNumOfTrainers()){

        for(Customer* cus:customers)    //deleting unused customers
            delete cus;

        error(errMsg);
        return;
    }


    Trainer* t1=studio.getTrainer(trainerId);

    if(t1->isOpen()) {
        error(errMsg);
        for(Customer* cus:customers)    //deleting unused customers
            delete cus;

        return;
    }

    t1->openTrainer();

    size_t i=0;
    int current_num_of_customers=t1->getCustomers().size();
    while (i<customers.size() && current_num_of_customers < t1->getCapacity()){
          t1->addCustomer(customers[i]);
          i++;
          current_num_of_customers++;
    }

    while (i<customers.size()){     // deleting customers that could not be added

        delete customers[i];
        i++;
    }

    complete();
}


std::string OpenTrainer::toString() const {
	// TODO: concatenation operation should be faster?
	ostringstream iss;

	iss << "open " << this->trainerId;

	for (Customer *ptr_customer : customers) {
		iss << ' ' << ptr_customer->toString();
	}

	iss << ' ' << getStatusStr();

	return iss.str();
}


BaseAction* OpenTrainer::duplicate() {
	// TODO: sync with how the copying of customers happens in the constructor
	vector<Customer *> newCustomers;
	for (Customer *ptr_customer : this->customers) {
		newCustomers.push_back(ptr_customer->duplicate());
	}

	OpenTrainer* ptr_newOpenTrainerAction = new OpenTrainer(this->trainerId, newCustomers);
	
    // BaseAction::matchFlags(this, ptr_newOpenTrainerAction);

	return ptr_newOpenTrainerAction;
}