/*
 * GroupMember.h
 *
 *  Created on: 29/12/2009
 *      Author: victor
 */

#ifndef GROUPMEMBER_H_
#define GROUPMEMBER_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/scene/variables/StringId.h"

class GroupMember : public Variable {
	ManagedReference<SceneObject*> creature;

public:
	GroupMember() {
		creature = NULL;
	}

	GroupMember(const GroupMember& obj) : Variable() {
		creature = obj.creature;
	}

	GroupMember(SceneObject* obj) {
		creature = obj;
	}

	bool operator==(const GroupMember& member) const {
		return creature.get() == member.creature.get();
	}

	bool operator==(SceneObject* member) const {
		return creature.get() == member;
	}

	void operator=(SceneObject* obj) {
		creature = obj;
	}

	Reference<SceneObject*> operator->() const {
		return creature.get();
	}

	Reference<SceneObject*> get() {
		return creature.get();
	}

	operator Reference<SceneObject*>() const {
		return creature.get();
	}

	bool toString(String& str) {
		return creature.toString(str);
	}

	bool parseFromString(const String& str, int version = 0) {
		return creature.parseFromString(str, version);
	}

	bool toBinaryStream(ObjectOutputStream* stream) {
		String name;

		creature.toBinaryStream(stream);

		if (creature != NULL) {
			StringId* stringId = creature->getObjectName();
			name = creature->getCustomObjectName().toString();
		}

		name.toBinaryStream(stream);

		return true;
	}

	bool parseFromBinaryStream(ObjectInputStream* stream) {
		creature.parseFromBinaryStream(stream);

		if (creature == NULL)
			return false;

		String name;

		name.parseFromBinaryStream(stream);

		return true;
	}



};


#endif /* GROUPMEMBER_H_ */
