/*
 * 				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef DROIDMAINTENANCEMODULEDATACOMPONENT_H_
#define DROIDMAINTENANCEMODULEDATACOMPONENT_H_

#include "BaseDroidModuleComponent.h"
#include "engine/core/ManagedReference.h"
#include "system/util/Vector.h"

namespace server {
namespace zone {
namespace objects {
namespace tangible {
namespace components {
namespace droid {


class DroidMaintenanceModuleDataComponent : public BaseDroidModuleComponent {

protected:

	int moduleRating;
	int maxStructures;
	Vector<unsigned long long> assignedStructures; // Object ID

public:
	DroidMaintenanceModuleDataComponent();
	~DroidMaintenanceModuleDataComponent();
	String getModuleName();
	void initializeTransientMembers();
	void fillAttributeList(AttributeListMessage* msg, CreatureObject* droid);
	void fillObjectMenuResponse(SceneObject* droidObject, ObjectMenuResponse* menuResponse, CreatureObject* player);
	int handleObjectMenuSelect(CreatureObject* player, byte selectedID, PetControlDevice* controller);
	int getBatteryDrain();
	String toString();
	void copy(BaseDroidModuleComponent* other);
	bool isStackable() { return true; }
	void addToStack(BaseDroidModuleComponent* other);
	void updateCraftingValues(CraftingValues* values, bool firstUpdate);
	void onCall();
	void inline onStore() {}
	bool toBinaryStream(ObjectOutputStream* stream);
	bool parseFromBinaryStream(ObjectInputStream* stream);
	bool assignStructure( uint64 objectID );
	void unassignStructure( uint64 objectID );
	bool isAssignedTo(uint64 structure);
	void getStructureList(Vector<ManagedReference<StructureObject* > >* list, ZoneServer* srv,uint32 planet);
	void payStructures(CreatureObject* player,VectorMap<unsigned long long, int> assignments);
	long calculateRunTime(VectorMap<unsigned long long, int> assignments);
private:
	void validateStructures();
	bool isValidStructure(uint64 objectID);
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
#endif /* DROIDMAINTENANCEMODULEDATACOMPONENT_H_ */
