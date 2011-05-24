/*
 * FishObjectImplementation.cpp
 *
 *  Created on: May 8, 2010
 *      Author: swgemu
 */

#include "FishObject.h"
#include "server/zone/objects/tangible/TangibleObject.h"
#include "server/zone/packets/scene/AttributeListMessage.h"
#include "server/zone/objects/player/PlayerCreature.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"

#include "system/util/VectorMap.h"

int FishObjectImplementation::handleObjectMenuSelect(PlayerCreature* player, byte selectedID) {
	if (selectedID == 245) {
		if (getContainerObjectsSize() > 0) {
			filet(player);
		} else {
			player->sendSystemMessage("@fishing:already_fileted");
		}
	}

	return 0;
}

void FishObjectImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, PlayerCreature* player) {
	TangibleObjectImplementation::fillObjectMenuResponse(menuResponse, player);
	if (getContainerObjectsSize() > 0) {
		String text = "@fishing:mnu_filet";

		menuResponse->addRadialMenuItem(245, 3, text);
	}
}

void FishObjectImplementation::filet(PlayerCreature* player) {
	if (getContainerObjectsSize() > 0) {
		ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");

		if ((inventory->hasFullContainerObjects()) || ((inventory->getContainerObjectsSize() + getContainerObjectsSize()) > 80)) {
			StringIdChatParameter body("fishing","units_inventory");
			body.setDI(getContainerObjectsSize());
			player->sendSystemMessage(body);

		} else {
			ManagedReference<SceneObject*> item;

			while (getContainerObjectsSize() > 0) {
				item = getContainerObject((int)0);

				removeObject(item, false);

				inventory->addObject(item, -1, true);
			}

			player->sendSystemMessage("@fishing:good_filet");
		}
	}
}

void FishObjectImplementation::fillAttributeList(AttributeListMessage* alm, PlayerCreature* object) {
	TangibleObjectImplementation::fillAttributeList(alm,object);

	String lengthText = String::valueOf(length) + "m";
	alm->insertAttribute("length", lengthText);

	//TODO: Reenable with new zone system.
	//String planetText = Planet::getPlanetName(planet);
	//alm->insertAttribute("planet", planetText);
}
