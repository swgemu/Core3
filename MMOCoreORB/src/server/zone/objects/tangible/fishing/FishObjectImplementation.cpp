/*
 * FishObjectImplementation.cpp
 *
 *  Created on: May 8, 2010
 *      Author: swgemu
 */

#include "server/zone/objects/tangible/fishing/FishObject.h"
#include "server/zone/packets/scene/AttributeListMessage.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/structure/StructureObject.h"

int FishObjectImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {
	if (selectedID == 245) {
		if (getContainerObjectsSize() > 0) {
			filet(player);
		} else {
			player->sendSystemMessage("@fishing:already_fileted");
		}
	}

	return 0;
}

void FishObjectImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, CreatureObject* player) {
	TangibleObjectImplementation::fillObjectMenuResponse(menuResponse, player);
	if (getContainerObjectsSize() > 0) {

		String text = "@fishing:mnu_filet";
          
          	SceneObject* parent = getRootParent();

		if (parent == nullptr)
			return;

		if (parent->isStructureObject())
		{
			StructureObject* house = cast<StructureObject*>(parent);

			if (house != nullptr && house->isOnAdminList(player))
			{
				menuResponse->addRadialMenuItem(245, 3, text);
			}
		}

		SceneObject* inventory = player->getSlottedObject("inventory");
		SceneObject* thisParent = getParent().get();

		if (inventory != nullptr && thisParent != nullptr && thisParent == inventory)
		{
			menuResponse->addRadialMenuItem(245, 3, text);
		}
	}
}

void FishObjectImplementation::filet(CreatureObject* player) {
	if (getContainerObjectsSize() > 0) {
		ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");

		if ((inventory->isContainerFullRecursive()) || ((inventory->getCountableObjectsRecursive() + getContainerObjectsSize()) > 80)) {
			StringIdChatParameter body("fishing","units_inventory");
			body.setDI(getContainerObjectsSize());
			player->sendSystemMessage(body);

		} else {
			ManagedReference<SceneObject*> item;

			while (getContainerObjectsSize() > 0) {
				item = getContainerObject((int)0);

				//removeObject(item, false);

				inventory->transferObject(item, -1, true);
			}

			player->sendSystemMessage("@fishing:good_filet");
		}
	}
}

void FishObjectImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* object) {
	TangibleObjectImplementation::fillAttributeList(alm,object);

	alm->insertAttribute("type", String("a ") + objectName.getStringID());
	alm->insertAttribute("length", String::format("%fm", length));
	alm->insertAttribute("planet", String("@planet_n:") + zoneName);
}
