/*
 * CityRegion.cpp
 *
 *  Created on: Feb 9, 2012
 *      Author: xyborn
 */

#include "CityRegion.h"
#include "server/zone/Zone.h"
#include "server/chat/StringIdChatParameter.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/area/ActiveArea.h"

CityRegion::CityRegion(Zone* zne, const String& name) {
	zone = zne;

	cityRank = RANK_CLIENT; //Default to client city

	if (name.beginsWith("@")) {
		regionName.setStringId(name);
	} else {
		regionName.setCustomString(name);
	}

	setLoggingName("CityRegion[" + regionName.getDisplayedName() + "]");
	setLogging(true);

	addSerializableVariables();
}

CityRegion::CityRegion(const CityRegion& cr) : Object(), Logger(), ReadWriteLock() {
	regionName = cr.regionName;
	zone = cr.zone;
	activeAreas = cr.activeAreas;
	cityRank = cr.cityRank;
	citySpecialization = cr.citySpecialization;

	setLoggingName("CityRegion[" + regionName.getDisplayedName() + "]");
	setLogging(true);

	addSerializableVariables();
}

CityRegion& CityRegion::operator=(const CityRegion& cr) {
	if (this == &cr)
		return *this;

	regionName = cr.regionName;
	zone = cr.zone;
	activeAreas = cr.activeAreas;
	cityRank = cr.cityRank;
	citySpecialization = cr.citySpecialization;

	return *this;
}

void CityRegion::addSerializableVariables() {
	addSerializableVariable("regionName", &regionName);
	addSerializableVariable("zone", &zone);
	addSerializableVariable("activeAreas", &activeAreas);
	addSerializableVariable("cityRank", &cityRank);
	addSerializableVariable("citySpecialization", &citySpecialization);
}

void CityRegion::addActiveArea(float x, float y, float radius) {
	SceneObject* obj = zone->getZoneServer()->createObject(String("object/active_area.iff").hashCode(), 1);

	if (obj == NULL || !obj->isActiveArea())
		return;

	ActiveArea* aa = cast<ActiveArea*>(obj);
	aa->setRadius(radius);
	aa->initializePosition(x, 0, y);
}

void CityRegion::notifyEnter(CreatureObject* creature) {
	if (cityRank == RANK_CLIENT)
		return;

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

void CityRegion::notifyExit(CreatureObject* creature) {
	if (cityRank == RANK_CLIENT)
		return;

	StringIdChatParameter params("city/city", "city_leave_city"); //You have left %TO.
	params.setTO(regionName.getDisplayedName());

	//Remove skillmods for specialization
}

bool CityRegion::containsPoint(float x, float y) {
	Locker lock(this);

	for (int i = 0; i < activeAreas.size(); ++i) {
		ActiveArea* aa = activeAreas.get(i);

		if (aa->containsPoint(x, y))
			return true;
	}

	return false;
}
