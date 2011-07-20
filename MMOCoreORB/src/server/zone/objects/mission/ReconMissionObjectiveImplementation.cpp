/*
 * ReconMissionObjectiveImplementation.cpp
 *
 *  Created on: 20/08/2010
 *      Author: dannuic
 */

#include "ReconMissionObjective.h"
#include "server/zone/objects/area/MissionReconActiveArea.h"

#include "server/zone/objects/waypoint/WaypointObject.h"
#include "server/zone/objects/tangible/lair/LairObject.h"
#include "server/zone/Zone.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/packets/player/PlayMusicMessage.h"
#include "server/zone/managers/object/ObjectManager.h"
#include "server/zone/managers/mission/MissionManager.h"
#include "MissionObject.h"
#include "MissionObserver.h"

void ReconMissionObjectiveImplementation::activate() {
	/*
	if (mission == NULL)
		return;

	ManagedReference<ZoneServer*> zoneServer = Core::lookupObject<ZoneServer>("ZoneServer");

	if (locationActiveArea == NULL) {
		locationActiveArea = (MissionReconActiveArea*) zoneServer->createObject(String("object/mission_recon_area.iff").hashCode(), 1);
		locationActiveArea->setMissionObjective(_this);
	}

	if (!locationActiveArea->isInQuadTree()) {
		uint32 startPlanetCRC = mission->getStartPlanetCRC();

		String planetName = Planet::getPlanetNameByCrc(startPlanetCRC);

		Zone* zone = zoneServer->getZone(planetName);
		locationActiveArea->initializePosition(mission->getStartPositionX(), 0, mission->getStartPositionY());
		locationActiveArea->setRadius(32.f);
		locationActiveArea->insertToZone(zone);

		info("inserting to zone " + zone->getZoneName(), true);
	}

	WaypointObject* waypoint = mission->getWaypointToMission();

	if (waypoint == NULL)
		waypoint = mission->createWaypoint();

	waypoint->setPlanetCRC(mission->getStartPlanetCRC());
	waypoint->setPosition(mission->getStartPositionX(), 0, mission->getStartPositionY());
	waypoint->setActive(true);

	mission->updateMissionLocation();
	*/
}

void ReconMissionObjectiveImplementation::abort() {
	if (locationActiveArea != NULL)
		locationActiveArea->removeFromZone();
}

void ReconMissionObjectiveImplementation::complete() {
	CreatureObject* player = (CreatureObject*) getPlayerOwner();

	if (player == NULL)
		return;

	locationActiveArea->removeFromZone();

	Locker locker(player);

	PlayMusicMessage* pmm = new PlayMusicMessage("sound/music_mission_complete.snd");
	player->sendMessage(pmm);

	int missionReward = mission->getRewardCredits();

	StringIdChatParameter stringId("mission/mission_generic", "success_w_amount");
	stringId.setDI(missionReward);
	player->sendSystemMessage(stringId);

	player->addBankCredits(missionReward, true);

	ZoneServer* zoneServer = player->getZoneServer();
	MissionManager* missionManager = zoneServer->getMissionManager();

	missionManager->removeMission(mission, player);
}
