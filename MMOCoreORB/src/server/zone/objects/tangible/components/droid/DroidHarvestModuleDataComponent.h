/*
 * 				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef DROIDHARVESTMODULEDATACOMPONENT_H_
#define DROIDHARVESTMODULEDATACOMPONENT_H_

#include "BaseDroidModuleComponent.h"
#include "engine/core/ManagedReference.h"
#include "server/zone/objects/tangible/components/droid/DroidHarvestObserver.h"

namespace server {
namespace zone {
namespace objects {
namespace tangible {
namespace components {
namespace droid {


class DroidHarvestModuleDataComponent : public BaseDroidModuleComponent {

protected:
	int harvestBonus;
	int interest;
	bool active;
	ManagedReference<DroidHarvestObserver*> observer;
	Vector<uint64> harvestTargets;
public:
	enum {
		INTREST_RANDOM,
		INTREST_BONE,
		INTREST_MEAT,
		INTREST_HIDE
	};

	DroidHarvestModuleDataComponent();
	~DroidHarvestModuleDataComponent();
	String getModuleName();
	void initializeTransientMembers();
	void fillAttributeList(AttributeListMessage* msg, CreatureObject* droid);
	void fillObjectMenuResponse(SceneObject* droidObject, ObjectMenuResponse* menuResponse, CreatureObject* player);
	int handleObjectMenuSelect(CreatureObject* player, byte selectedID, PetControlDevice* controller);
	int getBatteryDrain();
	void deactivate();
	String toString();
	void onCall();
	int getHarvestInterest() { return interest; }
	void onStore();
	void setHarvestInterest(CreatureObject* player, int option);
	void updateCraftingValues(CraftingValues* values, bool firstUpdate);
	bool isActive(){ return active; }
	int getHarvestPower(){ return harvestBonus; }
	void handlePetCommand(String cmd, CreatureObject* speaker) ;
	virtual bool isStackable() { return true; }
	virtual void addToStack(BaseDroidModuleComponent* other);
	virtual void copy(BaseDroidModuleComponent* other);
	void creatureHarvestCheck(CreatureObject* target);
	void harvestDestinationReached();
	bool hasMoreTargets() { return harvestTargets.size() > 0; }
	void addHarvestTarget(uint64 target,bool first = false) {
		if (first)
			harvestTargets.add(0,target);
		else
			harvestTargets.add(target);
	}
	uint64 getNextHarvestTarget() {if (harvestTargets.size() > 0) {return harvestTargets.remove(0);} else { return -1;}}
};


} // droid
} // components
} // tangible
} // objects
} // zone
} // server
using namespace server::zone::objects::tangible::components::droid;
#endif /* DROIDHARVESTMODULEDATACOMPONENT_H_ */
