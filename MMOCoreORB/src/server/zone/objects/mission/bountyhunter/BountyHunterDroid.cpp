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
		player->sendSystemMessage("@mission/mission_generic:bounty_no_ability"); // You do not understand how to use this item.
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
		player->sendSystemMessage("@mission/mission_generic:bounty_no_ability"); // You do not understand how to use this item.
		break;
	}

	return task;
}

Reference<FindTargetTask*> BountyHunterDroid::findTarget(SceneObject* droidObject, CreatureObject* player, MissionObject* mission, bool track) {
	if (mission->getMissionLevel() < 2 ||
			(mission->getMissionLevel() < 3 && track)) {
		player->sendSystemMessage("@mission/mission_generic:bounty_no_ability"); // You do not understand how to use this item.
		return NULL;
	}

	ManagedReference<BountyMissionObjective*> objective = cast<BountyMissionObjective*>(mission->getMissionObjective());

	if (objective == NULL || objective->getObjectiveStatus() == BountyMissionObjective::INITSTATUS) {
		player->sendSystemMessage("@mission/mission_generic:bounty_no_signature");// You must go speak with your informant before you can track your target.
		return NULL;
	}

	if (player->isRidingMount()) {
		player->sendSystemMessage("@error_message:survey_on_mount"); // You cannot perform that action while mounted on a creature or driving a vehicle.
		return NULL;
	}

	ManagedReference<AiAgent*> droid = cast<AiAgent*>(player->getZone()->getCreatureManager()->spawnCreature(String("seeker").hashCode(), 0, player->getPositionX(), player->getPositionZ(), player->getPositionY(), 0));
	droid->activateLoad("stationary");

	Reference<FindTargetTask*> findTargetTask = new FindTargetTask(droid, player, objective, track, false);
	findTargetTask->schedule(2000);

	Locker locker(droidObject);

	TangibleObject* tano = cast<TangibleObject*>(droidObject);
	if(tano != NULL){
		tano->setUseCount(tano->getUseCount() - 1, true);
	} else {
		droidObject->destroyObjectFromWorld(true);
		droidObject->destroyObjectFromDatabase(true);
	}

	return findTargetTask;
}

Reference<CallArakydTask*> BountyHunterDroid::callArakydDroid(SceneObject* droidObject, CreatureObject* player, MissionObject* mission) {
	if (mission->getMissionLevel() < 2) {
		player->sendSystemMessage("@mission/mission_generic:bounty_no_ability"); // You do not understand how to use this item.
		return NULL;
	}

	if (mission->getMissionObjective() == NULL) {
		player->sendSystemMessage("@mission/mission_generic:bounty_no_mission"); // You must accept a bounty mission before you can use a probe droid.
		return NULL;
	}

	ManagedReference<BountyMissionObjective*> objective = cast<BountyMissionObjective*>(mission->getMissionObjective());

	if (objective == NULL || objective->getObjectiveStatus() == BountyMissionObjective::INITSTATUS) {
		player->sendSystemMessage("@mission/mission_generic:bounty_no_signature");// You must go speak with your informant before you can track your target.
		return NULL;
	}

	if (objective->getArakydDroid() != NULL) {
		player->sendSystemMessage("@mission/mission_generic:probe_droid_too_many"); // You cannot launch another probe droid.
		return NULL;
	}

	Vector<ManagedReference<ActiveArea*> >* areas = player->getActiveAreas();
	for (int i = 0; i < areas->size(); i++) {
		if (areas->get(i)->isMunicipalZone()) {
			player->sendSystemMessage("@mission/mission_generic:probe_droid_bad_location"); // You must move to a different area to call down a probe droid from orbit.
			return NULL;
		}
	}

	if (player->isRidingMount()) {
		player->sendSystemMessage("@error_message:survey_on_mount"); // You cannot perform that action while mounted on a creature or driving a vehicle.
		return NULL;
	}

	Reference<CallArakydTask*> task = new CallArakydTask(player, cast<BountyMissionObjective*>(mission->getMissionObjective()));

	Core::getTaskManager()->executeTask(task);

	//Temporary set the arakyd droid to the player object. The call task will overwrite it with correct value.
	//This is needed to prevent the player from launching more than one droid at a time.
	Locker olocker(objective);

	objective->setArakydDroid(player);

	olocker.release();

	Locker locker(droidObject);

	TangibleObject* tano = cast<TangibleObject*>(droidObject);

	if(tano != NULL){
		tano->setUseCount(tano->getUseCount() - 1, true);
	} else {
		droidObject->destroyObjectFromWorld(true);
		droidObject->destroyObjectFromDatabase(true);
	}

	return task;
}

Reference<FindTargetTask*> BountyHunterDroid::transmitBiologicalSignature(SceneObject* droidObject, CreatureObject* player, MissionObject* mission) {
	if (mission->getMissionLevel() < 2) {
		player->sendSystemMessage("@mission/mission_generic:bounty_no_ability"); // You do not understand how to use this item.
		return NULL;
	}

	ManagedReference<BountyMissionObjective*> objective = cast<BountyMissionObjective*>(mission->getMissionObjective());

	if (objective == NULL || objective->getObjectiveStatus() == BountyMissionObjective::INITSTATUS) {
		player->sendSystemMessage("@mission/mission_generic:bounty_no_signature"); // You must go speak with your informant before you can track your target.
		return NULL;
	}

	if (objective->hasArakydFindTask()) {
		player->sendSystemMessage("@mission/mission_generic:bounty_already_tracking"); // You are already tracking your target.
		return NULL;
	}

	if (player->isRidingMount()) {
		player->sendSystemMessage("@error_message:survey_on_mount"); // You cannot perform that action while mounted on a creature or driving a vehicle.
		return NULL;
	}

	objective->cancelCallArakydTask();

	Reference<FindTargetTask*> findTargetTask = new FindTargetTask(cast<CreatureObject*>(droidObject), player, objective, false, true);
	findTargetTask->schedule(1000);

	return findTargetTask;
}
