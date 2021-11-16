#include "Trainer.h"


int Trainer::number_of_trainers=0;


Trainer::Trainer(int t_capacity):id(number_of_trainers),capacity(t_capacity){
    current_salary=0;
    open=false;

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
    for (auto p:customersList) {
        delete p;
    }

}


int Trainer::getCapacity() const{
    return capacity;
}


void Trainer::addCustomer(Customer* customer){
    if(customersList.size()<capacity){

       int insertion_index=find_insertion_index(customer->getId());
       auto it=customersList.insert(customersList.begin()+insertion_index,customer);
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

    for(int i=0;i<workout_ids.size();i++)
        for(int j=0;j<workout_options.size();j++)
            if(workout_options[j].getId()==workout_ids[i]) {
                orderList.emplace_back(customer_id, workout_options[j]);

                update_salary(workout_options[j].getPrice());
            }

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
    return  id;
}


void Trainer::update_number_of_trainers() {
    number_of_trainers++;
}


void Trainer::update_salary(int sum){
    current_salary+=sum;

}
