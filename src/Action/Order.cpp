#include "Action.h"


// static
const string Order::commonErrorMessage = "Trainer does not exist or is not open";


Order::Order (int id) : trainerId(id) {
}


void Order::act(Studio &studio) {
    if( ! Trainer::isValidTrainerId(trainerId)) {
        error(commonErrorMessage);
        return;
    }

    Trainer* t1=studio.getTrainer(trainerId);

    if(!t1->isOpen()) {
        error(commonErrorMessage);
        return;
    }

    for(size_t i=0;i<t1->getCustomers().size();i++) {    //giving the trainer current customer's workout plan
        std::vector<int> v1 = t1->getCustomers()[i]->order(studio.getWorkoutOptions());

        t1->order(t1->getCustomers()[i]->getId(), v1, studio.getWorkoutOptions());  //inserting the orders to trainer

        for(unsigned long j=v1.size();j>0;j--){                // printing
           std::cout<<t1->getCustomers()[i]->getName()+" Is Doing "+t1->getOrders()[t1->getOrders().size()-j].second.getName()<<std::endl;

        }
    }

    complete();
}


std::string Order::toString() const {
	return "order " + to_string(trainerId) + ' ' + getStatusStr();
}


BaseAction* Order::duplicate() {
	Order* ptr_newOrderAction = new Order(this->trainerId);

	return ptr_newOrderAction;
}