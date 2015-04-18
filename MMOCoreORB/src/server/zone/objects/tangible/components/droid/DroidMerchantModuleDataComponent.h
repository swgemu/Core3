/*
 * 				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef DROIDMERCHANTODULEDATACOMPONENT_H_
#define DROIDMERCHANTODULEDATACOMPONENT_H_

#include "BaseDroidModuleComponent.h"
#include "engine/core/ManagedReference.h"
#include "server/zone/objects/waypoint/WaypointObject.h"
namespace server {
namespace zone {
namespace objects {
namespace tangible {
namespace components {
namespace droid {


class DroidMerchantModuleDataComponent : public BaseDroidModuleComponent {

protected:
	String message;
	bool active;
	bool waitingOnMessage;
	ManagedReference<WaypointObject*> waypoint;

public:
	DroidMerchantModuleDataComponent();
	~DroidMerchantModuleDataComponent();
	String getModuleName();
	void setWaypoint(ManagedReference<WaypointObject*> wp);
	void initializeTransientMembers();
	void fillAttributeList(AttributeListMessage* msg, CreatureObject* droid);
	void fillObjectMenuResponse(SceneObject* droidObject, ObjectMenuResponse* menuResponse, CreatureObject* player);
	int handleObjectMenuSelect(CreatureObject* player, byte selectedID, PetControlDevice* controller);
	void handlePetCommand(String cmd, CreatureObject* speaker) ;
	int getBatteryDrain();
	String toString();
	String getMessage() { return message; }
	bool isActive(){ return active; }
	void onCall();
	void deactivate();
	void onStore();
	bool isStackable() { return false; }
};


} // droid
} // components
} // tangible
} // objects
} // zone
} // server
using namespace server::zone::objects::tangible::components::droid;
#endif /* DROIDMERCHANTODULEDATACOMPONENT_H_ */
