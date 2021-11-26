#include <sstream>      // for std::istringstream
#include <string>
#include <unordered_map>
#include "Action.h"
#include "Studio.h"

// action source files
#include "Action/BaseAction.cpp"
#include "Action/OpenTrainer.cpp"
#include "Action/Order.cpp"
#include "Action/MoveCustomer.cpp"
#include "Action/Close.cpp"
#include "Action/CloseAll.cpp"
#include "Action/PrintWorkoutOptions.cpp"
#include "Action/PrintTrainerStatus.cpp"
#include "Action/PrintActionsLog.cpp"


extern Studio* backup;

#include "Action/BackupStudio.cpp"
#include "Action/RestoreStudio.cpp"

// command parsing auxilary static functions source file
#include "Action/actionFromCommand.cpp"