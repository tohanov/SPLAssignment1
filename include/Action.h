#ifndef ACTION_H_
#define ACTION_H_

#include <string>
#include <iostream>
#include "Customer.h"

enum ActionStatus{
    COMPLETED, ERROR
};

// begin added
// forward declaration for use in struct
class BaseAction;

struct  CommandHashPair {
	size_t commandTypeHash;
	BaseAction* (*matchingFunction)(std::istringstream &commandStream);
};
// end added


//Forward declaration
class Studio;

class BaseAction{
public:
    BaseAction();
    ActionStatus getStatus() const;
    virtual void act(Studio& studio)=0;
    virtual std::string toString() const=0;
	// added
	static BaseAction* actionFromCommand(std::istringstream &commandStream);
protected:
    void complete();
    void error(std::string errorMsg);
    std::string getErrorMsg() const;
private:
    std::string errorMsg;
    ActionStatus status;
	// added
	static std::hash<std::string> hasher;
	static CommandHashPair hashedCommandPairs[];
};


class OpenTrainer : public BaseAction {
public:
    OpenTrainer(int id, std::vector<Customer *> &customersList);
    void act(Studio &studio);
    std::string toString() const;
	// added
	static BaseAction* actionFromCommand(std::istringstream &commandStream);
private:
	const int trainerId;
	std::vector<Customer *> customers;
	// added
	static std::string strategies[];
};


class Order : public BaseAction {
public:
    Order(int id);
    void act(Studio &studio);
    std::string toString() const;
	// added
	static BaseAction* actionFromCommand(std::istringstream &commandStream);
private:
    const int trainerId;
};


class MoveCustomer : public BaseAction {
public:
    MoveCustomer(int src, int dst, int customerId);
    void act(Studio &studio);
    std::string toString() const;
	// added
	static BaseAction* actionFromCommand(std::istringstream &commandStream);
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
	// added
	static BaseAction* actionFromCommand(std::istringstream &commandStream);
private:
    const int trainerId;
};


class CloseAll : public BaseAction {
public:
    CloseAll();
    void act(Studio &studio);
    std::string toString() const;
	// added
	static BaseAction* actionFromCommand(std::istringstream &commandStream);
private:
};


class PrintWorkoutOptions : public BaseAction {
public:
    PrintWorkoutOptions();
    void act(Studio &studio);
    std::string toString() const;
	// added
	static BaseAction* actionFromCommand(std::istringstream &commandStream);
private:
};


class PrintTrainerStatus : public BaseAction {
public:
    PrintTrainerStatus(int id);
    void act(Studio &studio);
    std::string toString() const;
	// added
	static BaseAction* actionFromCommand(std::istringstream &commandStream);
private:
    const int trainerId;
};


class PrintActionsLog : public BaseAction {
public:
    PrintActionsLog();
    void act(Studio &studio);
    std::string toString() const;
	// added
	static BaseAction* actionFromCommand(std::istringstream &commandStream);
private:
};


class BackupStudio : public BaseAction {
public:
    BackupStudio();
    void act(Studio &studio);
    std::string toString() const;
	// added
	static BaseAction* actionFromCommand(std::istringstream &commandStream);
private:
};


class RestoreStudio : public BaseAction {
public:
    RestoreStudio();
    void act(Studio &studio);
    std::string toString() const;
	// added
	static BaseAction* actionFromCommand(std::istringstream &commandStream);

};
#endif
