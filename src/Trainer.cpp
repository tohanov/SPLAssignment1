#include "Trainer.h"

// static
int Trainer::number_of_trainers=0;


Trainer::Trainer(int t_capacity) : capacity(t_capacity), id(number_of_trainers), openedBefore(false) {
    current_salary=0;
    open=false;

    update_number_of_trainers();
}


// partial rule of 5 implementation due to presense of const properties
Trainer::Trainer(const Trainer &to_copy): id(to_copy.get_id()) {	//Copy constructor
    copy_properties_from_trainer(to_copy);
}



Trainer::Trainer(const Trainer &&to_move) : id(to_move.get_id()) {    //move constructor
    move_properties_from_trainer(&to_move);
}


// copy assignment not possible due to presense of const properties
// move assignment not possible due to presense of const properties


//Destructor
Trainer::~Trainer() {
    for (Customer *ptr_customer : customersList) {
        delete ptr_customer;
    }

    customersList.clear();
}


//added functions:

void Trainer::copy_properties_from_trainer(const Trainer &to_copy) {
    capacity = to_copy.getCapacity();
    openedBefore = to_copy.openedBefore;
    open=to_copy.open;
    current_salary=to_copy.current_salary;

    for(auto customer:to_copy.customersList)
        customersList.push_back(customer->duplicate());

    for(auto order:to_copy.orderList)
        orderList.emplace_back(order.first,order.second);

}

void Trainer::move_properties_from_trainer(const Trainer *to_move) {
    capacity = to_move->getCapacity();
    openedBefore = to_move->openedBefore;
    open=to_move->open;
    current_salary=to_move->current_salary;

    for(auto cus:to_move->customersList)
        customersList.push_back(cus);

    for(auto order:to_move->orderList)
        orderList.push_back(order);

}

void Trainer::delete_vectors_trainer() {
    orderList.clear();

    for(auto cus:customersList)
        delete cus;

    customersList.clear();

}


int Trainer::getCapacity() const{
    return capacity;
}


void Trainer::addCustomer(Customer* customer){
    if(customersList.size()<static_cast<size_t>(capacity)){

       int insertion_index=find_insertion_index(customer->getId());
       customersList.insert(customersList.begin()+insertion_index,customer);
   }
}


void Trainer::removeCustomer(int id){
    int customer_index= find_customer_index(id);

    if (customer_index!=-1) {
        std::vector<OrderPair> new_orderList;

        for(auto it1: orderList)
            if (it1.first==id)
                update_salary(-1* it1.second.getPrice());
            else
                new_orderList.emplace_back(it1.first,it1.second);

        orderList.clear();

       for(auto it2 : new_orderList)
           orderList.push_back(it2);

        customersList.erase(customersList.begin() + customer_index, customersList.begin() + customer_index + 1);
    }

}


Customer* Trainer::getCustomer(int id){
    int customer_index= find_customer_index(id);

    if(customer_index!=-1)
        return getCustomers()[customer_index];
    else
        return nullptr;
}


std::vector<Customer*>& Trainer::getCustomers(){
    std::vector<Customer*>& refCustomersList=customersList;
    return refCustomersList;
}


std::vector<OrderPair>& Trainer::getOrders(){
    std::vector<OrderPair>& refOrderList=orderList;
    return refOrderList;
}


void Trainer::order(const int customer_id, const std::vector<int> workout_ids, const std::vector<Workout> &workout_options) {
    for (size_t i = 0; i < workout_ids.size(); i++)
        for (size_t j = 0; j < workout_options.size(); j++)
            if (workout_options[j].getId() == workout_ids[i]) {
                orderList.emplace_back(customer_id, workout_options[j]);

                update_salary(workout_options[j].getPrice());
            }
}


void Trainer::openTrainer() {
    openedBefore = true;
    if (open)
        std::cout<<"Trainer already open"<<std::endl; // TODO: remove debug before submission
    else
        open= true;
}


void Trainer::closeTrainer(){
    if (!open)
        std::cout<<"Trainer already closed"<<std::endl; // TODO: remove debug before submission
    else{
        open= false;
        orderList.clear();
        for (auto p:customersList) {
            delete p;
        }
        customersList.clear();
    }
}


int Trainer::getSalary(){
    return current_salary;
}


bool Trainer::isOpen(){
    return open;
}


//auxiliary functions
int Trainer::find_customer_index(int id) {
    int low = 0, high =customersList.size()-1 , middle;

    while (high >= low) {
        middle = (low + high) / 2;

        if(getCustomers()[middle]->getId()==id)
            return middle;
        else if (getCustomers()[middle]->getId() > id)
            high = middle - 1;
        else                // no 2 customers have same id
            low = middle + 1;
    }

    return -1;

}


int Trainer::find_insertion_index(int id) {
    int low = 0, high =customersList.size()-1 , middle;

    while (high >= low) {
        middle = (low + high) / 2;

        if(getCustomers()[middle]->getId()==id)
            return middle;
        else if (getCustomers()[middle]->getId() > id)
            high = middle - 1;
        else                // no 2 customers have same id
            low = middle + 1;
    }

    return high+1;


}


const int Trainer::get_id() const {
    return id;
}


void Trainer::update_number_of_trainers() {
    number_of_trainers++;
}


void Trainer::update_salary(int sum){
    current_salary+=sum;

}


// returns true if trainer was opened at least once before
bool Trainer::getOpenedBefore() const {
    return openedBefore;
}


// static
// used in checks acrross the project
bool Trainer::isValidTrainerId(int _trainerId) { // static function
    return (_trainerId >= 0) && (_trainerId < number_of_trainers);
}