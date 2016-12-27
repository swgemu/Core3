/*
 * 				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef DROIDDETONATIONMODULEDATACOMPONENT_H_
#define DROIDDETONATIONMODULEDATACOMPONENT_H_

#include "BaseDroidModuleComponent.h"
#include "server/zone/objects/creature/ai/DroidObject.h"

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
