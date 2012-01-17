/*
 * MissionObjectiveImplementation.cpp
 *
 *  Created on: 22/06/2010
 *      Author: victor
 */

#include "server/zone/ZoneProcessServer.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "MissionObjective.h"
#include "MissionObserver.h"
#include "MissionObject.h"
#include "server/zone/managers/object/ObjectManager.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/managers/mission/MissionManager.h"
#include "server/zone/packets/player/PlayMusicMessage.h"

void MissionObjectiveImplementation::destroyObjectFromDatabase() {
	for (int i = 0; i < observers.size(); ++i) {
		MissionObserver* observer = observers.get(i);

		observer->destroyObjectFromDatabase();
	}

	ObjectManager::instance()->destroyObjectFromDatabase(_this->_getObjectID());
}

CreatureObject* MissionObjectiveImplementation::getPlayerOwner() {
	if (mission != NULL)
		return cast<CreatureObject*>( mission->getParentRecursively(SceneObjectType::PLAYERCREATURE));
	else
		return NULL;
}

void MissionObjectiveImplementation::complete() {
	CreatureObject* player = getPlayerOwner();

	if (player == NULL)
		return;

	Locker locker(player);

	PlayMusicMessage* pmm = new PlayMusicMessage("sound/music_mission_complete.snd");
	player->sendMessage(pmm);

	int missionReward = mission->getRewardCredits();

	StringIdChatParameter stringId("mission/mission_generic", "success_w_amount");
	stringId.setDI(missionReward);
	player->sendSystemMessage(stringId);

	player->addBankCredits(missionReward, true);

	awardFactionPoints();

	removeMissionFromPlayer();
}

void MissionObjectiveImplementation::awardFactionPoints() {
	int factionPointsRebel = mission->getRewardFactionPointsRebel();
	int factionPointsImperial = mission->getRewardFactionPointsImperial();

	if ((factionPointsRebel <= 0 && factionPointsImperial <= 0) || mission->getFaction() == MissionObject::FACTIONNEUTRAL) {
		return;
	}

	//Award faction points for faction delivery missions.
	ManagedReference<PlayerObject*> ghost = getPlayerOwner()->getPlayerObject();
	if (ghost != NULL) {
		Locker ghostLocker(ghost);

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

void MissionObjectiveImplementation::removeMissionFromPlayer() {
	CreatureObject* player = getPlayerOwner();

	ZoneServer* zoneServer = player->getZoneServer();
	MissionManager* missionManager = zoneServer->getMissionManager();

	missionManager->removeMission(mission, player);
}
