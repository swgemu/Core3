/*
 * SpaceZoneReference.cpp
 *
 *  Created on: May 19, 2011
 *      Author: crush
 */

#include "SpaceZoneReference.h"

#include "server/zone/SpaceZone.h"
#include "server/ServerCore.h"

bool SpaceZoneReference::toBinaryStream(ObjectOutputStream* stream) {
#ifdef ODB_SERIALIZATION
	zoneName.toBinaryStream(stream);
#else
	SpaceZone* object = Reference<SpaceZone*>::get();

	if (object != nullptr)
		object->getZoneName().toBinaryStream(stream);
	else
		stream->writeShort(0);
#endif
	return true;
}

bool SpaceZoneReference::parseFromBinaryStream(ObjectInputStream* stream) {
#ifdef ODB_SERIALIZATION
	zoneName.parseFromBinaryStream(stream);
#else
	String zoneName;
	zoneName.parseFromBinaryStream(stream);

	Zone* zone = ServerCore::getZoneServer()->getZone(zoneName);

	if (zone == nullptr || !zone->isSpaceZone())
		return false;

	SpaceZone* spaceZone = cast<SpaceZone*>(zone);

	if (spaceZone == nullptr) {
		updateObject(nullptr);
		return false;
	}

	updateObject(spaceZone);
#endif

	return true;
}

SpaceZone* SpaceZoneReference::operator= (SpaceZone* obj) {
	updateObject(obj);

	return obj;
}

void server::zone::to_json(nlohmann::json& j, const SpaceZoneReference& p) {
#ifdef ODB_SERIALIZATION
	j = p.getZoneName();
#else
	SpaceZone* object = p.get();

	if (object != nullptr)
		j = object->getZoneName();
	else
		j = "";
#endif
}

