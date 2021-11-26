#include "Action.h"


// static properties of OpenTrainer
ostringstream OpenTrainer::oss;
const string OpenTrainer::commonErrorMessage = "Trainer does not exist or is not open";


// Constructor
OpenTrainer::OpenTrainer(int id, std::vector<Customer *> &customersList) : trainerId(id), customers(customersList) {
	// rebuilding the command string to store for ::toString usage, without storing customer objects
	oss << "open " << this->trainerId;

	for (Customer *ptr_customer : customers) {
		oss << ' ' << ptr_customer->toString();
	}

    this->rebuiltCommandStr = oss.str();
    
    // resetting static ostringstream object
    oss.str("");
    oss.clear(); // flags
}


void OpenTrainer::act(Studio &studio) {
    if( ! Trainer::isValidTrainerId(trainerId)) {
        error(commonErrorMessage);
        deleteCustomers();		//deleting unused customers
    }
    else {
        Trainer* t1=studio.getTrainer(trainerId);

        if(t1->isOpen()) {
            error(commonErrorMessage);
            deleteCustomers();	//deleting unused customers
        }
        else {
            t1->openTrainer();

            size_t i=0;
            int current_num_of_customers=t1->getCustomers().size();
            while (i<customers.size() && current_num_of_customers < t1->getCapacity()){
                t1->addCustomer(customers[i]);
                customers[i] = nullptr;
                i++;
                current_num_of_customers++;
            }

            studio.notifyCustomersAddition(i);

            while (i<customers.size()){     // deleting customers that could not be added
                delete customers[i];
                i++;
            }

            complete();
        }
    }

    // those that were used are now pointed to by the Trainer instance, and those that weren't -
	// are now deleted. no need to store pointers
    customers.clear();
}


// copy constructor
OpenTrainer::OpenTrainer(const OpenTrainer &ref_otherOpenTrainer) : trainerId(ref_otherOpenTrainer.trainerId), rebuiltCommandStr(ref_otherOpenTrainer.rebuiltCommandStr) {
    matchFlags(&ref_otherOpenTrainer, this);

    // not actually going to run since the other action's customers list is cleared at this point, but needed for correctness of code for the course
    copyCustomers(ref_otherOpenTrainer, *this);
}


// move constructor
OpenTrainer::OpenTrainer(const OpenTrainer &&ref_otherOpenTrainer) : trainerId(ref_otherOpenTrainer.trainerId), customers(ref_otherOpenTrainer.customers), rebuiltCommandStr(ref_otherOpenTrainer.rebuiltCommandStr) {
    matchFlags(&ref_otherOpenTrainer, this);
}


// destructor
OpenTrainer::~OpenTrainer() {
    deleteCustomers();
}


// copy assignment not possible due to presense of const properties
// move assignment not possible due to presense of const properties


// deep copy of customers used in copy constructor
void OpenTrainer::copyCustomers(const OpenTrainer &ref_source, OpenTrainer &ref_destination) {
    for (Customer *ptr_customer : ref_source.customers) {
        ref_destination.customers.push_back(ptr_customer->duplicate());
    }
}


// free linked customer objects from memory
void OpenTrainer::deleteCustomers() {
    for(Customer* cus : customers) {
        delete cus;		// will itself perform check for nullptr
    }
}


std::string OpenTrainer::toString() const {
	return rebuiltCommandStr + ' ' + getStatusStr();
}


BaseAction* OpenTrainer::duplicate() {
    OpenTrainer *ptr_newOpenTrainerAction = new OpenTrainer(*this);

	return ptr_newOpenTrainerAction;
}