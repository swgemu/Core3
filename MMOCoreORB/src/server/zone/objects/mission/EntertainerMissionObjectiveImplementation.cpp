/*
 * EntertainerMissionObjectiveImplementation.cpp
 *
 *  Created on: 20/08/2010
 *      Author: dannuic
 */

#include "EntertainerMissionObjective.h"

#include "server/zone/objects/waypoint/WaypointObject.h"
#include "server/zone/Zone.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/managers/object/ObjectManager.h"
#include "server/zone/managers/mission/MissionManager.h"
#include "MissionObject.h"
#include "MissionObserver.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/tangible/weapon/WeaponObject.h"

void EntertainerMissionObjectiveImplementation::activate() {
	MissionObjectiveImplementation::activate();

	if (hasObservers()) {
		return;
	}

	if (mission == NULL)
		return;

	ManagedReference<ZoneServer*> zoneServer = Core::lookupObject<ZoneServer>("ZoneServer");

	if (locationActiveArea == NULL) {
		locationActiveArea = cast<ActiveArea*>( zoneServer->createObject(String("object/active_area.iff").hashCode(), 1));
	}

	if (!locationActiveArea->isInQuadTree()) {
		String planetName = mission->getStartPlanet();

		Zone* zone = zoneServer->getZone(planetName);

		locationActiveArea->initializePosition(mission->getStartPositionX(), 0, mission->getStartPositionY());
		locationActiveArea->setRadius(32.f);

		if (zone != NULL) {
			zone->transferObject(locationActiveArea, -1, true);
		} else {
			error("Failed to insert entertainer location to zone.");
			return;
		}
	}

	Locker locationLocker(locationActiveArea);

	ManagedReference<MissionObserver*> observer1 = new MissionObserver(_this);
	addObserver(observer1, true);
	locationActiveArea->registerObserver(ObserverEventType::ENTEREDAREA, observer1);

	ManagedReference<MissionObserver*> observer2 = new MissionObserver(_this);
	addObserver(observer2, true);
	locationActiveArea->registerObserver(ObserverEventType::EXITEDAREA, observer2);

	WaypointObject* waypoint = mission->getWaypointToMission();

	if (waypoint == NULL)
		waypoint = mission->createWaypoint();

	waypoint->setPlanetCRC(mission->getStartPlanetCRC());
	waypoint->setPosition(mission->getStartPositionX(), 0, mission->getStartPositionY());
	waypoint->setActive(true);

	mission->updateMissionLocation();
}

void EntertainerMissionObjectiveImplementation::abort() {
	MissionObjectiveImplementation::abort();

	clearLocationActiveAreaAndObservers();
}

void EntertainerMissionObjectiveImplementation::clearLocationActiveAreaAndObservers() {
	if (locationActiveArea != NULL) {
		Locker locationLocker(locationActiveArea);

		for (int i = 0; i < getObserverCount(); i++) {
			ManagedReference<MissionObserver*> observer = getObserver(i);

			if (i == 0) {
				locationActiveArea->dropObserver(ObserverEventType::ENTEREDAREA, observer);
			} else {
				locationActiveArea->dropObserver(ObserverEventType::EXITEDAREA, observer);
			}
		}

		removeAllObservers();

		locationLocker.release();

		locationActiveArea->destroyObjectFromWorld(true);
	}
}

void EntertainerMissionObjectiveImplementation::complete() {
	clearLocationActiveAreaAndObservers();

	MissionObjectiveImplementation::complete();
}

void EntertainerMissionObjectiveImplementation::setIsEntertaining(bool value) {
	if (isEntertaining == value) {
		return;
	}

	isEntertaining = value;

	startCompleteTask();
}

void EntertainerMissionObjectiveImplementation::startCompleteTask() {
	//Is entertaining in mission area inside a building.
	if (isEntertaining && inMissionArea && getPlayerOwner()->getParentID() != 0) {
		if (completeTask == NULL) {
			completeTask = new CompleteMissionAfterCertainTimeTask(_this);
		}

		if (completeTask->isScheduled()) {
			completeTask->reschedule(10 * 60 * 1000);
		} else {
			completeTask->schedule(10 * 60 * 1000);
		}
	} else {
		if (completeTask != NULL && completeTask->isScheduled()) {
			completeTask->cancel();
		}
	}
}

int EntertainerMissionObjectiveImplementation::notifyObserverEvent(MissionObserver* observer, unsigned int eventType, Observable* observable, ManagedObject* arg1, long long arg2) {
	if (eventType != ObserverEventType::ENTEREDAREA && eventType != ObserverEventType::EXITEDAREA) {
		return 0;
	}

	if (cast<ActiveArea*>(observable) != locationActiveArea) {
		return 0;
	}

	if (cast<CreatureObject*>(arg1) != getPlayerOwner()) {
		return 0;
	}

	if (eventType == ObserverEventType::ENTEREDAREA) {
		inMissionArea = true;
	} else {
		inMissionArea = false;
	}

	startCompleteTask();

	return 0;
}
