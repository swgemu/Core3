/*
 * VillageHolocronMenuComponent.cpp
 *
 *  Created on: 01/23/2012
 *      Author: xyborn
 */

#include "VillageHolocronMenuComponent.h"

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/player/PlayerObject.h"

#include "server/zone/ZoneServer.h"
#include "server/zone/managers/player/PlayerManager.h"

int VillageHolocronMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* creature, byte selectedID) {
	if (selectedID != 20)
		return 0;

	if (!sceneObject->isASubChildOf(creature))
		return 0;

	ManagedReference<PlayerObject*> playerObject = creature->getPlayerObject();

	if (playerObject != NULL && playerObject->isJedi() && !creature->checkCooldownRecovery("used_holocron")) {
		if (playerObject->getForcePower() == playerObject->getForcePowerMax()) {
			creature->sendSystemMessage("@jedi_spam:holocron_force_replenish"); //The holocrom hums softly as you feel your Force power replenish.

			playerObject->setForcePower(playerObject->getForcePowerMax(), true);

			creature->addCooldown("used_holocron", 24 * 3600000); //24 hours.
			sceneObject->destroyObjectFromWorld(true);
		} else {
			creature->sendSystemMessage("@jedi_spam:holocron_force_max"); //You are already at your maximum Force power.
		}
	} else {
		creature->sendSystemMessage("@jedi_spam:holocron_no_effect"); //The holocron hums briefly, but otherwise does nothing.
	}

	return 0;
}

