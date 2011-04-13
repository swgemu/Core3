/*
 * MapLocationEntry.cpp
 *
 *  Created on: 24/06/2010
 *      Author: victor
 */

#include "MapLocationEntry.h"
#include "server/zone/objects/scene/SceneObject.h"

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

	mapLoc1 = entry.mapLoc1;
	mapLoc2 = entry.mapLoc2;
	mapLoc3 = entry.mapLoc3;

	return *this;
}

uint64 MapLocationEntry::getObjectID() const {
	return object->getObjectID();
}
