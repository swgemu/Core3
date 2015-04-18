/*
 * 				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef DROIDDATASTORAGEMODULEDATACOMPONENT_H_
#define DROIDDATASTORAGEMODULEDATACOMPONENT_H_

#include "BaseDroidModuleComponent.h"
#include "engine/core/ManagedReference.h"

namespace server {
namespace zone {
namespace objects {
namespace tangible {
namespace components {
namespace droid {


class DroidDataStorageModuleDataComponent : public BaseDroidModuleComponent {

protected:
	int rating;

public:
	DroidDataStorageModuleDataComponent();
	~DroidDataStorageModuleDataComponent();
	String getModuleName();
	void initializeTransientMembers();
	void fillAttributeList(AttributeListMessage* msg, CreatureObject* droid);
	int getBatteryDrain() { return 0;}
	String toString();
	// crafting droid module specific
	void onCall();
	void onStore();
	bool isStackable() { return true; }
	void copy(BaseDroidModuleComponent* other);
	void addToStack(BaseDroidModuleComponent* other);
	void updateCraftingValues(CraftingValues* values, bool firstUpdate);
	int getStorageRating();
	void fillObjectMenuResponse(SceneObject* droidObject, ObjectMenuResponse* menuResponse, CreatureObject* player);
	int handleObjectMenuSelect(CreatureObject* player, byte selectedID, PetControlDevice* controller);
	void initialize(CreatureObject* droid);
};


} // droid
} // components
} // tangible
} // objects
} // zone
} // server
using namespace server::zone::objects::tangible::components::droid;
#endif /* DROIDDATASTORAGEMODULEDATACOMPONENT_H_ */
