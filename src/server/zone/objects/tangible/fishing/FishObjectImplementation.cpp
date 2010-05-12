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
#include "server/zone/objects/terrain/PlanetNames.h"
#include "system/util/VectorMap.h"

int FishObjectImplementation::handleObjectMenuSelect(PlayerCreature* player, byte selectedID) {
	if (selectedID == 245) {
		if (containerObjects.size() > 0) {
			filet(player);
		} else {
			player->sendSystemMessage("@fishing:already_fileted");
		}
	}

	return 0;
}

void FishObjectImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, PlayerCreature* player) {
	if (containerObjects.size() > 0) {
		String text = "@fishing:mnu_filet";

		menuResponse->addRadialMenuItem(245, 3, text);
	}
}

void FishObjectImplementation::filet(PlayerCreature* player) {
	if (containerObjects.size() > 0) {
		ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");

		if (inventory->hasFullContainerObjects()) {
			player->sendSystemMessage("@fishing:toss_trash");
			while (containerObjects.size() > 0) {
				removeObject(containerObjects.get(0), true);
			}
		} else {
			ManagedReference<SceneObject*> item;

			while (containerObjects.size() > 0) {
				item = containerObjects.get(0);

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

	String planetText = Planet::getPlanetName(planet);
	alm->insertAttribute("planet", planetText);
}
