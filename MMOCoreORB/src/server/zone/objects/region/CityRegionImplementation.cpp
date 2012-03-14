/*
 * CityRegionImplementation.cpp
 *
 *  Created on: Feb 9, 2012
 *      Author: xyborn
 */

#include "CityRegion.h"
#include "events/CityUpdateEvent.h"
#include "server/zone/Zone.h"
#include "server/zone/objects/area/ActiveArea.h"
#include "server/chat/StringIdChatParameter.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/structure/StructureObject.h"
#include "server/zone/objects/region/Region.h"
#include "server/zone/managers/stringid/StringIdManager.h"
#include "server/ServerCore.h"
#include "server/zone/managers/city/CityManager.h"

void CityRegionImplementation::initializeTransientMembers() {
	ManagedObjectImplementation::initializeTransientMembers();

	if (cityRank == CityManager::CLIENT)
		return;

	int seconds = -1 * round(nextUpdateTime.miliDifference() / 1000.f);

	if (seconds < 0) //If the update occurred in the past, force an immediate update.
		seconds = 0;

	rescheduleUpdateEvent(seconds);
}

void CityRegionImplementation::initialize() {
	zoningEnabled = true;

	registered = false;

	cityTreasury = 0;

	cityRank = RANK_CLIENT; //Default to client city

	cityHall = NULL;

	mayorID = 0;

	zone = NULL;

	cityUpdateEvent = NULL;

	zoningRights.setAllowOverwriteInsertPlan();
	zoningRights.setNullValue(0);

	setLoggingName("CityRegion");
	setLogging(true);
}

Region* CityRegionImplementation::addRegion(float x, float y, float radius, bool persistent) {
	if (zone == NULL) {
		return NULL;
	}

	String temp = "object/region_area.iff";
	SceneObject* obj = zone->getZoneServer()->createObject(temp.hashCode(), persistent ? 1 : 0);

	if (obj == NULL || !obj->isRegion()) {
		return NULL;
	}

	ManagedReference<Region*> region = cast<Region*>(obj);
	region->setCityRegion(_this);
	region->setRadius(radius);
	region->initializePosition(x, 0, y);
	region->setObjectName(regionName);

	if (isClientRegion())
		region->setNoBuildArea(true);

	zone->transferObject(region, -1, false);

	regions.put(region);

	return region;
}

void CityRegionImplementation::rescheduleUpdateEvent(uint32 seconds) {
	if (cityRank == CityManager::CLIENT)
		return;

	if (cityUpdateEvent == NULL) {
		cityUpdateEvent = new CityUpdateEvent(_this, ServerCore::getZoneServer());
	} else if (cityUpdateEvent->isScheduled()) {
		cityUpdateEvent->cancel();
	}

	cityUpdateEvent->schedule(seconds * 1000);
	Core::getTaskManager()->getNextExecutionTime(cityUpdateEvent, nextUpdateTime);
}

int CityRegionImplementation::getTimeToUpdate() {
	return round(nextUpdateTime.miliDifference() / -1000.f);
}

void CityRegionImplementation::notifyEnter(SceneObject* object) {
	object->setCityRegion(_this);

	if (isClientRegion())
		return;

	if (!object->isCreatureObject())
			return;

	CreatureObject* creature = cast<CreatureObject*>(object);

	StringIdChatParameter params("city/city", "city_enter_city"); //You have entered %TT (%TO).
	params.setTT(getRegionName());

	UnicodeString strRank = StringIdManager::instance()->getStringId(String("@city/city:rank" + String::valueOf(cityRank)).hashCode());

	if (citySpecialization.isEmpty()) {
		params.setTO(strRank);
	} else {
		UnicodeString citySpec = StringIdManager::instance()->getStringId(citySpecialization.hashCode());
		params.setTO(strRank + ", " + citySpec);
	}

	creature->sendSystemMessage(params);

	//Apply skillmods for specialization
}

void CityRegionImplementation::notifyExit(SceneObject* object) {
	object->setCityRegion(NULL);

	if (isClientRegion())
		return;

	if (!object->isCreatureObject())
		return;

	CreatureObject* creature = cast<CreatureObject*>(object);

	StringIdChatParameter params("city/city", "city_leave_city"); //You have left %TO.
	params.setTO(getRegionName());

	creature->sendSystemMessage(params);

	//Remove skillmods for specialization
}

void CityRegionImplementation::setRegionName(const StringId& name) {
	regionName = name;
}

Vector<ManagedReference<SceneObject*> >* CityRegionImplementation::getVendorsInCity() {
	Vector<ManagedReference<SceneObject*> >* vendors = new Vector<ManagedReference<SceneObject*> >();

	return vendors;
}

void CityRegionImplementation::addZoningRights(uint64 objectid, uint32 duration) {
	Time now;

	zoningRights.put(objectid, duration + now.getTime());
}

bool CityRegionImplementation::hasZoningRights(uint64 objectid) {
	if (isMilitiaMember(objectid))
		return true;

	uint32 timestamp = zoningRights.get(objectid);

	if (timestamp == 0)
		return false;

	Time now;
	return (now.getTime() <= timestamp);
}

void CityRegionImplementation::setZone(Zone* zne) {
	zone = zne;
}

void CityRegionImplementation::setRadius(float rad) {
	if (regions.size() <= 0)
		return;

	ManagedReference<ActiveArea*> aa = regions.get(0).get();
	aa->setRadius(rad);

	zone->removeObject(aa, NULL, false);
	zone->transferObject(aa, -1, false);
}

void CityRegionImplementation::destroyActiveAreas() {
	for (int i = 0; i < regions.size(); ++i) {
		ManagedReference<Region*> aa = regions.get(i);

		if (aa != NULL) {
			aa->destroyObjectFromWorld(false);
			aa->destroyObjectFromDatabase(true);

			regions.drop(aa);
		}
	}
}

String CityRegionImplementation::getRegionName() {
	if(!customRegionName.isEmpty())
		return customRegionName;

	return regionName.getFullPath();
}
