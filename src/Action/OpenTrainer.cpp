#include "Action.h"

ostringstream OpenTrainer::oss; // static property of OpenTrainer

OpenTrainer::OpenTrainer(int id, std::vector<Customer *> &customersList) : trainerId(id), customers(customersList) {
	// TODO: ?expects the vector of customers to be fresh without anyone sharing the same pointers?

	oss << "open " << this->trainerId;

	for (Customer *ptr_customer : customers) {
		oss << ' ' << ptr_customer->toString();
	}

	// oss << ' ' << getStatusStr();

    this->rebuiltCommandStr = oss.str();
    
    oss.str("");
    oss.clear();
}


void OpenTrainer::act(Studio &studio) {

	const string errMsg = "Workout session does not exist or is already open";

    if(trainerId<0 || trainerId >= studio.getNumOfTrainers()){

        for(Customer* cus:customers)    //deleting unused customers
            delete cus;

        error(errMsg);
        // return;
    }
    else {

        Trainer* t1=studio.getTrainer(trainerId);

        if(t1->isOpen()) {
            error(errMsg);
            for(Customer* cus:customers)    //deleting unused customers
                delete cus;

            // return;
        }
        else {
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
    }

    this->rebuiltCommandStr += ' ' + getStatusStr();
}


std::string OpenTrainer::toString() const {
	// TODO: concatenation operation should be faster?
	return rebuiltCommandStr;
}


BaseAction* OpenTrainer::duplicate() {
	// TODO: sync with how the copying of customers happens in the constructor
	vector<Customer *> dummyVector;
	// for (Customer *ptr_customer : this->customers) {
	// 	newCustomers.push_back(ptr_customer->duplicate());
	// }

	OpenTrainer* ptr_newOpenTrainerAction = new OpenTrainer(this->trainerId, dummyVector);
	ptr_newOpenTrainerAction->rebuiltCommandStr = this->rebuiltCommandStr;

    // BaseAction::matchFlags(this, ptr_newOpenTrainerAction);

	return ptr_newOpenTrainerAction;
}