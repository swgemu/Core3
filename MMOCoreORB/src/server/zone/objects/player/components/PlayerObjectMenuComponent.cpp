/*
 				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#include "PlayerObjectMenuComponent.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/group/GroupObject.h"
#include "server/zone/managers/player/PlayerManager.h"

void PlayerObjectMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) const {
	if (!sceneObject->isCreatureObject())
		return;

	CreatureObject* creature = cast<CreatureObject*>(sceneObject);
	GroupObject* group = creature->getGroup();
	PlayerObject* ghost = player->getPlayerObject();
	PlayerObject* targetGhost = creature->getPlayerObject();

	if (group != nullptr) {
		if (group->hasMember(player))
			menuResponse->addRadialMenuItem(51, 3, "@sui:teach");
	}

	uint64 listenID = player->getListenID();

	if (player->isListening()) {
		// Stop Listening radial if the target is the current listen target, or if the target is in the same group as the listen target
		if (listenID == creature->getObjectID() || (group != nullptr && group->hasMember(listenID)))
			menuResponse->addRadialMenuItem(115, 3, "@radial_performance:listen_stop");
	} else {
		// Listen radial if the target is playing music, and if either there is no current listen target or the current target is in a different group than the listen target
		if (creature->isPlayingMusic() && (listenID == 0 || !group->hasMember(listenID)))
			menuResponse->addRadialMenuItem(113, 3, "@radial_performance:listen");
	}

	uint64 watchID = player->getWatchToID();

	if (watchID == creature->getObjectID()) {
		menuResponse->addRadialMenuItem(116, 3, "@radial_performance:watch_stop");
	} else if (creature->isDancing()) {
		menuResponse->addRadialMenuItem(114, 3, "@radial_performance:watch");
	}

	// Allow admins to grant divorce to married players
	if (targetGhost != nullptr && targetGhost->isMarried() && ghost != nullptr && ghost->isPrivileged()) {
		menuResponse->addRadialMenuItem(117, 3, "@unity:mnu_divorce"); // "Divorce"
	}
}

int PlayerObjectMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) const {
	ManagedReference<CreatureObject*> ownerPlayer = dynamic_cast<CreatureObject*> (sceneObject);
	PlayerObject* ghost = player->getPlayerObject();

	switch (selectedID) {
	case 113:
		player->executeObjectControllerAction(0x5855BB1B, sceneObject->getObjectID(), ""); // listen
		break;
	case 115:
		player->executeObjectControllerAction(0xC2E4D4D0, sceneObject->getObjectID(), ""); // stoplistening
		break;
	case 114:
		player->executeObjectControllerAction(0xEC93CA43, sceneObject->getObjectID(), ""); // watch
		break;
	case 116:
		player->executeObjectControllerAction(0x6651AD9A, sceneObject->getObjectID(), ""); // stopwatching
		break;
	case 51:
		player->executeObjectControllerAction(0x5041F83A, sceneObject->getObjectID(), ""); // teach
		break;
	case 117:
		if (ghost != nullptr && ghost->isPrivileged()) {
			PlayerManager* playerManager = player->getZoneServer()->getPlayerManager();

			Core::getTaskManager()->executeTask([=] () {
				Locker locker(ownerPlayer);

				playerManager->grantDivorce(ownerPlayer);
			}, "GrantDivorceLambda");
		}
		break;
	}

	return 0;
}
