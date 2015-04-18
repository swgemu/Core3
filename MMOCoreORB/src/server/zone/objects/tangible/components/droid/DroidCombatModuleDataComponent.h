/*
 * 				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef DROIDCOMBATMODULEDATACOMPONENT_H_
#define DROIDCOMBATMODULEDATACOMPONENT_H_

#include "BaseDroidModuleComponent.h"
#include "engine/core/ManagedReference.h"

namespace server {
namespace zone {
namespace objects {
namespace tangible {
namespace components {
namespace droid {


class DroidCombatModuleDataComponent : public BaseDroidModuleComponent {

protected:
	int rating;

public:
	DroidCombatModuleDataComponent();
	~DroidCombatModuleDataComponent();
	String getModuleName();
	void initializeTransientMembers();
	void fillAttributeList(AttributeListMessage* msg, CreatureObject* droid);
	int getBatteryDrain() { return 0;}
	String toString();
	bool isStackable() { return true; }
	void copy(BaseDroidModuleComponent* other);
	void addToStack(BaseDroidModuleComponent* other);
	void updateCraftingValues(CraftingValues* values, bool firstUpdate);
	void initialize(CreatureObject* droid);
	bool isCombatModule() { return true; }
};


} // droid
} // components
} // tangible
} // objects
} // zone
} // server
using namespace server::zone::objects::tangible::components::droid;
#endif /* DROIDCOMBATMODULEDATACOMPONENT_H_ */
