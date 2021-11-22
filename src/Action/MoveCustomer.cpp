#include "Action.h"


MoveCustomer::MoveCustomer (int src, int dst, int customerId) : srcTrainer(src), dstTrainer(dst), id(customerId) {

}


void MoveCustomer::act(Studio &studio) {
    Trainer *src_trainer = studio.getTrainer(srcTrainer), *dst_trainer = studio.getTrainer(dstTrainer);

    if (src_trainer == nullptr || dst_trainer == nullptr || !src_trainer->isOpen() || !dst_trainer->isOpen()) {
        error("Cannot move customer");
        return;
    }

    if (static_cast<size_t>(dst_trainer->getCapacity()) == dst_trainer->getCustomers().size()) {
        error("Cannot move customer");
        return;
    }

    Customer *c = src_trainer->getCustomer(id);

    if (c == nullptr) {
        error("Cannot move customer");
        return;
    }

    src_trainer->removeCustomer(c->getId());
    dst_trainer->addCustomer(c);

    dst_trainer->order(c->getId(),c->order(studio.getWorkoutOptions()),studio.getWorkoutOptions());

    if(src_trainer->getCustomers().empty()){
        Close c(srcTrainer);
        c.act(studio);
    }
    complete();
}


std::string MoveCustomer::toString() const {
	return "move " + to_string(srcTrainer) + ' ' + to_string(dstTrainer) + ' ' + to_string(id) + ' ' + getStatusStr();
}


BaseAction* MoveCustomer::duplicate() {
	MoveCustomer *ptr_newMoveAction = new MoveCustomer(this->srcTrainer, this->dstTrainer, this->id);

	// BaseAction::matchFlags(this, ptr_newMoveAction);

	return ptr_newMoveAction;
}