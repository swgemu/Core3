/*
 * MissionObjectiveImplementation.cpp
 *
 *  Created on: 22/06/2010
 *      Author: victor
 */

#include "server/zone/ZoneProcessServer.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/mission/MissionObjective.h"
#include "server/zone/objects/mission/MissionObserver.h"
#include "server/zone/objects/mission/MissionObject.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/managers/terrain/TerrainManager.h"
#include "server/zone/managers/object/ObjectManager.h"
#include "server/zone/Zone.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/group/GroupObject.h"
#include "server/zone/managers/mission/MissionManager.h"
#include "server/zone/managers/statistics/StatisticsManager.h"
#include "server/zone/packets/player/PlayMusicMessage.h"
#include "server/zone/objects/mission/events/FailMissionAfterCertainTimeTask.h"
#include "events/CompleteMissionObjectiveTask.h"
#include "server/zone/objects/group/GroupObject.h"

void MissionObjectiveImplementation::destroyObjectFromDatabase() {
	for (int i = 0; i < observers.size(); ++i) {
		MissionObserver* observer = observers.get(i);

		observer->destroyObjectFromDatabase();
	}

	ObjectManager::instance()->destroyObjectFromDatabase(_this.get()->_getObjectID());
}

ManagedWeakReference<CreatureObject*> MissionObjectiveImplementation::getPlayerOwner() {
	ManagedReference<MissionObject*> strongReference = mission.get();
	ManagedWeakReference<CreatureObject*> weak;

	if (strongReference != NULL)
		weak = cast<CreatureObject*>( strongReference->getParentRecursively(SceneObjectType::PLAYERCREATURE).get().get());

	return weak;
}

void MissionObjectiveImplementation::activate() {
	if (!activated) {
		activated = true;
		timeRemaining -= missionStartTime.miliDifference();

		if (timeRemaining < 1) {
			timeRemaining = 1;
		}

		failTask = new FailMissionAfterCertainTimeTask(_this.get());
		failTask->schedule(timeRemaining);
	}
}

void MissionObjectiveImplementation::complete() {
	Locker _lock(_this.get());

	ManagedReference<CreatureObject*> player = getPlayerOwner();

	if (player == NULL)
		return;

	_lock.release();

	Reference<CompleteMissionObjectiveTask*> task = new CompleteMissionObjectiveTask(_this.get());
	task->execute();

	if (player->isGrouped() && player->getGroup() != NULL) {
		GroupObject* group = player->getGroup();
		Locker locker(group);
		group->scheduleUpdateNearestMissionForGroup(player->getPlanetCRC());
	}

	/*awardReward();

	awardFactionPoints();

	removeMissionFromPlayer();*/
}

void MissionObjectiveImplementation::addObserver(MissionObserver* observer, bool makePersistent) {
	Locker _lock(_this.get());

	if (makePersistent) {
		ObjectManager::instance()->persistObject(observer, 1, "missionobservers");
	} else if (!observer->isDeplyoed())
		observer->deploy();

	observers.put(observer);
}

void MissionObjectiveImplementation::abort() {
	if (failTask != NULL && failTask->isScheduled()) {
		failTask->cancel();
	}
}

void MissionObjectiveImplementation::awardFactionPoints() {
	ManagedReference<MissionObject* > mission = this->mission.get();

	int factionPointsRebel = mission->getRewardFactionPointsRebel();
	int factionPointsImperial = mission->getRewardFactionPointsImperial();

	if ((factionPointsRebel <= 0 && factionPointsImperial <= 0) || mission->getFaction() == MissionObject::FACTIONNEUTRAL) {
		return;
	}

	//Award faction points for faction delivery missions.
	ManagedReference<CreatureObject*> creatureOwner = getPlayerOwner();

	if (creatureOwner != NULL) {
		ManagedReference<PlayerObject*> ghost = creatureOwner->getPlayerObject();
		if (ghost != NULL) {
			Locker ghostLocker(creatureOwner);

			//Switch to get the correct order.
			switch (mission->getFaction()) {
			case MissionObject::FACTIONIMPERIAL:
				if (factionPointsImperial > 0) {
					ghost->increaseFactionStanding("imperial", factionPointsImperial);
				}
				if (factionPointsRebel < 0) {
					ghost->decreaseFactionStanding("rebel", -factionPointsRebel);
				}
				break;
			case MissionObject::FACTIONREBEL:
				if (factionPointsRebel > 0) {
					ghost->increaseFactionStanding("rebel", factionPointsRebel);
				}
				if (factionPointsImperial < 0) {
					ghost->decreaseFactionStanding("imperial", -factionPointsImperial);
				}
				break;
			}
		}
	}
}

void MissionObjectiveImplementation::removeMissionFromPlayer() {
	ManagedReference<CreatureObject*> player = getPlayerOwner();
	ManagedReference<MissionObject* > mission = this->mission.get();

	if (player != NULL) {
		ZoneServer* zoneServer = player->getZoneServer();
		MissionManager* missionManager = zoneServer->getMissionManager();

		missionManager->removeMission(mission, player);
	}
}

void MissionObjectiveImplementation::fail() {
	abort();
	removeMissionFromPlayer();
}

void MissionObjectiveImplementation::awardReward() {
	Vector<ManagedReference<CreatureObject*> > players;
	PlayMusicMessage* pmm = new PlayMusicMessage("sound/music_mission_complete.snd");

	Vector3 missionEndPoint = getEndPosition();

	ManagedReference<CreatureObject*> owner = getPlayerOwner();

	ManagedReference<GroupObject*> group = owner->getGroup();

	if (group != NULL) {
		Locker lockerGroup(group, _this.get());

		for(int i = 0; i < group->getGroupSize(); i++) {
			Reference<CreatureObject*> groupMember = group->getGroupMember(i)->isPlayerCreature() ? (group->getGroupMember(i)).castTo<CreatureObject*>() : NULL;

			if (groupMember != NULL) {
				//Play mission complete sound.
				groupMember->sendMessage(pmm->clone());

				if (groupMember->getWorldPosition().distanceTo(missionEndPoint) < 128) {
					players.add(groupMember);
				}
			}
		}

		delete pmm;
	} else {
		//Play mission complete sound.
		owner->sendMessage(pmm);
		players.add(owner);
	}

	if (players.size() == 0) {
		players.add(owner);
	}

	ManagedReference<MissionObject* > mission = this->mission.get();

	int dividedReward = mission->getRewardCredits() / players.size();

	for (int i = 0; i < players.size(); i++) {
		ManagedReference<CreatureObject*> player = players.get(i);
		StringIdChatParameter stringId("mission/mission_generic", "success_w_amount");
		stringId.setDI(dividedReward);
		player->sendSystemMessage(stringId);

		Locker lockerPl(player, _this.get());
		player->addBankCredits(dividedReward, true);
	}

	StatisticsManager::instance()->completeMission(mission->getTypeCRC() ,mission->getRewardCredits());
}

Vector3 MissionObjectiveImplementation::getEndPosition() {
	ManagedReference<MissionObject* > mission = this->mission.get();

	Vector3 missionEndPoint;

	missionEndPoint.setX(mission->getEndPositionX());
	missionEndPoint.setY(mission->getEndPositionY());
	TerrainManager* terrain = getPlayerOwner().get()->getZone()->getPlanetManager()->getTerrainManager();
	missionEndPoint.setZ(terrain->getHeight(missionEndPoint.getX(), missionEndPoint.getY()));

	return missionEndPoint;
}
