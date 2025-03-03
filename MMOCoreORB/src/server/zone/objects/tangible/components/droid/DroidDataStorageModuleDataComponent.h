/*
 * 				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef DROIDDATASTORAGEMODULEDATACOMPONENT_H_
#define DROIDDATASTORAGEMODULEDATACOMPONENT_H_

#include "BaseDroidModuleComponent.h"

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

	void initialize(DroidObject* droid);

	void initializeTransientMembers();

	void fillAttributeList(AttributeListMessage* msg, CreatureObject* droid);

	void copy(BaseDroidModuleComponent* other);

	void addToStack(BaseDroidModuleComponent* other);

	void updateCraftingValues(CraftingValues* values, bool firstUpdate);

	void fillObjectMenuResponse(SceneObject* droidObject, ObjectMenuResponse* menuResponse, CreatureObject* player);

	int handleObjectMenuSelect(CreatureObject* player, byte selectedID, PetControlDevice* controller);

	String getModuleName() const;

	int getStorageRating();

	String toString() const;

	void onCall();

	void onStore();

	int getRating() {
		return rating;
	}

	int getBatteryDrain() {
		return 0;
	}

	bool isStackable() {
		return true;
	}
};

} // droid
} // components
} // tangible
} // objects
} // zone
} // server
using namespace server::zone::objects::tangible::components::droid;

#endif /* DROIDDATASTORAGEMODULEDATACOMPONENT_H_ */
