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

CityRegionImplementation::CityRegionImplementation(Zone* zne, const String& name) {
	zone = zne;

	cityRank = RANK_CLIENT; //Default to client city

	if (name.beginsWith("@")) {
		regionName.setStringId(name);
	} else {
		regionName.setCustomString(name);
	}

	setLoggingName("CityRegion " + regionName.getDisplayedName());
	setLogging(true);
}

void CityRegionImplementation::addRegion(float x, float y, float radius) {
	if (zone == NULL) {
		return;
	}

	String temp = "object/region_area.iff";
	SceneObject* obj = zone->getZoneServer()->createObject(temp.hashCode(), 1);

	if (obj == NULL || !obj->isRegion()) {
		return;
	}

	Region* region = cast<Region*>(obj);
	region->setCityRegion(_this);
	region->setRadius(radius);
	region->initializePosition(x, 0, y);

	regions.put(region);
}

void CityRegionImplementation::notifyEnter(SceneObject* object) {
	if (cityRank == RANK_CLIENT)
		return;

	if (!object->isCreatureObject())
			return;

	CreatureObject* creature = cast<CreatureObject*>(object);

	StringIdChatParameter params("city/city", "city_enter_city"); //You have entered %TT (%TO).
	params.setTT(regionName.getDisplayedName());

	if (citySpecialization.isEmpty()) {
		params.setTO("@city/city:rank" + cityRank);
	} else {
		params.setTO(String("@city/city:rank" + cityRank) + ", " + String("@city/city:" + citySpecialization));
	}

	creature->sendSystemMessage(params);

	//Apply skillmods for specialization
}

void CityRegionImplementation::notifyExit(SceneObject* object) {
	if (cityRank == RANK_CLIENT)
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
