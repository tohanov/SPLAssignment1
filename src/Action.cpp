#include <sstream>      // for std::istringstream
//#include <functional>
#include <string>
#include <unordered_map>
#include "Action.h"
#include "Studio.h"


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


#include "Action/actionFromCommand.cpp"
