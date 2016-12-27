/*
 * 				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef DROIDTRAPMODULEDATACOMPONENT_H_
#define DROIDTRAPMODULEDATACOMPONENT_H_

#include "BaseDroidModuleComponent.h"

namespace server {
namespace zone {
namespace objects {
namespace tangible {
namespace components {
namespace droid {

class DroidTrapModuleDataComponent : public BaseDroidModuleComponent {

protected:
	int trapBonus;
	int modules;
	ManagedReference<TangibleObject*> trap;
public:
	static const String EMPTY_TRAP_MESSAGE;
	DroidTrapModuleDataComponent();
	~DroidTrapModuleDataComponent();
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
	void fillObjectMenuResponse(SceneObject* droidObject, ObjectMenuResponse* menuResponse, CreatureObject* player);
	int handleObjectMenuSelect(CreatureObject* player, byte selectedID, PetControlDevice* controller);
	void handleInsertTrap(CreatureObject* player, TangibleObject* trap);
	bool compatibleTrap(CreatureObject*player, uint32 type);
	void handlePetCommand(String cmd, CreatureObject* speaker) ;
	bool toBinaryStream(ObjectOutputStream* stream);
	bool parseFromBinaryStream(ObjectInputStream* stream);
	void decrementTrap();
	ManagedReference<TangibleObject*> getTrap() { return trap;}
	int getTrapBonus() { return trapBonus;}
private:
	int writeObjectMembers(ObjectOutputStream* stream);
	bool readObjectMember(ObjectInputStream* stream, const String& name);

};

} // droid
} // components
} // tangible
} // objects
} // zone
} // server
using namespace server::zone::objects::tangible::components::droid;

#endif /* DROIDTRAPMODULEDATACOMPONENT_H_ */
