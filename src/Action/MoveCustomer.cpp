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


BaseAction* MoveCustomer::duplicate() {
	MoveCustomer *ptr_newMoveAction = new MoveCustomer(this->srcTrainer, this->dstTrainer, this->id);

	BaseAction::matchFlags(this, ptr_newMoveAction);

	return ptr_newMoveAction;
}