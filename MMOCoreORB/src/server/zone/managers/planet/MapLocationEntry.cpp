/*
 * MapLocationEntry.cpp
 *
 *  Created on: 24/06/2010
 *      Author: victor
 */

#include "MapLocationEntry.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/area/ActiveArea.h"

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

void MapLocationEntry::insertToMessage(BaseMessage* message) const {
	message->insertLong(object->getObjectID());

	if (object->isBuildingObject() && object->getActiveRegion() != NULL)
		message->insertUnicode(object->getActiveRegion()->getObjectName()->getDisplayedName());
	else
		message->insertUnicode(object->getObjectName()->getDisplayedName());

	message->insertFloat(object->getWorldPositionX());
	message->insertFloat(object->getWorldPositionY());

	message->insertByte(object->getPlanetMapCategory()->getIndex());
	message->insertByte((object->getPlanetMapSubCategory() != NULL) ? object->getPlanetMapSubCategory()->getIndex() : 0);
	message->insertByte(active);
}
