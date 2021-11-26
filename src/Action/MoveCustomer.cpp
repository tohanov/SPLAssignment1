#include "Action.h"


// static
const string MoveCustomer::commonErrorMessage = "Cannot move customer";


MoveCustomer::MoveCustomer (int src, int dst, int customerId) : srcTrainer(src), dstTrainer(dst), id(customerId) {
}


void MoveCustomer::act(Studio &studio) {
    if( (! Trainer::isValidTrainerId(srcTrainer)) || (! Trainer::isValidTrainerId(dstTrainer)) ) {
        error(commonErrorMessage);
        return;
    }

    Trainer *src_trainer = studio.getTrainer(srcTrainer);
    Trainer *dst_trainer = studio.getTrainer(dstTrainer);

    if ( (!src_trainer->isOpen()) || (!dst_trainer->isOpen()) ) {
        error(commonErrorMessage);
        return;
    }

    if (static_cast<size_t>(dst_trainer->getCapacity()) == dst_trainer->getCustomers().size()) {
        error(commonErrorMessage);
        return;
    }

    Customer *c = src_trainer->getCustomer(id);

    if (c == nullptr) {
        error(commonErrorMessage);
        return;
    }

    src_trainer->removeCustomer(c->getId());
    dst_trainer->addCustomer(c);

    dst_trainer->order(
        c->getId(), 
        c->order(studio.getWorkoutOptions()), 
        studio.getWorkoutOptions());

    if(src_trainer->getCustomers().empty()) {
        Close close(srcTrainer);
        close.act(studio);
    }

    complete();
}


std::string MoveCustomer::toString() const {
	return "move " + to_string(srcTrainer) + ' ' + to_string(dstTrainer) + ' ' + to_string(id) + ' ' + getStatusStr();
}


BaseAction* MoveCustomer::duplicate() {
	MoveCustomer *ptr_newMoveAction = new MoveCustomer(this->srcTrainer, this->dstTrainer, this->id);

	return ptr_newMoveAction;
}