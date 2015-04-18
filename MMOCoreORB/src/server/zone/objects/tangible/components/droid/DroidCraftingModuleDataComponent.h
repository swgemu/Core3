/*
 * 				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef DROIDCRAFTINGMODULEDATACOMPONENT_H_
#define DROIDCRAFTINGMODULEDATACOMPONENT_H_

#include "BaseDroidModuleComponent.h"
#include "server/zone/objects/tangible/tool/CraftingStation.h"
#include "engine/core/ManagedReference.h"

namespace server {
namespace zone {
namespace objects {
namespace tangible {
namespace components {
namespace droid {


class DroidCraftingModuleDataComponent : public BaseDroidModuleComponent {

protected:
	int craftingType;
	String attributeListString;
	ManagedReference<CraftingStation*> craftingStation;

public:
	DroidCraftingModuleDataComponent();
	~DroidCraftingModuleDataComponent();
	String getModuleName();
	void initializeTransientMembers();
	void initialize(CreatureObject* droid);
	void fillAttributeList(AttributeListMessage* msg, CreatureObject* droid);
	void fillObjectMenuResponse(SceneObject* droidObject, ObjectMenuResponse* menuResponse, CreatureObject* player);
	int handleObjectMenuSelect(CreatureObject* player, byte selectedID, PetControlDevice* controller);
	void loadSkillMods(CreatureObject* player);
	void unloadSkillMods(CreatureObject* player);
	bool skillsByRange();
	void handlePetCommand(String cmd, CreatureObject* speaker) ;
	int getBatteryDrain();
	void deactivate();
	bool actsAsCraftingStation();
	String toString();
	// crafting droid module specific
	CraftingStation* getCraftingStation();
	bool isWeaponDroidGeneric();
	bool isFoodChemical();
	bool isClothingArmor();
	bool isStructureFurniture();
	bool isShip();
	bool validCraftingType(int type);
	void onCall();
	void onStore();
	void copy(BaseDroidModuleComponent* other);
};


} // droid
} // components
} // tangible
} // objects
} // zone
} // server
using namespace server::zone::objects::tangible::components::droid;
#endif /* DROIDCRAFTINGMODULEDATACOMPONENT_H_ */
