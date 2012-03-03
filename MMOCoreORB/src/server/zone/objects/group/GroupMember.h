/*
 * GroupMember.h
 *
 *  Created on: 29/12/2009
 *      Author: victor
 */

#ifndef GROUPMEMBER_H_
#define GROUPMEMBER_H_

#include "../scene/SceneObject.h"
#include "../scene/variables/StringId.h"

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

	void operator=(SceneObject* obj) {
		creature = obj;
	}

	SceneObject* operator->() const {
		return creature;
	}

	SceneObject* get() {
		return creature;
	}

	operator SceneObject*() const {
		return creature;
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
