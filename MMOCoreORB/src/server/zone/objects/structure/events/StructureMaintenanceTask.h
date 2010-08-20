/*
 * StructureMaintenanceTask.h
 *
 *  Created on: Aug 19, 2010
 *      Author: crush
 */

#ifndef STRUCTUREMAINTENANCETASK_H_
#define STRUCTUREMAINTENANCETASK_H_

#include "../StructureObject.h"

namespace server {
namespace zone {
namespace objects {
namespace structure {
namespace events {

class StructureMaintenanceTask : public Task, public Logger {
protected:
	WeakReference<StructureObject*> structureObject;

public:
	StructureMaintenanceTask(StructureObject* structure) : Task(), Logger("StructureMaintenanceTask") {
		structureObject = structure;
	}

	void run() {
		//Structure is out of maintenance. Start the decaying process...
		info("Structure is out of maintenance, starting decay process...", true);

		/*

string/en/player_structure.stf	structure_maintenance_empty_body	Your %TT %TO has an empty maintenance pool. It will start deducting from your bank account automatically.
string/en/player_structure.stf	structure_maintenance_empty_subject	Structure maintenance pool empty!
string/en/player_structure.stf	mail_structure_damage	Your %TT %TO is currently at %DI percent condition. It will be destroyed if it reaches 0. If you wish to keep this structure, you should immediately add maintenance.
string/en/player_structure.stf	mail_structure_damage_condemn	Your %TT %TO is currently at %DI percent condition. It will be condemned if it reaches 0. If you wish to keep this structure, you should immediately add maintenance.
		 */
	}

};

}
}
}
}
}

using namespace server::zone::objects::structure::events;

#endif /* STRUCTUREMAINTENANCETASK_H_ */
