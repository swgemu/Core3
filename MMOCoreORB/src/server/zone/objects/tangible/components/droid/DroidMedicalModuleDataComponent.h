/*
 * 				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef DROIDMEDICALGMODULEDATACOMPONENT_H_
#define DROIDMEDICALGMODULEDATACOMPONENT_H_

#include "BaseDroidModuleComponent.h"
#include "system/lang/String.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
class CreatureObject;
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

class DroidMedicalModuleDataComponent : public BaseDroidModuleComponent {

protected:
	int rating;

public:
	DroidMedicalModuleDataComponent();
	~DroidMedicalModuleDataComponent();
	String getModuleName();
	void initializeTransientMembers();
	void fillAttributeList(AttributeListMessage* msg, CreatureObject* droid);
	void loadSkillMods(CreatureObject* player);
	void unloadSkillMods(CreatureObject* player);
	bool skillsByRange() { return true;}
	int getBatteryDrain() { return 0;}
	String toString();
	// crafting droid module specific
	void onCall();
	void onStore();
	bool isStackable() { return true; }
	void copy(BaseDroidModuleComponent* other);
	void addToStack(BaseDroidModuleComponent* other);
	void updateCraftingValues(CraftingValues* values, bool firstUpdate);
	int getMedicalRating();
};

} // droid
} // components
} // tangible
} // objects
} // zone
} // server
using namespace server::zone::objects::tangible::components::droid;

#endif /* DROIDMEDICALGMODULEDATACOMPONENT_H_ */
