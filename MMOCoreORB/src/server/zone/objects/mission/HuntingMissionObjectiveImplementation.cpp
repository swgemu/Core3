/*
 * HuntingMissionObjectiveImplementation.cpp
 *
 *  Created on: 20/08/2010
 *      Author: dannuic
 */

#include "HuntingMissionObjective.h"
#include "server/zone/objects/area/MissionSpawnActiveArea.h"
#include "server/zone/objects/terrain/PlanetNames.h"
#include "server/zone/objects/waypoint/WaypointObject.h"
#include "server/zone/objects/tangible/lair/LairObject.h"
#include "server/zone/Zone.h"
#include "server/zone/packets/player/PlayMusicMessage.h"
#include "server/zone/managers/object/ObjectManager.h"
#include "server/zone/managers/mission/MissionManager.h"
#include "MissionObject.h"
#include "MissionObserver.h"

void HuntingMissionObjectiveImplementation::destroyObjectFromDatabase() {
	MissionObjectiveImplementation::destroyObjectFromDatabase();
}

void HuntingMissionObjectiveImplementation::activate() {
	WaypointObject* waypoint = mission->getWaypointToMission();

	if (waypoint == NULL)
		waypoint = mission->createWaypoint();

	waypoint->setPlanetCRC(mission->getStartPlanetCRC());
	waypoint->setPosition(mission->getStartPositionX(), 0, mission->getStartPositionY());
	waypoint->setActive(true);

	mission->updateMissionLocation();
}

void HuntingMissionObjectiveImplementation::abort() {
}

void HuntingMissionObjectiveImplementation::complete() {
	PlayerCreature* player = (PlayerCreature*) getPlayerOwner();

	if (player == NULL)
		return;

	Locker locker(player);

	PlayMusicMessage* pmm = new PlayMusicMessage("sound/music_mission_complete.snd");
	player->sendMessage(pmm);

	int missionReward = mission->getRewardCredits();

	ParameterizedStringId stringId("mission/mission_generic", "success_w_amount");
	stringId.setDI(missionReward);
	player->sendSystemMessage(stringId);

	player->addBankCredits(missionReward, true);

	ZoneServer* zoneServer = player->getZoneServer();
	MissionManager* missionManager = zoneServer->getMissionManager();

	missionManager->removeMission(mission, player);
}

int HuntingMissionObjectiveImplementation::notifyObserverEvent(MissionObserver* observer, uint32 eventType, Observable* observable, ManagedObject* arg1, int64 arg2) {
	if (eventType == ObserverEventType::CONVERSE) {
	}

	return 1;
}
