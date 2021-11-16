#include "Action.h"


CloseAll::CloseAll () {

}


void CloseAll::act(Studio &studio) {

    for(int i=0;i<studio.getNumOfTrainers();i++)
        if (studio.getTrainer(i)->isOpen()){
            studio.getTrainer(i)->closeTrainer();
            std::cout<<"Trainer "+ to_string(i)+" closed. Salary "+ to_string(studio.getTrainer(i)->getSalary())+"NIS"<<std::endl;
        }

    complete();

    // std::cout<<"Studio is now closed!"<<endl;
    // exit(0);
}


std::string CloseAll::toString() const {
	return "closeall Completed"; // + getStatusStr();
}


BaseAction* CloseAll::duplicate() {

	CloseAll *ptr_newCloseAllAction = new CloseAll();

	BaseAction::matchFlags(this, ptr_newCloseAllAction);

	return ptr_newCloseAllAction;
}