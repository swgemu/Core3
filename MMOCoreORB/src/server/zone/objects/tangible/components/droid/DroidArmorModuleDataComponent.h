/*
 * 				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef DROIDARMORMODULEDATACOMPONENT_H_
#define DROIDARMORMODULEDATACOMPONENT_H_

#include "BaseDroidModuleComponent.h"
#include "system/lang/String.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
class CreatureObject;
namespace ai {
class DroidObject;
}  // namespace ai
}  // namespace creature
namespace manufactureschematic {
namespace craftingvalues {
class CraftingValues;
}  // namespace craftingvalues
}  // namespace manufactureschematic
}  // namespace objects
namespace packets {
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

class DroidArmorModuleDataComponent : public BaseDroidModuleComponent {

protected:
	int armorModule;

public:
	DroidArmorModuleDataComponent();

	~DroidArmorModuleDataComponent();

	String getModuleName();

	void initializeTransientMembers();

	void initialize(DroidObject* droid);

	void fillAttributeList(AttributeListMessage* msg, CreatureObject* droid);

	int getBatteryDrain();

	String toString();

    bool isStackable() { return true; }

	void updateCraftingValues(CraftingValues* values, bool firstUpdate);

	void addToStack(BaseDroidModuleComponent* other);

	void copy(BaseDroidModuleComponent* other);
};

} // droid
} // components
} // tangible
} // objects
} // zone
} // server
using namespace server::zone::objects::tangible::components::droid;

#endif /* DROIDARMORMODULEDATACOMPONENT_H_ */
