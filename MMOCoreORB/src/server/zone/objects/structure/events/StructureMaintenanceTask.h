/*
 * StructureMaintenanceTask.h
 *
 *  Created on: Aug 19, 2010
 *      Author: crush
 */

#ifndef STRUCTUREMAINTENANCETASK_H_
#define STRUCTUREMAINTENANCETASK_H_

#include "engine/engine.h"

namespace server {
namespace zone {
namespace objects {
namespace structure {
	class StructureObject;
}
namespace creature {
	class CreatureObject;
}
}
}
}

using namespace server::zone::objects::creature;
using namespace server::zone::objects::structure;

namespace server {
namespace zone {
namespace objects {
namespace structure {
namespace events {

class StructureMaintenanceTask : public Task, public Logger {
protected:
	ManagedWeakReference<StructureObject*> structureObject;

	const static int oneDayTime = 24 * 60 * 60 * 1000;

public:
	StructureMaintenanceTask(StructureObject* structure) : Task(), Logger("StructureMaintenanceTask") {
		structureObject = structure;

		setCustomTaskQueue("slowQueue");
	}

	void run();

private:
	void sendMailMaintenanceWithdrawnFromBank(const String& creoName, StructureObject* structure);
	void sendMailDecay(const String& creoName, StructureObject* structure);
	void sendMailCondemned(const String& creoName, StructureObject* structure);

	bool shouldBuildingBeDestroyed(StructureObject* structure);
};

}
}
}
}
}

using namespace server::zone::objects::structure::events;

#endif /* STRUCTUREMAINTENANCETASK_H_ */
