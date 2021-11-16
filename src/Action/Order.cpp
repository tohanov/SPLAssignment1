#include "Action.h"


Order::Order (int id) : trainerId(id) {

}


void Order::act(Studio &studio) {
    Trainer* t1=studio.getTrainer(trainerId);

    if(t1== nullptr || !t1->isOpen()) {
        error("Workout session does not exist or is not open");
        return;
    }

    for(int i=0;i<t1->getCustomers().size();i++) {    //giving the trainer current customer's workout plan
        std::vector<int> v1 = t1->getCustomers()[i]->order(studio.getWorkoutOptions());

        for(int j=v1.size();j>=0;j--){                // printing
            std::cout<<t1->getCustomers()[j]->getName()+" IS DOING "+t1->getOrders()[t1->getOrders().size()-j].second.getName();

        }

        t1->order(t1->getCustomers()[i]->getId(), v1, studio.getWorkoutOptions());  //inserting the orders to trainer

    }

    complete();
}


std::string Order::toString() const {
	return "order " + to_string(trainerId) + " " + getStatusStr();
}


BaseAction* Order::duplicate() {
	Order* ptr_newOrderAction = new Order(this->trainerId);
	
    BaseAction::matchFlags(this, ptr_newOrderAction);

	return ptr_newOrderAction;
}