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

Task* BountyHunterDroid::performAction(int action, SceneObject* droidObject, CreatureObject* player, MissionObject* mission) {
	if (droidObject == NULL || player == NULL || mission == NULL) {
		//TODO: error message.
		return NULL;
	}

	switch (action) {
	case CALLDROID:
		return callArakydDroid(droidObject, player, mission);
	case TRANSMITBIOLOGICALSIGNATURE:
		break;
	case FINDTARGET:
		return findTarget(droidObject, player, mission, false);
	case FINDANDTRACKTARGET:
		return findTarget(droidObject, player, mission, true);
	default:
		//TODO: error message.
		break;
	}

	return NULL;
}

FindTargetTask* BountyHunterDroid::findTarget(SceneObject* droidObject, CreatureObject* player, MissionObject* mission, bool track) {
	if (mission->getDifficultyLevel() < 2) {
		player->sendSystemMessage("@mission/mission_generic:bounty_no_ability");
		return NULL;
	}

	ManagedReference<BountyMissionObjective*> objective = cast<BountyMissionObjective*>(mission->getMissionObjective());

	if (objective == NULL || objective->getObjectiveStatus() == BountyMissionObjective::INITSTATUS) {
		player->sendSystemMessage("@mission/mission_generic:bounty_no_signature");
		return NULL;
	}

	ManagedReference<CreatureObject*> droid = player->getZone()->getCreatureManager()->spawnCreature(String("seeker").hashCode(), 0, player->getPositionX(), player->getPositionZ(), player->getPositionY(), 0);

	Reference<FindTargetTask*> findTargetTask = new FindTargetTask(droid, player, objective, track);
	findTargetTask->schedule(2000);

	Locker locker(droidObject);

	droidObject->destroyObjectFromWorld(true);

	return findTargetTask;
}

CallArakydTask* BountyHunterDroid::callArakydDroid(SceneObject* droidObject, CreatureObject* player, MissionObject* mission) {
	if (mission->getDifficultyLevel() < 3) {
		player->sendSystemMessage("@mission/mission_generic:bounty_no_ability");
		return NULL;
	}

	Reference<CallArakydTask*> task = new CallArakydTask(player);

	if (task != NULL && !task->isScheduled()) {
		//Schedule immediately.
		task->schedule(1);
	}

	return task;
}
