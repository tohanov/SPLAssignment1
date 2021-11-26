#ifndef CUSTOMER_H_
#define CUSTOMER_H_

#include <vector>
#include <string>
#include "Workout.h"
#include <iostream>


class Customer{
public:
    Customer(std::string c_name, int c_id);
    Customer(const Customer &to_copy); //copy constructor
    virtual ~Customer();//destructor
    //Customer& operator=(const Customer &to_assign);//assignment constructor
    virtual std::vector<int> order(const std::vector<Workout> &workout_options)=0;
    virtual std::string toString() const = 0;
    std::string getName() const;
    int getId() const;

    // added
    virtual Customer* duplicate()=0;
private:
    const std::string name;
    const int id;
};


class SweatyCustomer : public Customer {
public:
    SweatyCustomer(std::string name, int id);
    std::vector<int> order(const std::vector<Workout> &workout_options);
    std::string toString() const;

    // added
    virtual Customer* duplicate();
private:
};


class CheapCustomer : public Customer {
public:
    CheapCustomer(std::string name, int id);
    std::vector<int> order(const std::vector<Workout> &workout_options);
    std::string toString() const;

    // added
    virtual Customer* duplicate();
private:
};


class HeavyMuscleCustomer : public Customer {
public:
    HeavyMuscleCustomer(std::string name, int id);
    std::vector<int> order(const std::vector<Workout> &workout_options);
    std::string toString() const;

    // added
    virtual Customer* duplicate();
private:
};


class FullBodyCustomer : public Customer {
public:
    FullBodyCustomer(std::string name, int id);
    std::vector<int> order(const std::vector<Workout> &workout_options);
    std::string toString() const;

    // added
    virtual Customer* duplicate();
private:
};

int find_cheapest_workout(const std::vector<Workout> &workout_options);
int find_cheapest_workout(const std::vector<Workout> &workout_options,WorkoutType type);
int find_most_expensive_mixed_workout(const std::vector<Workout> &workout_options);

#endif
