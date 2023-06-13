#include "server/zone/objects/ship/ShipObject.h"

#include "GroupMemberShip.h"

void to_json(nlohmann::json& j, const GroupMemberShip& m) {
	String name;

	j["ship"] = m.ship;

	if (m.ship != nullptr) {
		name = m.ship->getCustomObjectName().toString();
	}

	j["name"] = name;
}

bool GroupMemberShip::toBinaryStream(ObjectOutputStream* stream) {
	String name;

	ship.toBinaryStream(stream);

	if (ship != nullptr) {
		name = ship->getCustomObjectName().toString();
	}

	name.toBinaryStream(stream);

	return true;
}