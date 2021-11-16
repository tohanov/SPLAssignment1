#ifndef TRAINER_H_
#define TRAINER_H_

#include <vector>
#include "Workout.h"
// #include "Action.h"
#include "Customer.h"

typedef std::pair<int, Workout> OrderPair;

class Trainer{
public:
    Trainer(int t_capacity);
    Trainer(const Trainer &to_copy);
    ~Trainer();
    int getCapacity() const;
    void addCustomer(Customer* customer);
    void removeCustomer(int id);
    Customer* getCustomer(int id);
    std::vector<Customer*>& getCustomers();
    std::vector<OrderPair>& getOrders();
    void order(const int customer_id, const std::vector<int> workout_ids, const std::vector<Workout>& workout_options);
    void openTrainer();
    void closeTrainer();
    int getSalary();
    bool isOpen();

private:

    int capacity;
    int current_salary;
    const int id;
    bool open;
    std::vector<Customer*> customersList;
    std::vector<OrderPair> orderList; //A list of pairs for each order for the trainer - (customer_id, Workout)
    static int number_of_trainers;
    const int get_id() const;
    static void update_number_of_trainers();
    void update_salary(int sum);

    int find_customer_index(int id);
    int find_insertion_index(int id);
};


#endif
