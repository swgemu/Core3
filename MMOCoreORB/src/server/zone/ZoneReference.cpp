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
	Zone* object = Reference<Zone*>::get();

	if (object != nullptr)
		object->getZoneName().toBinaryStream(stream);
	else
		stream->writeShort(0);

	return true;
}

bool ZoneReference::parseFromBinaryStream(ObjectInputStream* stream) {
	String zoneName;
	zoneName.parseFromBinaryStream(stream);

	Zone* obj = ServerCore::getZoneServer()->getZone(zoneName);

	if (obj == nullptr) {
		updateObject(nullptr);
		return false;
	}

	updateObject(obj);

	return true;
}

Zone* ZoneReference::operator= (Zone* obj) {
	updateObject(obj);

	return obj;
}

String ZoneReference::toString() const {
	Zone* obj = Reference<Zone*>::get();

	if (obj != nullptr) {
		return obj->getZoneName();
	} else {
		return String();
	}
}

void server::zone::to_json(nlohmann::json& j, const server::zone::ZoneReference& p) {
	auto val = p.toString();

	j = val.toCharArray();
}