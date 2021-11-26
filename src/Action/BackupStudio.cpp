#include "Action.h"


BackupStudio::BackupStudio () {
}


void BackupStudio::act(Studio& studio) {
	// never results in an error
	delete backup; // safe even if nullptr

	backup = new Studio(studio);
	
	complete();
}


std::string BackupStudio::toString() const {
	return "backup Completed";
}


BaseAction* BackupStudio::duplicate() {
	BackupStudio *ptr_newBackupAction = new BackupStudio();

	return ptr_newBackupAction;
}
