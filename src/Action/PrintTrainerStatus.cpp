#include "Action.h"


PrintTrainerStatus::PrintTrainerStatus (int id) : trainerId(id) {

}


// TODO: fix error caused by deletion of unused clients
void PrintTrainerStatus::act(Studio& studio) {
	// never results in an error

	// cout << "[*] inside PrintTrainerStatus::act()" << endl; // TODO: remove debug line
	Trainer &ref_trainer = *(studio.getTrainer(trainerId));
	bool isOpen = ref_trainer.isOpen();
	cout << "Trainer " << trainerId << " status: " << (isOpen ? "open" : "closed")  << endl;

	if (isOpen) {
		vector<Customer*> &ref_customers = ref_trainer.getCustomers();

		cout << "Customers:" << endl;
		for (Customer* ptr_customer : ref_customers) {
			cout << ptr_customer->getId() << ' ' << ptr_customer->getName() << endl;
		}

		vector<OrderPair> &ref_orders = ref_trainer.getOrders();

		cout << "Orders:" << endl;
		for (OrderPair pair : ref_orders) {
			cout << pair.second.getName() << ' ' << pair.second.getPrice() << ' ' << pair.first << endl;
		}

		cout << "Current Trainer's Salary: " << ref_trainer.getSalary() << "NIS" << endl;
	}

	complete();
}


std::string PrintTrainerStatus::toString() const {
	// ostringstream retStrStream;
	// retStrStream << "status " << trainerId << " " << getStatusStr();

	// return retStrStream.str();

	return "status " + to_string(trainerId) + " Completed";
}


BaseAction* PrintTrainerStatus::duplicate() {
	PrintTrainerStatus *ptr_printTrainerAction = new PrintTrainerStatus(this->trainerId);

	// BaseAction::matchFlags(this, ptr_printTrainerAction);

	return ptr_printTrainerAction;
}