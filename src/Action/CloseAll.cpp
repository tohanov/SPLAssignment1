#include "Action.h"


CloseAll::CloseAll () {
}


void CloseAll::act(Studio &studio) {
    for (int i = 0; i < studio.getNumOfTrainers(); i++) {
        if (studio.getTrainer(i)->isOpen()) {
            Close c(i);
            c.act(studio);
        }
    }

    studio.setClosed();
    complete();
}


std::string CloseAll::toString() const {
	return "closeall Completed";
}


BaseAction* CloseAll::duplicate() {
	CloseAll *ptr_newCloseAllAction = new CloseAll();

	return ptr_newCloseAllAction;
}