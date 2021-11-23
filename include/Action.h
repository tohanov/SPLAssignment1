#ifndef ACTION_H_
#define ACTION_H_

#include <string>
#include <iostream>
#include "Customer.h"

using namespace std;

enum ActionStatus {
    COMPLETED, ERROR
};


//Forward declaration
class Studio;


// begin added
class BaseAction; // forward declaration for use in struct

struct CommandHashPair {
	size_t commandTypeHash;
	BaseAction* (*matchingFunction)(istringstream &commandStream, Studio &ref_studio);
};

enum ActionType {
    BASE,
    OPEN_TRAINER,
    ORDER,
    MOVE_CUSTOMER,
    CLOSE,
    CLOSE_ALL,
    PRNT_WORKOUT_OPTS,
    PRNT_TRAINER_STATUS,
    PRNT_ACTIONS_LOG,
    BACKUP,
    RESTORE
};
// end added


class BaseAction{
public:
    BaseAction();
    ActionStatus getStatus() const;
    virtual void act(Studio& studio)=0;
    virtual std::string toString() const=0;
	// added
    // BaseAction(const BaseAction &ref_otherBaseAction);
	static BaseAction* actionFromCommand(std::istringstream &commandStream, Studio &ref_studio);
    virtual BaseAction* duplicate()=0;
    virtual ~BaseAction();
    static void matchFlags(const BaseAction *source, BaseAction *destination);
protected:
    void complete();
    void error(std::string errorMsg);
    std::string getErrorMsg() const;
	
	// added
	string getStatusStr() const;
private:
    std::string errorMsg;
    ActionStatus status;

	// added
	static const std::hash<std::string> hasher;
	static const CommandHashPair hashedCommandPairs[];
	// static const string statusStrs[];
};


class OpenTrainer : public BaseAction {
public:
    OpenTrainer(int id, std::vector<Customer *> &customersList);
    void act(Studio &studio);
    std::string toString() const;

	// added
	static BaseAction* actionFromCommand(std::istringstream &commandStream, Studio &ref_studio);
    virtual BaseAction* duplicate();

    // rule of 5
    virtual ~OpenTrainer();// destructor
    OpenTrainer(const OpenTrainer &ref_otherOpenTrainer);// copy constructor
    OpenTrainer(const OpenTrainer &&ref_otherOpenTrainer);// move constructor
    // OpenTrainer& operator=(const OpenTrainer &ref_otherOpenTrainer);// copy assignment
    // OpenTrainer& operator=(const OpenTrainer &&ref_otherOpenTrainer);// move assignment
private:
	const int trainerId;
	std::vector<Customer *> customers;
    
	// added
	// static const std::string strategies[];
    string rebuiltCommandStr;
    static ostringstream oss;

    // OpenTrainer& performCopy(const OpenTrainer &ref_otherOpenTrainer);
    // void copyHeaders(const OpenTrainer &ref_source, OpenTrainer &ref_destionation);
    void copyCustomers(const OpenTrainer &ref_source, OpenTrainer &ref_destination);

    void deleteCustomers();
};


class Order : public BaseAction {
public:
    Order(int id);
    void act(Studio &studio);
    std::string toString() const;

	// added
	static BaseAction* actionFromCommand(std::istringstream &commandStream, Studio &ref_studio);
    virtual BaseAction* duplicate();
private:
    const int trainerId;
};


class MoveCustomer : public BaseAction {
public:
    MoveCustomer(int src, int dst, int customerId);
    void act(Studio &studio);
    std::string toString() const;

	// added
	static BaseAction* actionFromCommand(std::istringstream &commandStream, Studio &ref_studio);
    virtual BaseAction* duplicate();
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
	static BaseAction* actionFromCommand(std::istringstream &commandStream, Studio &ref_studio);
    virtual BaseAction* duplicate();
private:
    const int trainerId;
};


class CloseAll : public BaseAction {
public:
    CloseAll();
    void act(Studio &studio);
    std::string toString() const;

	// added
	static BaseAction* actionFromCommand(std::istringstream &commandStream, Studio &ref_studio);
    virtual BaseAction* duplicate();
private:
};


class PrintWorkoutOptions : public BaseAction {
public:
    PrintWorkoutOptions();
    void act(Studio &studio);
    std::string toString() const;

	// added
	static BaseAction* actionFromCommand(std::istringstream &commandStream, Studio &ref_studio);
    virtual BaseAction* duplicate();
private:
};


class PrintTrainerStatus : public BaseAction {
public:
    PrintTrainerStatus(int id);
    void act(Studio &studio);
    std::string toString() const;

	// added
	static BaseAction* actionFromCommand(std::istringstream &commandStream, Studio &ref_studio);
    virtual BaseAction* duplicate();
private:
    const int trainerId;
};


class PrintActionsLog : public BaseAction {
public:
    PrintActionsLog();
    void act(Studio &studio);
    std::string toString() const;

	// added
	static BaseAction* actionFromCommand(std::istringstream &commandStream, Studio &ref_studio);
    virtual BaseAction* duplicate();
private:
};


class BackupStudio : public BaseAction {
public:
    BackupStudio();
    void act(Studio &studio);
    std::string toString() const;

	// added
	static BaseAction* actionFromCommand(std::istringstream &commandStream, Studio &ref_studio);
    virtual BaseAction* duplicate();
private:
};


class RestoreStudio : public BaseAction {
public:
    RestoreStudio();
    void act(Studio &studio);
    std::string toString() const;
    
	// added
	static BaseAction* actionFromCommand(std::istringstream &commandStream, Studio &ref_studio);
    virtual BaseAction* duplicate();

};
#endif
