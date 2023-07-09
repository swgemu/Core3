/*
* GroupMember.cpp
*/

#include "server/zone/objects/creature/CreatureObject.h"

#include "GroupMember.h"

void to_json(nlohmann::json& j, const GroupMember& m) {
	String name;

	j["creature"] = m.creature;

	if (m.creature != nullptr) {
		name = m.creature->getCustomObjectName().toString();
	}

	j["name"] = name;
}

bool GroupMember::toBinaryStream(ObjectOutputStream* stream) {
	String name;

	creature.toBinaryStream(stream);

	if (creature != nullptr) {
		name = creature->getCustomObjectName().toString();
	}

	name.toBinaryStream(stream);

	return true;
}