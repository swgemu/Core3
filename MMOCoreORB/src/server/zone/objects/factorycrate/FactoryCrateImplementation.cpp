/*
 * FactoryCrateImplementation.cpp
 *
 *  Created on: 07/25/2010
 *      Author: Kyle
 */

#include "FactoryCrate.h"
#include "server/zone/packets/factory/FactoryCrateObjectMessage3.h"
#include "server/zone/packets/factory/FactoryCrateObjectMessage6.h"
#include "server/zone/objects/player/PlayerCreature.h"
#include "server/zone/managers/object/ObjectManager.h"
#include "server/zone/packets/scene/SceneObjectCreateMessage.h"
#include "server/zone/packets/scene/SceneObjectDestroyMessage.h"
#include "server/zone/packets/scene/SceneObjectCloseMessage.h"
#include "server/zone/packets/scene/UpdateContainmentMessage.h"

void FactoryCrateImplementation::initializeTransientMembers() {
	TangibleObjectImplementation::initializeTransientMembers();

	setLoggingName("FactoryCrate");
}

void FactoryCrateImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	TangibleObjectImplementation::loadTemplateData(templateData);

	setOptionsBitmask(0x2100);
}

void FactoryCrateImplementation::sendTo(SceneObject* player, bool doClose) {
	if (isStaticObject())
		return;


	if (getParent() == NULL)
		return;

	// Scene Create
	BaseMessage* create = new SceneObjectCreateMessage(_this);
	player->sendMessage(create);

	if (parent != NULL) {
		BaseMessage* link = new UpdateContainmentMessage(getObjectID(), getParent()->getObjectID(), 0xFFFFFFFF);
		player->sendMessage(link);
	}

	sendBaselinesTo(player);

	sendSlottedObjectsTo(player);
	sendContainerObjectsTo(player);

	if(doClose) {
		BaseMessage* msg = new SceneObjectCloseMessage(_this);
		player->sendMessage(msg);
	}

}

void FactoryCrateImplementation::sendBaselinesTo(SceneObject* player) {
	/*StringBuffer msg;
	msg << "sending cell number " << cellNumber << " baselines";
	info(msg.toString(), true);*/

	BaseMessage* fctyMsg3 = new FactoryCrateObjectMessage3(_this);
	player->sendMessage(fctyMsg3);

	BaseMessage* fctyMsg6 = new FactoryCrateObjectMessage6(_this);
	player->sendMessage(fctyMsg6);

}

void FactoryCrateImplementation::fillAttributeList(AttributeListMessage* alm, PlayerCreature* object) {

	//TangibleObjectImplementation::fillAttributeList(alm, object);

	if(prototype != NULL)
		prototype->fillAttributeList(alm, object);
}

void FactoryCrateImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, PlayerCreature* player) {
	TangibleObjectImplementation::fillObjectMenuResponse(menuResponse, player);
}

int FactoryCrateImplementation::handleObjectMenuSelect(PlayerCreature* player, byte selectedID) {

	switch (selectedID) {

	case 77:

		break;

	default:
		TangibleObjectImplementation::handleObjectMenuSelect(player, selectedID);
	}

	return 0;
}

bool FactoryCrateImplementation::extractObject() {
	ObjectManager* objectManager = ObjectManager::instance();

	TangibleObject* protoclone = (TangibleObject*) objectManager->cloneObject(prototype);

	if(protoclone != NULL) {
		parent->addObject(protoclone, -1, true);
		parent->broadcastObject(protoclone, true);

		protoclone->setOptionsBitmask(0x2100);

		setUseCount(getUseCount() - 1);
		return true;
	}
	return false;
}
