#include "Action.h"

// TODO: complete implementation

MoveCustomer::MoveCustomer (int src, int dst, int customerId) : srcTrainer(src), dstTrainer(dst), id(customerId) {

}


void MoveCustomer::act(Studio& studio) {
	// TODO
}


std::string MoveCustomer::toString() const {
	//TODO
	return "***PLACEHOLDER***";
}


BaseAction* Close::duplicate() {

	Close *ptr_newMoveAction = new Close(this->src, this->dst, this->customerId);

	BaseAction::matchFlags(this, ptr_newMoveAction);

	return ptr_newMoveAction;
}