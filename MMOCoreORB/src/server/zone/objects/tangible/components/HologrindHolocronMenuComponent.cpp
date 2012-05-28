/*
 * HologrindHolocronMenuComponent.cpp
 *
 *  Created on: 01/23/2012
 *      Author: xyborn
 */

#include "HologrindHolocronMenuComponent.h"

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/player/PlayerObject.h"

#include "server/zone/ZoneServer.h"
#include "server/zone/managers/player/PlayerManager.h"

int HologrindHolocronMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* creature, byte selectedID) {
	if (selectedID != 20)
		return 0;

	ManagedReference<PlayerObject*> playerObject = creature->getPlayerObject();

	if (playerObject != NULL) {
		Vector<byte>* profs = playerObject->getHologrindProfessions();

		byte prof = 0;
		for (int i = 0; i < profs->size(); ++i) {
			prof = profs->elementAt(i);

			int badgeIdx = 42 + prof;

			if (playerObject->hasBadge(badgeIdx))
				continue;

			//Only show the first 4 profs.
			if (i < 4) {
				String stringKey = creature->getZoneServer()->getPlayerManager()->getBadgeKey(badgeIdx);

				StringIdChatParameter params("jedi_spam", "holocron_light_information");
				params.setTO("@skl_n:" + stringKey);
				creature->sendSystemMessage(params);
				sceneObject->destroyObjectFromWorld(true);

				return 0;
			} else {
				creature->sendSystemMessage("@jedi_spam:holocron_quiet"); //The Holocron is quiet. The ancients' knowledge of the Force will no longer assist you on your journey. You must continue seeking on your own.

				return 0;
			}
		}
	}

	return 0;
}

