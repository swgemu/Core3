/*
 * ZoneReference.cpp
 *
 *  Created on: May 19, 2011
 *      Author: crush
 */

#include "ZoneReference.h"
#include "Zone.h"
#include "../ServerCore.h"

bool ZoneReference::toBinaryStream(ObjectOutputStream* stream) {
	Zone* object = Reference<Zone*>::get();

	if (object != NULL)
		object->getZoneName().toBinaryStream(stream);
	else
		stream->writeShort(0);

	return true;
}

bool ZoneReference::parseFromBinaryStream(ObjectInputStream* stream) {
	String zoneName;
	zoneName.parseFromBinaryStream(stream);

	Zone* obj = ServerCore::getZoneServer()->getZone(zoneName);

	if (obj == NULL) {
		updateObject(NULL);
		return false;
	}

	updateObject(obj);

	return true;
}

Zone* ZoneReference::operator= (Zone* obj) {
	updateObject(obj);

	return obj;
}
