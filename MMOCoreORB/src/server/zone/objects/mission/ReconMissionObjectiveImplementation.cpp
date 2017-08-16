/*
 * ReconMissionObjectiveImplementation.cpp
 *
 *  Created on: 20/08/2010
 *      Author: dannuic
 */

#include "server/zone/objects/mission/ReconMissionObjective.h"
#include "server/zone/objects/area/MissionReconActiveArea.h"

#include "server/zone/objects/waypoint/WaypointObject.h"
#include "server/zone/Zone.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "terrain/manager/TerrainManager.h"
#include "server/zone/objects/mission/MissionObject.h"

void ReconMissionObjectiveImplementation::activate() {
	MissionObjectiveImplementation::activate();
	ManagedReference<MissionObject* > mission = this->mission.get();

	if (mission == NULL)
		return;

	ManagedReference<ZoneServer*> zoneServer = Core::lookupObject<ZoneServer>("ZoneServer");

	if (locationActiveArea == NULL) {
		locationActiveArea = ( zoneServer->createObject(STRING_HASHCODE("object/mission_recon_area.iff"), 1)).castTo<MissionReconActiveArea*>();
		Locker locker(locationActiveArea);
		locationActiveArea->setMissionObjective(_this.getReferenceUnsafeStaticCast());
	}

	if (!locationActiveArea->isInQuadTree()) {
		String planetName = mission->getStartPlanet();

		Zone* zone = zoneServer->getZone(planetName);

		if (zone != nullptr) {
			Reference<MissionReconActiveArea* > area = locationActiveArea;

			Core::getTaskManager()->executeTask([zone, area, this, mission] () {
				Locker locker(area);

				area->initializePosition(mission->getStartPositionX(), 0, mission->getStartPositionY());
				area->setRadius(32.f);

				if (zone != NULL) {
					zone->transferObject(area, -1, true);
				} else {
					error("Failed to insert recon location to zone.");
					abort();
					return;
				}
			}, "ReconMissionObjectiveActivateLambda");
		}
	}

	ManagedReference<WaypointObject*> waypoint = mission->getWaypointToMission();

	Locker locker(waypoint);

	waypoint->setPlanetCRC(mission->getStartPlanetCRC());
	waypoint->setPosition(mission->getStartPositionX(), 0, mission->getStartPositionY());
	waypoint->setActive(true);

	mission->updateMissionLocation();
}

void ReconMissionObjectiveImplementation::abort() {
	MissionObjectiveImplementation::abort();

	if (locationActiveArea != NULL) {
		Reference<MissionReconActiveArea* > area = locationActiveArea;

		Core::getTaskManager()->executeTask([=] () {
			Locker locker(area);

			area->destroyObjectFromWorld(true);
			area->destroyObjectFromDatabase(true);
		}, "DestroyReconMissionAreaLambda");
	}
}

void ReconMissionObjectiveImplementation::complete() {
	Reference<MissionReconActiveArea* > area = locationActiveArea;

	Core::getTaskManager()->executeTask([=] () {
		Locker locker(area);

		area->destroyObjectFromWorld(true);
		area->destroyObjectFromDatabase(true);
	}, "DestroyReconMissionAreaLambda2");

	MissionObjectiveImplementation::complete();
}

Vector3 ReconMissionObjectiveImplementation::getEndPosition() {
	ManagedReference<MissionObject* > mission = this->mission.get();

	Vector3 missionEndPoint;
	if(mission == NULL)
		return missionEndPoint;

	missionEndPoint.setX(mission->getStartPositionX());
	missionEndPoint.setY(mission->getStartPositionY());

	Zone* zone =  getPlayerOwner()->getZone();

	if (zone != NULL) {
		TerrainManager* terrain = zone->getPlanetManager()->getTerrainManager();
		missionEndPoint.setZ(terrain->getHeight(missionEndPoint.getX(), missionEndPoint.getY()));
	}

	return missionEndPoint;
}
