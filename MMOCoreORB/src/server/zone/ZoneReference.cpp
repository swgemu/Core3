/*
 * ZoneReference.cpp
 *
 *  Created on: May 19, 2011
 *      Author: crush
 */

#include "ZoneReference.h"

#include "server/zone/Zone.h"
#include "server/ServerCore.h"

bool ZoneReference::toBinaryStream(ObjectOutputStream* stream) {
#ifdef ODB_SERIALIZATION
	zoneName.toBinaryStream(stream);
#else
	Zone* object = Reference<Zone*>::get();

	if (object != nullptr)
		object->getZoneName().toBinaryStream(stream);
	else
		stream->writeShort(0);
#endif
	return true;
}

bool ZoneReference::parseFromBinaryStream(ObjectInputStream* stream) {
#ifdef ODB_SERIALIZATION
	zoneName.parseFromBinaryStream(stream);
#else
	String zoneName;
	zoneName.parseFromBinaryStream(stream);

	Zone* obj = ServerCore::getZoneServer()->getZone(zoneName);

	if (obj == nullptr) {
		updateObject(nullptr);
		return false;
	}

	updateObject(obj);
#endif

	return true;
}

Zone* ZoneReference::operator= (Zone* obj) {
	updateObject(obj);

	return obj;
}

void server::zone::to_json(nlohmann::json& j, const ZoneReference& p) {
#ifdef ODB_SERIALIZATION
	j = p.getZoneName();
#else
	Zone* object = p.get();

	if (object != nullptr)
		j = object->getZoneName();
	else
		j = "";
#endif
}

