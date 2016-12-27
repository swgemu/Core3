/*
 * 				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef DROIDREPAIRMODULEDATACOMPONENT_H_
#define DROIDREPAIRMODULEDATACOMPONENT_H_

#include "BaseDroidModuleComponent.h"

namespace server {
namespace zone {
namespace objects {
namespace tangible {
namespace components {
namespace droid {


class DroidRepairModuleDataComponent : public BaseDroidModuleComponent {

protected:

public:
	DroidRepairModuleDataComponent();
	~DroidRepairModuleDataComponent();
	String getModuleName();
	void initializeTransientMembers();
	void fillAttributeList(AttributeListMessage* msg, CreatureObject* droid);
	void fillObjectMenuResponse(SceneObject* droidObject, ObjectMenuResponse* menuResponse, CreatureObject* player);
	int handleObjectMenuSelect(CreatureObject* player, byte selectedID, PetControlDevice* controller);
	void handlePetCommand(String cmd, CreatureObject* speaker) ;
	int getBatteryDrain();
	String toString();

	/**
	 * There is no added benefit to having multiple repair modules installed.
	 * We want to collapse all repair modules down to one to avoid multiple modules
	 * adding radial selections, handling commands, etc
	 * copy() and addToStack() NO OPS from the base class (no stats to copy/add)
	 */
	bool isStackable() { return true; }
};


} // droid
} // components
} // tangible
} // objects
} // zone
} // server
using namespace server::zone::objects::tangible::components::droid;
#endif /* DROIDREPAIRMODULEDATACOMPONENT_H_ */
