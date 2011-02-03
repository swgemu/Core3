/*
 * SkillList.cpp
 *
 *  Created on: 28/12/2009
 *      Author: victor
 */

#include "SkillList.h"

#include "server/zone/objects/creature/professions/Skill.h"
#include "server/zone/ZoneServer.h"
#include "server/ServerCore.h"
#include "server/zone/managers/professions/ProfessionManager.h"

bool SkillList::contains(const String& element) {
	String lowCase = element.toLowerCase();

	for (int i = 0; i < vector.size(); ++i) {
		String skill = vector.get(i).toLowerCase();

		if (lowCase == skill)
			return true;
	}

	return false;
}

/*void SkillList::getStringList(Vector<String>& skills) {
	for (int i = 0; i < vector.size(); ++i) {
		Skill* box = vector.get(i);

		String& name = box->getName();

		skills.add(name);
	}
}

bool SkillList::toString(String& str) {
	Vector<String> names;
	getStringList(names);

	TypeInfo<uint32>::toString(&updateCounter, str);
	names.toString(str);

	return true;
}

bool SkillList::toBinaryStream(ObjectOutputStream* stream) {
	Vector<String> names;
	getStringList(names);

	TypeInfo<uint32>::toBinaryStream(&updateCounter, stream);
	names.toBinaryStream(stream);

	return true;
}


bool SkillList::parseFromString(const String& str, int version) {
	Vector<String> skills;

	TypeInfo<uint32>::parseFromString(&updateCounter, str, version);
	skills.parseFromString(str, version);

	loadFromNames(skills);

	return true;
}

bool SkillList::parseFromBinaryStream(ObjectInputStream* stream) {
	Vector<String> skills;

	TypeInfo<uint32>::parseFromBinaryStream(&updateCounter, stream);
	skills.parseFromBinaryStream(stream);

	loadFromNames(skills);

	return true;
}

void SkillList::loadFromNames(Vector<String>& skills) {
	ZoneServer* server = ServerCore::getZoneServer();
	ProfessionManager* professionManager = server->getProfessionManager();

	for (int i = 0; i < skills.size(); ++i) {
		String& name = skills.get(i);

		Skill* box = professionManager->getSkill(name);

		vector.add(box);
	}
}

bool SkillList::add(const String& element, DeltaMessage* message, int updates) {
	bool val = vector.add(element);

	if (message != NULL) {
		if (updates != 0)
			message->startList(updates, updateCounter += updates);

		message->insertByte(1);
		message->insertShort(vector.size() - 1);

		String name = element->getName();
		name.toBinaryStream(message);
	}

	return val;
}

void SkillList::insertToMessage(BaseMessage* msg) {
	msg->insertInt(size());
	msg->insertInt(updateCounter);

	for (int i = 0; i < size(); ++i) {
		Skill* skill = get(i);

		msg->insertAscii(skill->getName());
	}
}*/
