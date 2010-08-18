/*
 * FishingPoleObjectImplementation.cpp
 *
 *  Created on: Apr 12, 2010
 *      Author: swgemu
 */

#include "FishingPoleObject.h"
#include "server/zone/objects/tangible/TangibleObject.h"
#include "server/zone/packets/scene/AttributeListMessage.h"
#include "server/zone/objects/scene/variables/CustomizationVariables.h"
#include "server/zone/objects/scene/TransferErrorCode.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/ZoneProcessServerImplementation.h"
#include "server/zone/managers/minigames/FishingManager.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerCreature.h"


void FishingPoleObjectImplementation::fillAttributeList(AttributeListMessage* alm, PlayerCreature* object) {
	TangibleObjectImplementation::fillAttributeList(alm,object);

	alm->insertAttribute("quality", String::valueOf(quality));
}


int FishingPoleObjectImplementation::canAddObject(SceneObject* object, String& errorDescription) {
	if (object->isFishingBait()) {
		return TangibleObjectImplementation::canAddObject(object, errorDescription);
	}

	errorDescription = "@fishing:bait_only";

	return TransferErrorCode::BAITONLY;
}

int FishingPoleObjectImplementation::handleObjectMenuSelect(PlayerCreature* player, byte selectedID) {
	if (selectedID == 245) {
		doFishing(player);
	}

	return 0;
}

void FishingPoleObjectImplementation::doFishing(PlayerCreature* player) {
	ManagedReference<FishingManager*> manager = server->getZoneServer()->getFishingManager();

	if (manager->getFishingState(player) != FishingManager::NOTFISHING) {
		manager->stopFishing(player, manager->getFishBoxID(player), true);
	} else {
		//manager->freeBait(player);
		player->executeObjectControllerAction(String("fish").hashCode());
	}
}

String FishingPoleObjectImplementation::getText(PlayerCreature* player) {
	ManagedReference<FishingManager*> manager = server->getZoneServer()->getFishingManager();
	String text = "@fishing:mnu_start_fishing";

	if (manager->getFishingState(player) != FishingManager::NOTFISHING) {
		text = "@fishing:mnu_stop_fishing";
	}

	return text;
}

bool FishingPoleObjectImplementation::removeObject(SceneObject* object, bool notifyClient) {
	ManagedReference<FishingManager*> manager = server->getZoneServer()->getFishingManager();
	if ((parent.get() != NULL) && (parent.get()->isPlayerCreature())) {
		ManagedReference<PlayerCreature*> player = (PlayerCreature*)parent.get();
		if ((player != NULL) && (object->isFishingBait())) {
			if (manager->getFishingState(player) != FishingManager::NOTFISHING) {
				player->sendSystemMessage("Cannot remove bait while fishing pole is in use.");

				return false;
			}

			return TangibleObjectImplementation::removeObject(object, notifyClient);
		}
	}
	return false;
}
