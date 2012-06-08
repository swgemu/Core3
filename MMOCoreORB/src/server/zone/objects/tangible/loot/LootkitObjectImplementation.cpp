/*
 * LootkitObjectImplementation.cpp
 *
 *  Created on: Apr 12, 2010
 *      Author: swgemu
 */

#include "LootkitObject.h"
#include "../TangibleObject.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/packets/scene/AttributeListMessage.h"
#include "server/zone/objects/scene/variables/CustomizationVariables.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/ZoneProcessServer.h"
#include "server/zone/templates/tangible/LootkitObjectTemplate.h"

void LootkitObjectImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* object) {
	TangibleObjectImplementation::fillAttributeList(alm,object);

	String boolean[] = {"No","Yes"};

	StringBuffer componentAttributes;
	for (int i=0; i<attributes.size();++i) {
		componentAttributes << boolean[components.get(comps.get(i))];
		alm->insertAttribute(attributes.get(comps.get(i)), componentAttributes);
		componentAttributes.deleteAll();
	}
}

void LootkitObjectImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	TangibleObjectImplementation::loadTemplateData(templateData);

	LootkitObjectTemplate* LootkitData = dynamic_cast<LootkitObjectTemplate*>(templateData);

	components = LootkitData->getComponents();
	attributes = LootkitData->getAttributes();

	comps = LootkitData->getComps();
	reward = LootkitData->getReward();

	deleteComponents = LootkitData->getDeleteComponents();
}

ManagedWeakReference<CreatureObject*> LootkitObjectImplementation::getPlayer() {
	return cast<CreatureObject*>(getParentRecursively(SceneObjectType::PLAYERCREATURE).get().get());
}

int LootkitObjectImplementation::notifyObjectInserted(SceneObject* object) {
	addToKit(object);
	return 0;
}

void LootkitObjectImplementation::addToKit(SceneObject* object) {
	uint32 crc = object->getServerObjectCRC();
	if (components.contains(crc)) {

		if (hasObjectInContainer(object->getObjectID())) {

			if (deleteComponents) {

				if (getPlayer().get() == NULL)
					return;

				getPlayer().get()->sendSystemMessage("@loot_kit:item_used");

				ManagedReference<SceneObject*> inventory = getPlayer().get()->getSlottedObject("inventory");
				Locker locker(object);
				Locker iLocker(inventory);
				//removeObject(object, true);
				object->destroyObjectFromWorld(true);

				if (object->isPersistent())
					object->destroyObjectFromDatabase(true);
			}

			components.drop(crc);
			components.put(crc,true);

			createItem();
		}
	}
}

void LootkitObjectImplementation::createItem() {
	for (int i = 1; i<comps.size(); ++i) {
		if (components.get(comps.get(i)) == 0) {
			return; // Still missing pieces
		}
	}
	ManagedReference<CreatureObject*> player = getPlayer().get();
	if (player != NULL) {

		getPlayer().get()->sendSystemMessage("@loot_kit:new_item_created");

		ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");
		ZoneServer* zoneServer = server->getZoneServer();

		ManagedReference<SceneObject*> rewardObject = zoneServer->createObject(reward.get(System::random(reward.size()-1)), 2);

		Locker clocker(inventory, player);
		rewardObject->sendTo(player, true);
		if (inventory->transferObject(rewardObject, -1, true)) {
			//getParent()->removeObject(_this, true);
			destroyObjectFromWorld(true);

			if (isPersistent())
				destroyObjectFromDatabase(true);
		}
	}
}

int LootkitObjectImplementation::canAddObject(SceneObject* object, int containmentType, String& errorDescription) {
	if (components.contains(object->getServerObjectCRC())) {

		if (!components.get(object->getServerObjectCRC()) && getPlayer().get() != NULL) {
			ManagedReference<SceneObject*> inventory = getPlayer().get()->getSlottedObject("inventory");

			if (inventory->hasFullContainerObjects()) {
				errorDescription = "@error_message:inv_full";
				return 5;
			}

			return TangibleObjectImplementation::canAddObject(object, containmentType, errorDescription);

		} else {

			if (getPlayer().get() != NULL) {
				errorDescription = "@loot_kit:already_contains";
			}

			return 5;
		}
	}

	if (getPlayer().get() != NULL) {
		errorDescription = "@loot_kit:incorrect_item";
	}

	return 5;
}
