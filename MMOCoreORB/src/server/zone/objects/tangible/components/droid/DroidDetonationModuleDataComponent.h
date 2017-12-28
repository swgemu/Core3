/*
 * 				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef DROIDDETONATIONMODULEDATACOMPONENT_H_
#define DROIDDETONATIONMODULEDATACOMPONENT_H_

#include "BaseDroidModuleComponent.h"
#include "server/zone/objects/creature/ai/DroidObject.h"
#include "system/lang/String.h"
#include "system/platform.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
class CreatureObject;
namespace ai {
class DroidObject;
}  // namespace ai
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

class DroidDetonationModuleDataComponent : public BaseDroidModuleComponent {

protected:
	bool initialized;
	int rating;
	int moduleCount;
	bool started;
	bool mseDroid;
	bool advanced;
public:
	DroidDetonationModuleDataComponent();

	~DroidDetonationModuleDataComponent();

	String getModuleName();

	void initializeTransientMembers();

	void fillAttributeList(AttributeListMessage* msg, CreatureObject* droid);

	void fillObjectMenuResponse(SceneObject* droidObject, ObjectMenuResponse* menuResponse, CreatureObject* player);

	int handleObjectMenuSelect(CreatureObject* player, byte selectedID, PetControlDevice* controller);

	virtual int getBatteryDrain() { return 0; }

	void deactivate();

	String toString();

	void onCall();

	void onStore();

	virtual bool isStackable() { return true; }

	virtual void addToStack(BaseDroidModuleComponent* other);

	virtual void copy(BaseDroidModuleComponent* other);

	// method for init process
	void updateCraftingValues(CraftingValues* values, bool firstUpdate);

	int calculateDamage(DroidObject* droid);

	bool readyForDetonation() { return initialized; }

	void setReadyForDetonation() { initialized = true;}

	bool countdownInProgress() { return started; }

	void startCountDown() { started = true;}

	void stopCountDown() { started = false;}

	void setSpecies(int i);

	void initialize(DroidObject* droid);
};

} // droid
} // components
} // tangible
} // objects
} // zone
} // server
using namespace server::zone::objects::tangible::components::droid;

#endif /* DROIDDETONATIONMODULEDATACOMPONENT_H_ */
