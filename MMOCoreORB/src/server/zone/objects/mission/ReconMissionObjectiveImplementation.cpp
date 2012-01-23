/*
 * ReconMissionObjectiveImplementation.cpp
 *
 *  Created on: 20/08/2010
 *      Author: dannuic
 */

#include "ReconMissionObjective.h"
#include "server/zone/objects/area/MissionReconActiveArea.h"

#include "server/zone/objects/waypoint/WaypointObject.h"
#include "server/zone/Zone.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/managers/object/ObjectManager.h"
#include "server/zone/managers/mission/MissionManager.h"
#include "MissionObject.h"
#include "MissionObserver.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/tangible/weapon/WeaponObject.h"

void ReconMissionObjectiveImplementation::activate() {
	if (mission == NULL)
		return;

	ManagedReference<ZoneServer*> zoneServer = Core::lookupObject<ZoneServer>("ZoneServer");

	if (locationActiveArea == NULL) {
		locationActiveArea = cast<MissionReconActiveArea*>( zoneServer->createObject(String("object/mission_recon_area.iff").hashCode(), 1));
		locationActiveArea->setMissionObjective(_this);
	}

	if (!locationActiveArea->isInQuadTree()) {
		String planetName = mission->getStartPlanet();

		Zone* zone = zoneServer->getZone(planetName);

		locationActiveArea->initializePosition(mission->getStartPositionX(), 0, mission->getStartPositionY());
		locationActiveArea->setRadius(32.f);

		if (zone != NULL) {
			zone->transferObject(locationActiveArea, -1, true);
		} else {
			error("Failed to insert recon location to zone.");
			return;
		}
	}

	WaypointObject* waypoint = mission->getWaypointToMission();

	if (waypoint == NULL)
		waypoint = mission->createWaypoint();

	waypoint->setPlanetCRC(mission->getStartPlanetCRC());
	waypoint->setPosition(mission->getStartPositionX(), 0, mission->getStartPositionY());
	waypoint->setActive(true);

	mission->updateMissionLocation();
}

void ReconMissionObjectiveImplementation::abort() {
	if (locationActiveArea != NULL)
		locationActiveArea->destroyObjectFromWorld(true);
}

void ReconMissionObjectiveImplementation::complete() {
	locationActiveArea->destroyObjectFromWorld(true);

	MissionObjectiveImplementation::complete();
}
