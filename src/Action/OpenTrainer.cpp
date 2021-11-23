#include "Action.h"


ostringstream OpenTrainer::oss; // static property of OpenTrainer
const string OpenTrainer::commonErrorMessage = "Workout session does not exist or is already open"; // static property


OpenTrainer::OpenTrainer(int id, std::vector<Customer *> &customersList) : trainerId(id), customers(customersList) {
	// TODO: ?expects the vector of customers to be fresh without anyone sharing the same pointers?

	oss << "open " << this->trainerId;

	for (Customer *ptr_customer : customers) {
		oss << ' ' << ptr_customer->toString();
	}

	// oss << ' ' << getStatusStr();

    this->rebuiltCommandStr = oss.str();
    
    oss.str("");
    oss.clear(); // flags
}


void OpenTrainer::act(Studio &studio) {
    // shouldn't do anything if no customers are given, according to answers at the forum
    // if (customers.size() != 0) {
    if(trainerId<0 || trainerId >= studio.getNumOfTrainers()){
        error(commonErrorMessage);
        deleteCustomers();    //deleting unused customers

        // return;
    }
    else {
        Trainer* t1=studio.getTrainer(trainerId);

        if(t1->isOpen()) {
            error(commonErrorMessage);
            deleteCustomers();    //deleting unused customers

            // return;
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

            while (i<customers.size()){     // deleting customers that could not be added
                delete customers[i];
                i++;
            }

            complete();
        }
    }
    // }

    // those that were used are now pointed to by the Trainer instance, and those that weren't are now deleted. no need to store pointers
    customers.clear();

    // this->rebuiltCommandStr += ' ' + getStatusStr();
}


// copy constructor
OpenTrainer::OpenTrainer(const OpenTrainer &ref_otherOpenTrainer) : trainerId(ref_otherOpenTrainer.trainerId), /*customers(ref_otherOpenTrainer.customers),*/ rebuiltCommandStr(ref_otherOpenTrainer.rebuiltCommandStr) {
    matchFlags(&ref_otherOpenTrainer, this);

    // not actually going to run since the other action's customers list is cleared at this point, but needed for correctness of code for the course
    copyCustomers(ref_otherOpenTrainer, *this);

    // this->rebuiltCommandStr = ref_otherOpenTrainer.rebuiltCommandStr;
    // this->customers;
}


// TODO: do with constructor of BaseAction
// move constructor
OpenTrainer::OpenTrainer(const OpenTrainer &&ref_otherOpenTrainer) : trainerId(ref_otherOpenTrainer.trainerId), customers(ref_otherOpenTrainer.customers), rebuiltCommandStr(ref_otherOpenTrainer.rebuiltCommandStr) {
    matchFlags(&ref_otherOpenTrainer, this);
}


// destructor
OpenTrainer::~OpenTrainer() {
    deleteCustomers();
}


// copy assignment
// OpenTrainer& OpenTrainer::operator=(const OpenTrainer &ref_otherOpenTrainer) {
//     // copyHeaders(ref_otherOpenTrainer, *this);

//     // matchFlags(&ref_otherOpenTrainer, this);

//     // // not actually going to do anything since the action's customers list is cleared at this point, but needed for correctlness of assignment
//     // deleteCustomers();

//     // // not actually going to do anything since the other action's customers list is cleared at this point, but needed for correctlness of assignment
//     // // for (Customer *ptr_customer : ref_otherOpenTrainer.customers) {
//     // //     this->customers.push_back(ptr_customer->duplicate());
//     // // }
//     // copyCustomers(ref_otherOpenTrainer, *this);


//     // return *this;
//     return performCopy(ref_otherOpenTrainer);
// }


// // move assignment
// OpenTrainer& OpenTrainer::operator=(const OpenTrainer &&ref_otherOpenTrainer) {
//     // copyHeaders(ref_otherOpenTrainer, *this);

//     // matchFlags(&ref_otherOpenTrainer, this);

//     // // not actually going to do anything since the action's customers list is cleared at this point, but needed for correctlness of assignment
//     // deleteCustomers();

//     // // not actually going to do anything since the other action's customers list is cleared at this point, but needed for correctlness of assignment
//     // for (Customer *ptr_customer : ref_otherOpenTrainer.customers) {
//     //     this->customers.push_back(ptr_customer->duplicate());
//     // }

//     // return *this;
//     // cout << "[*] inside move assignment" << endl; // TODO: remove debug
//     // return operator=(ref_otherOpenTrainer);

//     return performCopy(ref_otherOpenTrainer);
// }


// OpenTrainer& OpenTrainer::performCopy(const OpenTrainer &ref_otherOpenTrainer) {
//     copyHeaders(ref_otherOpenTrainer, *this);

//     matchFlags(&ref_otherOpenTrainer, this);

//     // not actually going to do anything since the action's customers list is cleared at this point, but needed for correctlness of assignment
//     deleteCustomers();

//     // not actually going to do anything since the other action's customers list is cleared at this point, but needed for correctlness of assignment
//     // for (Customer *ptr_customer : ref_otherOpenTrainer.customers) {
//     //     this->customers.push_back(ptr_customer->duplicate());
//     // }
//     copyCustomers(ref_otherOpenTrainer, *this);


//     return *this;
// }


// void OpenTrainer::copyHeaders(const OpenTrainer &ref_source, OpenTrainer &ref_destination) {
//     ref_destination.trainerId = ref_source.trainerId;
//     ref_destination.rebuiltCommandStr = ref_source.rebuiltCommandStr;
// }


void OpenTrainer::copyCustomers(const OpenTrainer &ref_source, OpenTrainer &ref_destination) {
    for (Customer *ptr_customer : ref_source.customers) {
        ref_destination.customers.push_back(ptr_customer->duplicate());
    }
}


void OpenTrainer::deleteCustomers() {
    for(Customer* cus : customers) {
        delete cus;
    }
}


std::string OpenTrainer::toString() const {
	// TODO: concatenation operation should be faster?
	return rebuiltCommandStr + ' ' + getStatusStr();
}


BaseAction* OpenTrainer::duplicate() {
	// TODO: sync with how the copying of customers happens in the constructor
	// vector<Customer *> dummyVector;
	// for (Customer *ptr_customer : this->customers) {
	// 	newCustomers.push_back(ptr_customer->duplicate());
	// }

	// OpenTrainer* ptr_newOpenTrainerAction = new OpenTrainer(this->trainerId, dummyVector);
	// ptr_newOpenTrainerAction->rebuiltCommandStr = this->rebuiltCommandStr;

    OpenTrainer *ptr_newOpenTrainerAction = new OpenTrainer(*this);

    // BaseAction::matchFlags(this, ptr_newOpenTrainerAction);

	return ptr_newOpenTrainerAction;
}