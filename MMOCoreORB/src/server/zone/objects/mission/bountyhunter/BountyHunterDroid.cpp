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
#include "server/zone/managers/planet/PlanetManager.h"

Reference<Task*> BountyHunterDroid::performAction(int action, SceneObject* droidObject, CreatureObject* player, MissionObject* mission) {
	if (droidObject == NULL || player == NULL || mission == NULL) {
		player->sendSystemMessage("@mission/mission_generic:bounty_no_ability");
		return NULL;
	}

	Reference<Task*> task = NULL;

	Locker playerLock(player);

	switch (action) {
	case CALLDROID:
		task = callArakydDroid(droidObject, player, mission);
		break;
	case TRANSMITBIOLOGICALSIGNATURE:
		task = transmitBiologicalSignature(droidObject, player, mission);
		break;
	case FINDTARGET:
		task = findTarget(droidObject, player, mission, false);
		break;
	case FINDANDTRACKTARGET:
		task = findTarget(droidObject, player, mission, true);
		break;
	default:
		player->sendSystemMessage("@mission/mission_generic:bounty_no_ability");
		break;
	}

	return task;
}

Reference<FindTargetTask*> BountyHunterDroid::findTarget(SceneObject* droidObject, CreatureObject* player, MissionObject* mission, bool track) {
	if (mission->getMissionLevel() < 2 ||
			(mission->getMissionLevel() < 3 && track)) {
		player->sendSystemMessage("@mission/mission_generic:bounty_no_ability");
		return NULL;
	}

	ManagedReference<BountyMissionObjective*> objective = cast<BountyMissionObjective*>(mission->getMissionObjective());

	if (objective == NULL || objective->getObjectiveStatus() == BountyMissionObjective::INITSTATUS) {
		player->sendSystemMessage("@mission/mission_generic:bounty_no_signature");
		return NULL;
	}

	if (player->isRidingCreature() || player->isRidingMount()) {
		player->sendSystemMessage("@error_message:survey_on_mount");
		return NULL;
	}

	ManagedReference<CreatureObject*> droid = player->getZone()->getCreatureManager()->spawnCreature(String("seeker").hashCode(), 0, player->getPositionX(), player->getPositionZ(), player->getPositionY(), 0);

	Reference<FindTargetTask*> findTargetTask = new FindTargetTask(droid, player, objective, track, false);
	findTargetTask->schedule(2000);

	Locker locker(droidObject);

	TangibleObject* tano = cast<TangibleObject*>(droidObject);
	if(tano != NULL){
		tano->setUseCount(tano->getUseCount() - 1, true);
	} else {
		droidObject->destroyObjectFromWorld(true);
	}

	return findTargetTask;
}

Reference<CallArakydTask*> BountyHunterDroid::callArakydDroid(SceneObject* droidObject, CreatureObject* player, MissionObject* mission) {
	if (mission->getMissionLevel() < 3) {
		player->sendSystemMessage("@mission/mission_generic:bounty_no_ability");
		return NULL;
	}

	if (mission->getMissionObjective() == NULL) {
		player->sendSystemMessage("@mission/mission_generic:bounty_no_mission");
		return NULL;
	}

	ManagedReference<BountyMissionObjective*> objective = cast<BountyMissionObjective*>(mission->getMissionObjective());

	if (objective->getArakydDroid() != NULL) {
		player->sendSystemMessage("@mission/mission_generic:probe_droid_too_many");
		return NULL;
	}

	Vector<ManagedReference<ActiveArea*> >* areas = player->getActiveAreas();
	for (int i = 0; i < areas->size(); i++) {
		if (areas->get(i)->isMunicipalZone()) {
			player->sendSystemMessage("@mission/mission_generic:probe_droid_bad_location");
			return NULL;
		}
	}

	if (player->isRidingCreature() || player->isRidingMount()) {
		player->sendSystemMessage("@error_message:survey_on_mount");
		return NULL;
	}

	Reference<CallArakydTask*> task = new CallArakydTask(player, cast<BountyMissionObjective*>(mission->getMissionObjective()));

	Core::getTaskManager()->executeTask(task);

	//Temporary set the arakyd droid to the player object. The call task will overwrite it with correct value.
	//This is needed to prevent the player from launching more than one droid at a time.
	objective->setArakydDroid(player);

	Locker locker(droidObject);

	TangibleObject* tano = cast<TangibleObject*>(droidObject);

	if(tano != NULL){
		tano->setUseCount(tano->getUseCount() - 1, true);
	} else {
		droidObject->destroyObjectFromWorld(true);
	}

	return task;
}

Reference<FindTargetTask*> BountyHunterDroid::transmitBiologicalSignature(SceneObject* droidObject, CreatureObject* player, MissionObject* mission) {
	if (mission->getMissionLevel() < 3) {
		player->sendSystemMessage("@mission/mission_generic:bounty_no_ability");
		return NULL;
	}

	ManagedReference<BountyMissionObjective*> objective = cast<BountyMissionObjective*>(mission->getMissionObjective());

	if (objective == NULL || objective->getObjectiveStatus() == BountyMissionObjective::INITSTATUS) {
		player->sendSystemMessage("@mission/mission_generic:bounty_no_signature");
		return NULL;
	}

	if (player->isRidingCreature() || player->isRidingMount()) {
		player->sendSystemMessage("@error_message:survey_on_mount");
		return NULL;
	}

	Reference<FindTargetTask*> findTargetTask = new FindTargetTask(cast<CreatureObject*>(droidObject), player, objective, false, true);
	findTargetTask->schedule(1000);

	return findTargetTask;
}
