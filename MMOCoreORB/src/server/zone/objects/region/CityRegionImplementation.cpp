/*
 * CityRegionImplementation.cpp
 *
 *  Created on: Feb 9, 2012
 *      Author: xyborn
 */

#include "CityRegion.h"
#include "server/zone/Zone.h"
#include "server/chat/StringIdChatParameter.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/region/Region.h"
#include "server/zone/managers/stringid/StringIdManager.h"

void CityRegionImplementation::initialize(Zone* zne, const String& name) {
	zone = zne;

	zoningEnabled = true;

	cityTreasury = 0;

	cityRank = RANK_CLIENT; //Default to client city

	if (name.beginsWith("@")) {
		regionName.setStringId(name);
	} else {
		regionName.setCustomString(name);
	}

	mayorID = 0;

	zoningRights.setAllowOverwriteInsertPlan();
	zoningRights.setNullValue(0);

	setLoggingName("CityRegion " + regionName.getDisplayedName());
	setLogging(true);
}

Region* CityRegionImplementation::addRegion(float x, float y, float radius) {
	if (zone == NULL) {
		return NULL;
	}

	String temp = "object/region_area.iff";
	SceneObject* obj = zone->getZoneServer()->createObject(temp.hashCode(), 1);

	if (obj == NULL || !obj->isRegion()) {
		return NULL;
	}

	Region* region = cast<Region*>(obj);
	region->setCityRegion(_this);
	region->setRadius(radius);
	region->initializePosition(x, 0, y);

	if (regions.size() <= 0) {
		region->setPlanetMapCategory(TemplateManager::instance()->getPlanetMapCategoryByName("city"));
		region->setObjectName(regionName);
	}

	if (isClientRegion())
		region->setNoBuildArea(true);

	zone->transferObject(region, -1, false);

	regions.put(region);

	return region;
}

void CityRegionImplementation::notifyEnter(SceneObject* object) {
	object->setCityRegion(_this);

	if (isClientRegion())
		return;

	if (!object->isCreatureObject())
			return;

	CreatureObject* creature = cast<CreatureObject*>(object);

	StringIdChatParameter params("city/city", "city_enter_city"); //You have entered %TT (%TO).
	params.setTT(regionName.getDisplayedName());

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
	params.setTO(regionName.getDisplayedName());

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
