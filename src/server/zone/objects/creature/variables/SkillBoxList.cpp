/*
 * SkillBoxMap.cpp
 *
 *  Created on: 27/12/2009
 *      Author: victor
 */

#include "SkillBoxList.h"

#include "../professions/SkillBox.h"
#include "server/ServerCore.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/managers/professions/ProfessionManager.h"
#include "server/zone/managers/objectcontroller/ObjectController.h"

bool SkillBoxList::containsSkillBox(const String& skillBox) {
	for (int i = 0; i < vector.size(); ++i) {
		SkillBox* box = vector.get(i);

		String& name = box->getName();

		if (name == skillBox)
			return true;
	}

	return false;
}

void SkillBoxList::getStringList(Vector<String>& skillBoxes) {
	for (int i = 0; i < vector.size(); ++i) {
		SkillBox* box = vector.get(i);

		String& name = box->getName();

		skillBoxes.add(name);
	}
}

bool SkillBoxList::toString(String& str) {
	Vector<String> names;
	getStringList(names);

	TypeInfo<uint32>::toString(&updateCounter, str);
	names.toString(str);

	return true;
}

bool SkillBoxList::toBinaryStream(ObjectOutputStream* stream) {
	Vector<String> names;
	getStringList(names);

	TypeInfo<uint32>::toBinaryStream(&updateCounter, stream);
	names.toBinaryStream(stream);

	return true;
}


bool SkillBoxList::parseFromString(const String& str, int version) {
	Vector<String> skillBoxes;

	TypeInfo<uint32>::parseFromString(&updateCounter, str, version);
	skillBoxes.parseFromString(str, version);

	loadFromNames(skillBoxes);

	return true;
}

bool SkillBoxList::parseFromBinaryStream(ObjectInputStream* stream) {
	Vector<String> skillBoxes;

	TypeInfo<uint32>::parseFromBinaryStream(&updateCounter, stream);
	skillBoxes.parseFromBinaryStream(stream);

	loadFromNames(skillBoxes);

	return true;
}

void SkillBoxList::loadFromNames(Vector<String>& skillBoxes) {
	ZoneServer* server = ServerCore::getZoneServer();
	ProfessionManager* professionManager = server->getProfessionManager();

	for (int i = 0; i < skillBoxes.size(); ++i) {
		String& name = skillBoxes.get(i);

		SkillBox* box = professionManager->getSkillBox(name);

		vector.add(box);
	}
}

bool SkillBoxList::add(SkillBox* element, DeltaMessage* message) {
	bool val = vector.add(element);

	if (message != NULL) {
		message->startList(1, ++updateCounter);

		message->insertByte(1);

		String name = element->getName();
		name.toBinaryStream(message);
	}

	return val;
}

void SkillBoxList::remove(SkillBox* skillBox, DeltaMessage* message) {
	int index = find(skillBox);

	SkillBox* object = vector.remove(index);

	if (message != NULL) {
		message->startList(1, ++updateCounter);

		message->insertByte(0);
		String name = object->getName();
		name.toBinaryStream(message);
	}
}

void SkillBoxList::insertToMessage(BaseMessage* msg) {
	msg->insertInt(size());
	msg->insertInt(updateCounter);

	for (int i = 0; i < size(); ++i) {
		SkillBox* skillBox = get(i);

		msg->insertAscii(skillBox->getName());
	}
}
