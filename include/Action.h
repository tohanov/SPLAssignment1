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
// end added


class BaseAction{
public:
    BaseAction();
    ActionStatus getStatus() const;
    virtual void act(Studio& studio)=0;
    virtual std::string toString() const=0;

	// added
    // static function for redirection to creation of an action matching the user's command
	static BaseAction* actionFromCommand(std::istringstream &commandStream, Studio &ref_studio);
    // overriden by child classes to return a duplicate object of the correct class
    virtual BaseAction* duplicate()=0;
    virtual ~BaseAction(); // default desctructor
    // match status and errorMsg between 2 action objects
    static void matchFlags(const BaseAction *source, BaseAction *destination);
protected:
    void complete();
    void error(std::string errorMsg);
    std::string getErrorMsg() const;
	
	// added
    // get status of in string form
	string getStatusStr() const;
private:
    std::string errorMsg;
    ActionStatus status;

	// added
    // static properties to help with parsing user input
	static const std::hash<std::string> hasher;
	static const CommandHashPair hashedCommandPairs[];
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
    OpenTrainer(const OpenTrainer &ref_otherOpenTrainer); // copy constructor
    OpenTrainer(const OpenTrainer &&ref_otherOpenTrainer); // move constructor
    // OpenTrainer& operator=(const OpenTrainer &ref_otherOpenTrainer);     // copy assignment not possible due to presense of const properties
    // OpenTrainer& operator=(const OpenTrainer &&ref_otherOpenTrainer);    // move assignment not possible due to presense of const properties
private:
	const int trainerId;
	std::vector<Customer *> customers;
    
	// added
    // storing string of command for ::toString usage, without storing customer objects
    string rebuiltCommandStr;
    // static property to help with rebuilding commands
    static ostringstream oss;
    static const string commonErrorMessage;
    
    // deep copy of customers used in copy constructor
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

    // added
    static const string commonErrorMessage;
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

    // added
    static const string commonErrorMessage;
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

    // added
    static const string commonErrorMessage;
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
private:

    // added
    static const string commonErrorMessage;
};
#endif
