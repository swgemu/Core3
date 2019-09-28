/*
 * GroupMember.h
 *
 *  Created on: 29/12/2009
 *      Author: victor
 */

#ifndef GROUPMEMBER_H_
#define GROUPMEMBER_H_

#include "engine/util/json_utils.h"

#include "server/zone/objects/creature/CreatureObject.h"

class GroupMember : public Variable {
	ManagedReference<CreatureObject*> creature;

public:
	GroupMember() {
		creature = nullptr;
	}

	GroupMember(const GroupMember& obj) : Variable() {
		creature = obj.creature;
	}

	GroupMember(CreatureObject* obj) {
		creature = obj;
	}

	bool operator==(const GroupMember& member) const {
		return creature.get() == member.creature.get();
	}

	bool operator==(CreatureObject* member) const {
		return creature.get() == member;
	}

	void operator=(CreatureObject* obj) {
		creature = obj;
	}

	Reference<CreatureObject*> operator->() const {
		return creature.get();
	}

	Reference<CreatureObject*> get() {
		return creature.get();
	}

	operator Reference<CreatureObject*>() const {
		return creature.get();
	}

	bool toString(String& str) {
		return creature.toString(str);
	}

	bool parseFromString(const String& str, int version = 0) {
		return creature.parseFromString(str, version);
	}

	friend void to_json(nlohmann::json& j, const GroupMember& m) {
		String name;

		j["creature"] = m.creature;

		if (m.creature != nullptr) {
			name = m.creature->getCustomObjectName().toString();
		}

		j["name"] = name;
	}

	bool toBinaryStream(ObjectOutputStream* stream) {
		String name;

		creature.toBinaryStream(stream);

		if (creature != nullptr) {
			name = creature->getCustomObjectName().toString();
		}

		name.toBinaryStream(stream);

		return true;
	}

	bool parseFromBinaryStream(ObjectInputStream* stream) {
		creature.parseFromBinaryStream(stream);

		if (creature == nullptr)
			return false;

		String name;

		name.parseFromBinaryStream(stream);

		return true;
	}

};


#endif /* GROUPMEMBER_H_ */
