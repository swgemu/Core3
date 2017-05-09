/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.
*/

#include "server/zone/objects/ship/ShipObject.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/packets/ship/ShipObjectMessage1.h"
#include "server/zone/packets/ship/ShipObjectMessage3.h"
#include "server/zone/packets/ship/ShipObjectMessage4.h"
#include "server/zone/packets/ship/ShipObjectMessage6.h"
//#include "server/zone/packets/tangible/TangibleObjectMessage8.h"
//#include "server/zone/packets/tangible/TangibleObjectMessage9.h"

void ShipObjectImplementation::sendTo(SceneObject* player, bool doClose, bool forceLoadContainer) {
	//info("testing");
	TangibleObjectImplementation::sendTo(player, doClose, forceLoadContainer);
}

void ShipObjectImplementation::initializeTransientMembers() {
	TangibleObjectImplementation::initializeTransientMembers();
}

uint16 ShipObjectImplementation::getUniqueID() {
	uint32 hash = UnsignedLong::hashCode(getObjectID());
	uint16 id = (uint16) (hash ^ (hash >> 16));

	//info("uniqueId: 0x" + String::hexvalueOf(id), true);

	return id;
}

void ShipObjectImplementation::sendBaselinesTo(SceneObject* player) {
	//info("sending ship baselines", true);

	BaseMessage* ship3 = new ShipObjectMessage3(_this.getReferenceUnsafeStaticCast());
	player->sendMessage(ship3);


	//if (player->getParent().get() == _this.getReferenceUnsafeStaticCast() || getRootParent().get() == player) {
		BaseMessage* ship4 = new ShipObjectMessage4(_this.getReferenceUnsafeStaticCast());
		player->sendMessage(ship4);
	
		BaseMessage* ship1 = new ShipObjectMessage1(_this.getReferenceUnsafeStaticCast());
		player->sendMessage(ship1);
	//}

	BaseMessage* ship6 = new ShipObjectMessage6(_this.getReferenceUnsafeStaticCast());
	player->sendMessage(ship6);
/*
	BaseMessage* ship8 = new TangibleObjectMessage8(_this);
	player->sendMessage(ship8);

	BaseMessage* ship9 = new TangibleObjectMessage9(_this);
	player->sendMessage(ship9);*/
}
