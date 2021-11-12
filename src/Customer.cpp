#include "Customer.h"
#include <string>
//Constructors:
//Constructor of base class
Customer::Customer(std::string c_name, int c_id):id(c_id),name(c_name){}

//Constructors of the derived classes
SweatyCustomer::SweatyCustomer(std::string name, int id):Customer(name,id){}

CheapCustomer::CheapCustomer(std::string name, int id):Customer(name,id){}

HeavyMuscleCustomer::HeavyMuscleCustomer(std::string name, int id):Customer(name,id){}

FullBodyCustomer::FullBodyCustomer(std::string name, int id):Customer(name,id){}

//Copy constructor:
Customer::Customer(const Customer &to_copy):name(to_copy.getName()),id(to_copy.getId()){}

//Destructor
Customer::~Customer() = default;


//Copy assignment constructor
//Customer& Customer::operator=(const Customer &to_assign) {}






int Customer::getId() const{
    return id;
}

std::string Customer::getName() const{
    return name;
}

std::string SweatyCustomer::toString() const {
    return "Customer's type: sweaty customer. Customer's name: "+this->getName()+". Customer's  id: "+std::to_string(getId());
}

std::string CheapCustomer::toString() const {
    return "Customer's type: cheap customer. Customer's name: "+this->getName()+". Customer's  id: "+std::to_string(getId());
}

std::string HeavyMuscleCustomer::toString() const {
    return "Customer's type: heavy muscle customer. Customer's name: "+this->getName()+". Customer's  id: "+std::to_string(getId());
}

std::string FullBodyCustomer::toString() const {
    return "Customer's type: full body customer. Customer's name: "+this->getName()+". Customer's  id: "+std::to_string(getId());
}

// implementation of the virtual function "order"

std::vector<int> SweatyCustomer::order(const std::vector<Workout> &workout_options){
    std::vector<int> output={};

    for(int i=0;i<workout_options.size();i++)
        if(workout_options[i].getType()==CARDIO)
            output.push_back(workout_options[i].getId());

    return output;

}

std::vector<int> CheapCustomer::order(const std::vector<Workout> &workout_options){
    std::vector<int> output={};

    if(workout_options.size()>0)
        output.push_back(workout_options[find_cheapest_workout(workout_options)].getId());

    return output;
}

std::vector<int> HeavyMuscleCustomer::order(const std::vector<Workout> &workout_options){
    std::vector<const Workout*> anaerobic_workouts={};
    std::vector<int> output={};

    for(int i=0;i<workout_options.size();i++)
        if(workout_options[i].getType()==ANAEROBIC){
            const Workout *p_workout;
            p_workout=&workout_options[i];
            anaerobic_workouts.push_back(p_workout);

        }

    // now sort anaerobic_workouts by price, min price to max, insertion sort
    int i,j,key;
    for(i=1;i<anaerobic_workouts.size();i++){
        key=anaerobic_workouts[i]->getPrice();
        j=i-1;

        while(j>=0 && key<anaerobic_workouts[j]->getPrice()){
            anaerobic_workouts[j+1]=anaerobic_workouts[j];
            j--;
        }

        anaerobic_workouts[j+1]=anaerobic_workouts[i];
    }

    for(i=anaerobic_workouts.size()-1;i>=0;i--)
        output.push_back(anaerobic_workouts[i]->getId());


    return output;
}

std::vector<int> FullBodyCustomer::order(const std::vector<Workout> &workout_options){
    std::vector<int> output={};

    int workout1=find_cheapest_workout(workout_options,CARDIO);
    int workout2=find_most_expensive_mixed_workout(workout_options);
    int workout3=find_cheapest_workout(workout_options, ANAEROBIC);

    if(workout1!=-1 && workout2!=-1 && workout3!=-1){
        output.push_back(workout_options[workout1].getId());
        output.push_back(workout_options[workout2].getId());
        output.push_back(workout_options[workout3].getId());

    }

    return output;

}

//auxiliary functions:

int find_cheapest_workout(const std::vector<Workout> &workout_options){
    if(workout_options.empty())
        return -1;

    int min_index=0;
    for(int i=1;i<workout_options.size();i++)
        if(workout_options[i].getPrice() < workout_options[min_index].getPrice())
            min_index=i;

    return min_index;
}

int find_cheapest_workout(const std::vector<Workout> &workout_options,WorkoutType type){
    int min_index=-1,i;

    for(i=0;min_index==-1 && i<workout_options.size();i++){ // finding first instance of desired type
        if(workout_options[i].getType()==type)
            min_index=i;

    }

    if(min_index!=-1){
        for(;i<workout_options.size();i++)
            if(workout_options[i].getType()==type && workout_options[i].getPrice() < workout_options[min_index].getPrice())
                min_index=i;


    }

    return min_index;
}

int find_most_expensive_mixed_workout(const std::vector<Workout> &workout_options){
    int max_index=-1,i;

    for(int i=0;max_index==-1 && i<workout_options.size();i++){ // finding first instance of mixed
        if(workout_options[i].getType()==MIXED)
            max_index=i;

    }

    if(max_index!=-1){
        for(int i=i;i<workout_options.size();i++)
            if(workout_options[i].getType()==MIXED && workout_options[i].getPrice() > workout_options[max_index].getPrice())
                max_index=i;


    }

    return max_index;


}

