/*
 * 				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef DROIDITEMSTORAGEMODULEDATACOMPONENT_H_
#define DROIDITEMSTORAGEMODULEDATACOMPONENT_H_

#include "BaseDroidModuleComponent.h"
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

class DroidItemStorageModuleDataComponent : public BaseDroidModuleComponent {

protected:
	int rating;

public:
	DroidItemStorageModuleDataComponent();

	~DroidItemStorageModuleDataComponent();

	String getModuleName();

	void initializeTransientMembers();

	void fillAttributeList(AttributeListMessage* msg, CreatureObject* droid);

	int getBatteryDrain() { return 0;}

	String toString();

	void onCall();

	void onStore();

	bool isStackable() { return true; }

	void copy(BaseDroidModuleComponent* other);

	void addToStack(BaseDroidModuleComponent* other);

	void updateCraftingValues(CraftingValues* values, bool firstUpdate);

	int getStorageRating();

	void fillObjectMenuResponse(SceneObject* droidObject, ObjectMenuResponse* menuResponse, CreatureObject* player);

	int handleObjectMenuSelect(CreatureObject* player, byte selectedID, PetControlDevice* controller);

	void initialize(DroidObject* droid);
};

} // droid
} // components
} // tangible
} // objects
} // zone
} // server
using namespace server::zone::objects::tangible::components::droid;

#endif /* DROIDITEMSTORAGEMODULEDATACOMPONENT_H_ */
