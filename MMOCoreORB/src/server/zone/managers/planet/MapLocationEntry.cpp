/*
 * MapLocationEntry.cpp
 *
 *  Created on: 24/06/2010
 *      Author: victor
 *  Updated on: Sun Oct 16 16:30:54 PDT 2011 by lordkator - resolve displayName on add in setObject() with cleaner names for maps
 *
 */

#include "MapLocationEntry.h"
#include "MapLocationType.h"
#include "PlanetManager.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/area/ActiveArea.h"
#include "server/zone/objects/region/CityRegion.h"
#include "server/zone/objects/creature/CreatureObject.h"

uint64 MapLocationEntry::getObjectID() const {
	return object->getObjectID();
}

int MapLocationEntry::compareTo(const MapLocationEntry& entry) const {
	if (getObjectID() < entry.getObjectID())
		return 1;
	else if (getObjectID() > entry.getObjectID())
		return -1;
	else
		return 0;
}

MapLocationEntry& MapLocationEntry::operator=(const MapLocationEntry& entry) {
	if (this == &entry)
		return *this;

	object = entry.object;
	active = entry.active;

	return *this;
}

void MapLocationEntry::setObject(SceneObject *obj) {
	displayName = "";
	object = obj;

	if(object == NULL)
		return;

	PlanetMapCategory* category = object->getPlanetMapCategory();

	if (category == NULL)
		return;

	ManagedReference<Zone*> zone = object->getZone();

	if(zone == NULL)
		return;

	// Default is the result of getDisplayedName()
	String newName = object->getObjectName()->getDisplayedName();

	if(object->isCreatureObject()) { // Try FirstName + FastName if it's a creature
		CreatureObject* creature = cast<CreatureObject*>(object.get());

		String fName = creature->getFirstName();
		String lName = creature->getLastName();

		if(fName.length() > 0) {
			newName = fName;

			if(lName.length() > 0)
				newName += " " + lName;
		}
	} else if(category->getIndex() == MapLocationType::SHUTTLEPORT) { // Shuttleports take on the name of nearest travel point
		ManagedReference<PlanetManager*> planetManager = zone->getPlanetManager();
		PlanetTravelPoint* ptp = planetManager->getNearestPlanetTravelPoint(object, 64.f);

		if(ptp != NULL) {
			newName = ptp->getPointName();
		}
	} else { // Everything else is just named by the city it's in
		ManagedReference<PlanetManager*> planetManager = zone->getPlanetManager();

		ManagedReference<CityRegion *> region = planetManager->getRegionAt(object->getWorldPositionX(), object->getWorldPositionY());

		if(region != NULL) {
			newName = region->getRegionName();
		}
	}


	displayName = newName;
}

bool MapLocationEntry::insertToMessage(BaseMessage* message) const {
	if (object == NULL)
		return false;

	PlanetMapCategory* category = object->getPlanetMapCategory();

	if (category == NULL)
		return false;

	message->insertLong(object->getObjectID());

	message->insertUnicode(displayName);

	message->insertFloat(object->getWorldPositionX());
	message->insertFloat(object->getWorldPositionY());

	message->insertByte(category->getIndex());
	message->insertByte((object->getPlanetMapSubCategory() != NULL) ? object->getPlanetMapSubCategory()->getIndex() : 0);
	message->insertByte(active);

	return true;
}
