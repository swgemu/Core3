/*
 * FactoryCrateImplementation.cpp
 *
 *  Created on: 07/25/2010
 *      Author: Kyle
 */

#include "FactoryCrate.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/packets/factory/FactoryCrateObjectMessage3.h"
#include "server/zone/packets/factory/FactoryCrateObjectMessage6.h"
#include "server/zone/packets/factory/FactoryCrateObjectDeltaMessage3.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/managers/object/ObjectManager.h"
#include "server/zone/packets/scene/SceneObjectCreateMessage.h"
#include "server/zone/packets/scene/SceneObjectDestroyMessage.h"
#include "server/zone/packets/scene/SceneObjectCloseMessage.h"
#include "server/zone/packets/scene/UpdateContainmentMessage.h"
#include "server/zone/packets/scene/AttributeListMessage.h"
#include "server/zone/packets/chat/ChatSystemMessage.h"

void FactoryCrateImplementation::initializeTransientMembers() {
	TangibleObjectImplementation::initializeTransientMembers();

	setLoggingName("FactoryCrate");
}

void FactoryCrateImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	TangibleObjectImplementation::loadTemplateData(templateData);
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

void FactoryCrateImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* object) {

	alm->insertAttribute("volume", volume);

	TangibleObject* prototype = getPrototype();

	if(prototype == NULL || !prototype->isTangibleObject()) {
		object->sendSystemMessage("This crate is broken, please contact Kyle if you get this message");
		return;
	}

	if (prototype->getCraftersName() != "") {
		alm->insertAttribute("crafter", prototype->getCraftersName());
	}

	if (prototype->getSerialNumber() != "") {
		alm->insertAttribute("serial_number", prototype->getSerialNumber());
	}

	alm->insertAttribute("factory_count", getUseCount());

	alm->insertAttribute("factory_attribs", "\\#pcontrast2 --------------");

	StringBuffer type;
	type << "@" << prototype->getObjectNameStringIdFile() << ":"
			<< prototype->getObjectNameStringIdName();

	alm->insertAttribute("object_type", "@got_n:component");
	alm->insertAttribute("original_name", type);

	if(prototype != NULL)
		prototype->fillAttributeList(alm, object);
}

void FactoryCrateImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, CreatureObject* player) {
	TangibleObjectImplementation::fillObjectMenuResponse(menuResponse, player);
}

int FactoryCrateImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {

	switch (selectedID) {

	case 77:

		break;

	default:
		TangibleObjectImplementation::handleObjectMenuSelect(player, selectedID);
	}

	return 0;
}

TangibleObject* FactoryCrateImplementation::getPrototype() {

	if(getContainerObjectsSize() == 0) {
		error("FactoryCrateImplementation::getPrototype there isn't an object in the container");
		return NULL;
	}

	TangibleObject* prototype = cast<TangibleObject*>( getContainerObject(0));

	if(prototype == NULL || !prototype->isTangibleObject()) {
		error("FactoryCrateImplementation::getPrototype has a NULL or non-tangible item");
		return NULL;
	}
	return prototype;
}

String FactoryCrateImplementation::getCraftersName() {

	TangibleObject* prototype = getPrototype();

	if(prototype == NULL || !prototype->isTangibleObject()) {
		error("FactoryCrateImplementation::getCraftersName has a NULL or non-tangible item");
		return "";
	}

	return prototype->getCraftersName();
}

String FactoryCrateImplementation::getCraftersSerial() {

	TangibleObject* prototype = getPrototype();

	if(prototype == NULL || !prototype->isTangibleObject()) {
		error("FactoryCrateImplementation::getCraftersSerial has a NULL or non-tangible item");
		return "";
	}

	return prototype->getSerialNumber();
}

bool FactoryCrateImplementation::extractObjectToParent() {

	TangibleObject* prototype = getPrototype();

	if (prototype == NULL || !prototype->isTangibleObject() || parent == NULL) {
		error("FactoryCrateImplementation::extractObject has a NULL or non-tangible item");
		return false;
	}

	ObjectManager* objectManager = ObjectManager::instance();

	ManagedReference<TangibleObject*> protoclone = cast<TangibleObject*>( objectManager->cloneObject(prototype));

	if (protoclone != NULL) {
		protoclone->setParent(NULL);

		String errorDescription;
		int errorNumber = 0;

		if ((errorNumber = getParent()->canAddObject(protoclone, -1, errorDescription)) != 0) {
			if (errorDescription.length() > 1) {
				ManagedReference<SceneObject*> player = getParent()->getParentRecursively(SceneObjectType::PLAYERCREATURE);

				if (player != NULL)
					player->sendMessage(new ChatSystemMessage(errorDescription));
			} else
				getParent()->error("cannot extratObjectToParent " + String::valueOf(errorNumber));

			return false;
		}

		if (parent != NULL) {
			getParent()->transferObject(protoclone, -1, true);
			getParent()->broadcastObject(protoclone, true);
		}

		setUseCount(getUseCount() - 1);

		return true;
	}

	return false;
}

TangibleObject* FactoryCrateImplementation::extractObject(int count) {

	TangibleObject* prototype = getPrototype();

	if(prototype == NULL || !prototype->isTangibleObject()) {
		error("FactoryCrateImplementation::extractObject has a NULL or non-tangible item");
		return NULL;
	}

	ObjectManager* objectManager = ObjectManager::instance();

	ManagedReference<TangibleObject*> protoclone = cast<TangibleObject*>( objectManager->cloneObject(prototype));

	if(protoclone != NULL) {
		protoclone->setParent(NULL);
		protoclone->setUseCount(count, false);

		if (parent != NULL)
			getParent()->transferObject(protoclone, -1, true);

		setUseCount(getUseCount() - count, true);

		return protoclone;
	}

	return NULL;
}

void FactoryCrateImplementation::split(int newStackSize) {

	TangibleObject* prototype = getPrototype();

	if(prototype == NULL || !prototype->isTangibleObject()) {
		error("FactoryCrateImplementation::split has a NULL or non-tangible item");
		return;
	}

	ObjectManager* objectManager = ObjectManager::instance();

	ManagedReference<TangibleObject*> protoclone = cast<TangibleObject*>( objectManager->cloneObject(prototype));

	ManagedReference<FactoryCrate*> newCrate =
			dynamic_cast<FactoryCrate*>(server->getZoneServer()->createObject(getServerObjectCRC(), 2));

	if(parent == NULL || newCrate == NULL || protoclone == NULL)
		return;

	protoclone->setParent(NULL);

	newCrate->transferObject(protoclone, -1, false);

	newCrate->setUseCount(newStackSize, false);
	setUseCount(getUseCount() - newStackSize, true);

	newCrate->setObjectName(*getObjectName());

	if (parent != NULL) {
		getParent()->transferObject(newCrate, -1, true);
		getParent()->broadcastObject(newCrate, true);
	}
}

void FactoryCrateImplementation::setUseCount(uint32 newUseCount, bool notifyClient) {
	if (useCount == newUseCount)
		return;

	useCount = newUseCount;

	if (useCount < 1) {
		destroyObjectFromWorld(true);

		destroyObjectFromDatabase(true);

		return;
	}

	if (!notifyClient)
		return;

	FactoryCrateObjectDeltaMessage3* dfcty3 = new FactoryCrateObjectDeltaMessage3(_this);
	dfcty3->setQuantity(newUseCount);
	dfcty3->close();

	broadcastMessage(dfcty3, true);
}
