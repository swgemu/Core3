/*
 * CityUpdateEvent.cpp
 *
 *  Created on: Feb 23, 2012
 *      Author: xyborn
 */

#include "server/zone/objects/region/CityRegion.h"
#include "CityUpdateEvent.h"
#include "server/zone/managers/city/CityManager.h"
#include "server/zone/ZoneServer.h"

CityUpdateEvent::CityUpdateEvent(CityRegion* city, ZoneServer* zserv) : Task() {
	cityRegion = city;
	zoneServer = zserv;

	setCustomTaskQueue("slowQueue");
}

void CityUpdateEvent::run() {
	if (zoneServer == NULL || zoneServer->isServerShuttingDown())
		return;

	ManagedReference<CityRegion*> city = cityRegion.get();

	if (city == NULL)
		return;

	Locker locker(city);

	if (zoneServer->isServerLoading()) {
		city->rescheduleUpdateEvent(10000);
		return;
	}

	CityManager* cityManager = zoneServer->getCityManager();
	cityManager->processCityUpdate(city);
}
