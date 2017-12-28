/*
 * 				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef DROIDAUTOREPAIRMODULEDATACOMPONENT_H_
#define DROIDAUTOREPAIRMODULEDATACOMPONENT_H_

#include "BaseDroidModuleComponent.h"
#include "system/lang/String.h"
#include "system/platform.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
class CreatureObject;
}  // namespace creature
namespace intangible {
class PetControlDevice;
}  // namespace intangible
namespace manufactureschematic {
namespace craftingvalues {
class CraftingValues;
}  // namespace craftingvalues
}  // namespace manufactureschematic
namespace scene {
class SceneObject;
}  // namespace scene
}  // namespace objects
namespace packets {
namespace object {
class ObjectMenuResponse;
}  // namespace object
namespace scene {
class AttributeListMessage;
}  // namespace scene
}  // namespace packets
}  // namespace zone
}  // namespace server

namespace server {
namespace zone {
namespace objects {
namespace tangible {
namespace components {
namespace droid {

class DroidAutoRepairModuleDataComponent : public BaseDroidModuleComponent {

protected:
	int autoRepairPower;
	bool active;

public:
	DroidAutoRepairModuleDataComponent();
	~DroidAutoRepairModuleDataComponent();
	String getModuleName();
	void initializeTransientMembers();
	void fillAttributeList(AttributeListMessage* msg, CreatureObject* droid);
	void fillObjectMenuResponse(SceneObject* droidObject, ObjectMenuResponse* menuResponse, CreatureObject* player);
	int handleObjectMenuSelect(CreatureObject* player, byte selectedID, PetControlDevice* controller);
	int getBatteryDrain();
	void deactivate();
	String toString();
	void onCall();
	void onStore();
	void updateCraftingValues(CraftingValues* values, bool firstUpdate);
	bool isActive(){ return active; }
	int getAutoRepairPower(){ return autoRepairPower; }
	virtual bool isStackable() { return true; }
	virtual void addToStack(BaseDroidModuleComponent* other);
	virtual void copy(BaseDroidModuleComponent* other);
};

} // droid
} // components
} // tangible
} // objects
} // zone
} // server
using namespace server::zone::objects::tangible::components::droid;

#endif /* DROIDAUTOREPAIRMODULEDATACOMPONENT_H_ */
