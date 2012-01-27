/*
 * BountyHunterDroid.cpp
 *
 *  Created on: Jan 20, 2012
 *      Author: loshult
 */

#include "BountyHunterDroid.h"
#include "server/zone/objects/mission/BountyMissionObjective.h"
#include "server/zone/Zone.h"
#include "server/zone/managers/creature/CreatureManager.h"
#include "server/zone/packets/scene/PlayClientEventObjectMessage.h"

void BountyHunterDroid::performAction(int action, SceneObject* sceneObject, CreatureObject* player) {
	if (sceneObject != droidObject) {
		//TODO: Error message, only one droid active at a time.
		return;
	}

	if (this->player != player) {
		//TODO: Error not the player owner.
		return;
	}

	if (droidObject == NULL || player == NULL || mission == NULL) {
		//TODO: error message.
		return;
	}

	switch (action) {
	case CALLDROID:
		break;
	case TRANSMITBIOLOGICALSIGNATURE:
		break;
	case FINDTARGET:
		findTarget();
		break;
	case FINDANDTRACKTARGET:
		break;
	default:
		//TODO: error message.
		break;
	}
}

void BountyHunterDroid::findTarget() {
	if (mission->getDifficultyLevel() < 2) {
		player->sendSystemMessage("@mission/mission_generic:bounty_no_ability");
		return;
	}

	ManagedReference<BountyMissionObjective*> objective = cast<BountyMissionObjective*>(mission->getMissionObjective());

	if (objective == NULL || objective->getObjectiveStatus() == BountyMissionObjective::INITSTATUS) {
		player->sendSystemMessage("@mission/mission_generic:bounty_no_signature");
		return;
	}

	droid = player->getZone()->getCreatureManager()->spawnCreature(String("seeker").hashCode(), 0, player->getPositionX(), player->getPositionZ(), player->getPositionY(), 0);

	if (findTargetTask == NULL) {
		//TODO: calculate success and search time as a function of player abilities.
		findTargetTask = new FindTargetTask(droid, player, objective, 10, true, false);
		findTargetTask->schedule(2000);
	}

	Locker locker(droidObject);

	droidObject->destroyObjectFromWorld(true);
}
