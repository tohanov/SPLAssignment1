#include "Action.h"

// TODO: complete implementation

BackupStudio::BackupStudio () {

}


void BackupStudio::act(Studio& studio) {
	// never results in an error
	delete backup; // safe even if nullptr

	backup = new Studio(studio);
	
	complete();
}


std::string BackupStudio::toString() const {
	return "backup";
}
