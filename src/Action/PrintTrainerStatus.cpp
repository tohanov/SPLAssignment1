#include "Action.h"


PrintTrainerStatus::PrintTrainerStatus (int id) : trainerId(id) {
}


void PrintTrainerStatus::act(Studio& studio) {
	// never results in an error
	Trainer &ref_trainer = *(studio.getTrainer(trainerId));
	bool isOpen = ref_trainer.isOpen();
	static const char SPACE = ' ';

	cout << "Trainer " << trainerId << 
		" status: " << (isOpen ? "open" : "closed")  << endl;

	if (isOpen && ref_trainer.getOrders().size() != 0) {
		vector<Customer*> &ref_customers = ref_trainer.getCustomers();
		cout << "Customers:" << endl;

		for (Customer* ptr_customer : ref_customers) {
			cout << ptr_customer->getId() << SPACE << ptr_customer->getName() << endl;
		}

		vector<OrderPair> &ref_orders = ref_trainer.getOrders();
		cout << "Orders:" << endl;

		for (OrderPair pair : ref_orders) {
			cout << pair.second.getName() << SPACE << 
				pair.second.getPrice() << "NIS" << SPACE << 
				pair.first << endl;
		}

		cout << "Current Trainer's Salary: " << ref_trainer.getSalary() << "NIS" << endl;
	}

	complete();
}


std::string PrintTrainerStatus::toString() const {
	return "status " + to_string(trainerId) + " Completed";
}


BaseAction* PrintTrainerStatus::duplicate() {
	PrintTrainerStatus *ptr_printTrainerAction = new PrintTrainerStatus(this->trainerId);

	return ptr_printTrainerAction;
}