/*
 * CityUpdateEvent.cpp
 *
 *  Created on: Feb 23, 2012
 *      Author: xyborn
 */

#include "../CityRegion.h"
#include "CityUpdateEvent.h"
#include "server/zone/managers/city/CityManager.h"
#include "server/zone/ZoneServer.h"

CityUpdateEvent::CityUpdateEvent(CityRegion* city, ZoneServer* zserv) : Task() {
	cityRegion = city;
	zoneServer = zserv;
}

void CityUpdateEvent::run() {
	ManagedReference<CityRegion*> city = cityRegion.get();

	if (city == NULL)
		return;

	Locker locker(city);

	CityManager* cityManager = zoneServer->getCityManager();
	cityManager->processCityUpdate(city);
}
