#ifndef ACTION_H_
#define ACTION_H_

#include <string>
#include <iostream>
#include "Customer.h"

enum ActionStatus{
    COMPLETED, ERROR
};

//Forward declaration
class Studio;

class BaseAction{
public:
    BaseAction();
    ActionStatus getStatus() const;
    virtual void act(Studio& studio)=0;
    virtual std::string toString() const=0;
protected:
    void complete();
    void error(std::string errorMsg);
    std::string getErrorMsg() const;
private:
    std::string errorMsg;
    ActionStatus status;
};


// mine
struct  CommandHashPair {
	size_t commandTypeHash;
	BaseAction* (*matchingFunction)(std::istringstream &commandStream);
};


BaseAction* actionFromCommand(const std::string &command, std::vector<CommandHashPair> (&commandHashPairs));

BaseAction* backupActionFromCommand(std::istringstream &commandStream);
BaseAction* closeActionFromCommand(std::istringstream &commandStream);
BaseAction* closeallActionFromCommand(std::istringstream &commandStream);
BaseAction* logActionFromCommand(std::istringstream &commandStream);
BaseAction* moveActionFromCommand(std::istringstream &commandStream);
BaseAction* openActionFromCommand(std::istringstream &commandStream);
BaseAction* orderActionFromCommand(std::istringstream &commandStream);
BaseAction* restoreActionFromCommand(std::istringstream &commandStream);
BaseAction* statusActionFromCommand(std::istringstream &commandStream);
BaseAction* workout_optionsActionFromCommand(std::istringstream &commandStream);
// end mine


class OpenTrainer : public BaseAction {
public:
    OpenTrainer(int id, std::vector<Customer *> &customersList);
    void act(Studio &studio);
    std::string toString() const;
private:
	const int trainerId;
	std::vector<Customer *> customers;
};


class Order : public BaseAction {
public:
    Order(int id);
    void act(Studio &studio);
    std::string toString() const;
private:
    const int trainerId;
};


class MoveCustomer : public BaseAction {
public:
    MoveCustomer(int src, int dst, int customerId);
    void act(Studio &studio);
    std::string toString() const;
private:
    const int srcTrainer;
    const int dstTrainer;
    const int id;
};


class Close : public BaseAction {
public:
    Close(int id);
    void act(Studio &studio);
    std::string toString() const;
private:
    const int trainerId;
};


class CloseAll : public BaseAction {
public:
    CloseAll();
    void act(Studio &studio);
    std::string toString() const;
private:
};


class PrintWorkoutOptions : public BaseAction {
public:
    PrintWorkoutOptions();
    void act(Studio &studio);
    std::string toString() const;
private:
};


class PrintTrainerStatus : public BaseAction {
public:
    PrintTrainerStatus(int id);
    void act(Studio &studio);
    std::string toString() const;
private:
    const int trainerId;
};


class PrintActionsLog : public BaseAction {
public:
    PrintActionsLog();
    void act(Studio &studio);
    std::string toString() const;
private:
};


class BackupStudio : public BaseAction {
public:
    BackupStudio();
    void act(Studio &studio);
    std::string toString() const;
private:
};


class RestoreStudio : public BaseAction {
public:
    RestoreStudio();
    void act(Studio &studio);
    std::string toString() const;

};


#endif
