#include "Action.h"

// TODO: complete implementation

Order::Order (int id) : trainerId(id) {

}


void Order::act(Studio& studio) {
	// TODO
}


std::string Order::toString() const {
	//TODO
	return "***PLACEHOLDER***";
}


BaseAction* Order::duplicate() {
	Order* ptr_newOrderAction = new Order(this->trainerId);
	
    BaseAction::matchFlags(this, ptr_newOrderAction);

	return ptr_newOrderAction;
}