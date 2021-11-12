#include "Trainer.h"

int Trainer::number_of_trainers=0;

Trainer::Trainer(int t_capacity):id(number_of_trainers),capacity(t_capacity){
    current_salary=0;
    open=false;
    std::vector<Customer*> customersList={};
    std::vector<OrderPair> orderList={};

    update_number_of_trainers();

}

//Copy constructor
Trainer::Trainer(const Trainer &to_copy):capacity(to_copy.getCapacity()),id(to_copy.get_id()) {
    current_salary=to_copy.current_salary;
    open=to_copy.open;

    //deep copies
    for(int i=0;i<to_copy.customersList.size();i++)
        customersList.push_back(to_copy.customersList[i]);

    for(int i=0;i<to_copy.orderList.size();i++)
        orderList.push_back(to_copy.orderList[i]);

}

//Destructor
Trainer::~Trainer() {
    customersList.clear();
    orderList.clear();
}


int Trainer::getCapacity() const{
    return capacity;
}

void Trainer::addCustomer(Customer* customer){
    customersList.push_back(customer);
}
void Trainer::removeCustomer(int id){
    bool found=false;
    for(int i=0;!found && i<customersList.size();i++){
        if (customersList[i]->getId()==id){
            customersList.erase(customersList.begin()+i,customersList.begin()+i+1);
            found= true;
        }

    }

}
Customer* Trainer::getCustomer(int id){
    for (int i=0;i<getCustomers().size();i++)
        if(getCustomers()[i]->getId()==id)
            return getCustomers()[i];

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
    // assuming valid input: trainer is open, number of customers doesn't exceed capacity, akk id's exist
    if(open && customersList.size()<capacity)
        for(int i=0;i<workout_ids.size();i++)
            for(int j=0;j<workout_options.size();j++)
                if(workout_options[j].getId()==workout_ids[i])
                    orderList.emplace_back(customer_id,workout_options[j]);

}

void Trainer::openTrainer(){
    if (open)
        std::cout<<"Trainer already open"<<std::endl;
    else
        open= true;
}
void Trainer::closeTrainer(){
    if (!open)
        std::cout<<"Trainer already closed"<<std::endl;
    open= false;
}
int Trainer::getSalary(){
    return current_salary;
}
bool Trainer::isOpen(){
    return open;
}

//auxiliary functions
const int Trainer::get_id() const {
    return  id;
}

void Trainer::update_number_of_trainers() {
    number_of_trainers++;
}
void Trainer::update_salary(){
    for(int i=0;i<getOrders().size();i++)
        current_salary+=getOrders()[i].second.getPrice();

}
