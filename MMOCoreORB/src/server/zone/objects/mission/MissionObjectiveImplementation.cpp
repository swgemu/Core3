/*
 * MissionObjectiveImplementation.cpp
 *
 *  Created on: 22/06/2010
 *      Author: victor
 */

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/mission/MissionObjective.h"
#include "server/zone/objects/mission/MissionObserver.h"
#include "server/zone/objects/mission/MissionObject.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "terrain/manager/TerrainManager.h"
#include "server/zone/managers/object/ObjectManager.h"
#include "server/zone/Zone.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/group/GroupObject.h"
#include "server/zone/managers/mission/MissionManager.h"
#include "server/zone/managers/statistics/StatisticsManager.h"
#include "server/zone/packets/player/PlayMusicMessage.h"
#include "server/zone/objects/mission/events/FailMissionAfterCertainTimeTask.h"
#include "events/CompleteMissionObjectiveTask.h"

void MissionObjectiveImplementation::destroyObjectFromDatabase() {
	for (int i = 0; i < observers.size(); ++i) {
		MissionObserver* observer = observers.get(i);

		Locker clocker(observer, _this.getReferenceUnsafeStaticCast());

		observer->destroyObjectFromDatabase();
	}

	ObjectManager::instance()->destroyObjectFromDatabase(_this.getReferenceUnsafeStaticCast()->_getObjectID());
}

Reference<CreatureObject*> MissionObjectiveImplementation::getPlayerOwner() {
	ManagedReference<MissionObject*> strongReference = mission.get();

	if (strongReference != NULL)
		return strongReference->getParentRecursively(SceneObjectType::PLAYERCREATURE).castTo<CreatureObject*>();

	return NULL;
}

void MissionObjectiveImplementation::activate() {
	if (!activated) {
		activated = true;
		int64 timeElapsed = missionStartTime.miliDifference();
		int64 timeRemaining = MISSIONDURATION - timeElapsed;

		if (timeRemaining < 1) {
			timeRemaining = 1;
		}

		failTask = new FailMissionAfterCertainTimeTask(mission.get());
		failTask->schedule(timeRemaining);
	}
}

void MissionObjectiveImplementation::complete() {
	Locker _lock(_this.getReferenceUnsafeStaticCast());

	ManagedReference<CreatureObject*> player = getPlayerOwner();

	if (player == NULL)
		return;

	_lock.release();

	Reference<CompleteMissionObjectiveTask*> task = new CompleteMissionObjectiveTask(_this.getReferenceUnsafeStaticCast());
	task->execute();

	if (player->isGrouped() && player->getGroup() != NULL) {
		GroupObject* group = player->getGroup();
		Locker locker(group);
		group->scheduleUpdateNearestMissionForGroup(player->getPlanetCRC());
	}

	clearFailTask();
}

void MissionObjectiveImplementation::addObserver(MissionObserver* observer, bool makePersistent) {
	Locker _lock(_this.getReferenceUnsafeStaticCast());

	if (makePersistent) {
		ObjectManager::instance()->persistObject(observer, 1, "missionobservers");
	} else if (!observer->isDeplyoed())
		observer->deploy();

	observers.put(observer);
}

void MissionObjectiveImplementation::abort() {
	clearFailTask();
}

void MissionObjectiveImplementation::clearFailTask() {
	if (failTask != NULL) {
		if (failTask->isScheduled())
			failTask->cancel();

		failTask = NULL;
	}
}

void MissionObjectiveImplementation::awardFactionPoints() {
	ManagedReference<MissionObject* > mission = this->mission.get();

	if(mission == NULL)
		return;

	int factionPointsRebel = mission->getRewardFactionPointsRebel();
	int factionPointsImperial = mission->getRewardFactionPointsImperial();

	if ((factionPointsRebel <= 0 && factionPointsImperial <= 0) || mission->getFaction() == Factions::FACTIONNEUTRAL) {
		return;
	}

	//Award faction points for faction delivery missions.
	ManagedReference<CreatureObject*> creatureOwner = getPlayerOwner();

	if (creatureOwner != NULL) {
		ManagedReference<PlayerObject*> ghost = creatureOwner->getPlayerObject();
		if (ghost != NULL) {
			Locker lockerGroup(creatureOwner, _this.getReferenceUnsafeStaticCast());

			//Switch to get the correct order.
			switch (mission->getFaction()) {
			case Factions::FACTIONIMPERIAL:
				if (factionPointsImperial > 0) {
					ghost->increaseFactionStanding("imperial", factionPointsImperial);
				}
				if (factionPointsRebel < 0) {
					ghost->decreaseFactionStanding("rebel", -factionPointsRebel);
				}
				break;
			case Factions::FACTIONREBEL:
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

	if (player != NULL && mission != NULL) {
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
	ManagedReference<MissionObject* > mission = this->mission.get();

	if(mission == NULL)
		return;

	Vector<ManagedReference<CreatureObject*> > players;
	PlayMusicMessage* pmm = new PlayMusicMessage("sound/music_mission_complete.snd");

	Vector3 missionEndPoint = getEndPosition();

	ManagedReference<CreatureObject*> owner = getPlayerOwner();

	ManagedReference<GroupObject*> group = owner->getGroup();

	int playerCount = 1;

	if (group != NULL) {
		Locker lockerGroup(group, _this.getReferenceUnsafeStaticCast());

		playerCount = group->getNumberOfPlayerMembers();

#ifdef LOCKFREE_BCLIENT_BUFFERS
	Reference<BasePacket*> pack = pmm;
#endif

		for (int i = 0; i < group->getGroupSize(); i++) {
			Reference<CreatureObject*> groupMember = group->getGroupMember(i);

			if (groupMember != NULL && groupMember->isPlayerCreature()) {
				//Play mission complete sound.
#ifdef LOCKFREE_BCLIENT_BUFFERS
				groupMember->sendMessage(pack);
#else
				groupMember->sendMessage(pmm->clone());
#endif

				if (groupMember->getWorldPosition().distanceTo(missionEndPoint) < 128) {
					players.add(groupMember);
				}
			}
		}

#ifndef LOCKFREE_BCLIENT_BUFFERS
		delete pmm;
#endif
	} else {
		//Play mission complete sound.
		owner->sendMessage(pmm);
		players.add(owner);
	}

	if (players.size() == 0) {
		players.add(owner);
	}

	int divisor = mission->getRewardCreditsDivisor();
	bool expanded = false;

	if (playerCount > divisor) {
		divisor = playerCount;
		expanded = true;
	}

	if (playerCount > players.size()) {
		owner->sendSystemMessage("@mission/mission_generic:group_too_far"); // Mission Alert! Some group members are too far away from the group to receive their reward and and are not eligible for reward.
	}

	int dividedReward = mission->getRewardCredits() / Math::max(divisor, 1);

	for (int i = 0; i < players.size(); i++) {
		ManagedReference<CreatureObject*> player = players.get(i);
		StringIdChatParameter stringId("mission/mission_generic", "success_w_amount");
		stringId.setDI(dividedReward);
		player->sendSystemMessage(stringId);

		Locker lockerPl(player, _this.getReferenceUnsafeStaticCast());
		player->addBankCredits(dividedReward, true);
	}

	if (group != NULL) {
		if (expanded) {
			owner->sendSystemMessage("@mission/mission_generic:group_expanded"); // Group Mission Success! Reward credits have been transmitted to the bank account of all group members in the immediate area. They have been recalculated to reflect the newly added members.
		} else {
			owner->sendSystemMessage("@mission/mission_generic:group_success"); // Group Mission Success! Reward credits have been transmitted to the bank account of all group members in the immediate area.
		}
	}

	int creditsDistributed = dividedReward * players.size();

	StatisticsManager::instance()->completeMission(mission->getTypeCRC(), creditsDistributed);
}

Vector3 MissionObjectiveImplementation::getEndPosition() {
	ManagedReference<MissionObject* > mission = this->mission.get();

	Vector3 missionEndPoint;
	if(mission != NULL) {
		missionEndPoint.setX(mission->getEndPositionX());
		missionEndPoint.setY(mission->getEndPositionY());
		TerrainManager* terrain = getPlayerOwner()->getZone()->getPlanetManager()->getTerrainManager();
		missionEndPoint.setZ(terrain->getHeight(missionEndPoint.getX(), missionEndPoint.getY()));
	}

	return missionEndPoint;
}
