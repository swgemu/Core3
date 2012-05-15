/*
 * SkillList.cpp
 *
 *  Created on: 28/12/2009
 *      Author: victor
 */

#include "AbilityList.h"
#include "Ability.h"

#include "server/zone/objects/creature/variables/Skill.h"
#include "server/zone/ZoneServer.h"
#include "server/ServerCore.h"
#include "server/zone/managers/skill/SkillManager.h"

bool AbilityList::contains(const String& element) {
	String lowCase = element.toLowerCase();

	for (int i = 0; i < vector.size(); ++i) {
		Ability* ability = vector.get(i);

		if (ability == NULL)
			continue;

		String skill = ability->getAbilityName().toLowerCase();

		if (lowCase == skill)
			return true;
	}

	return false;
}

void AbilityList::insertToMessage(BaseMessage* msg) {
	msg->insertInt(size());
	msg->insertInt(updateCounter);

	for (int i = 0; i < size(); ++i) {
		Reference<Ability*> ability = get(i);

		msg->insertAscii(ability->getAbilityName());
	}
}

bool AbilityList::toBinaryStream(ObjectOutputStream* stream) {
	Vector<String> names;
	getStringList(names);

	TypeInfo<uint32>::toBinaryStream(&updateCounter, stream);
	names.toBinaryStream(stream);

	return true;
}

void AbilityList::getStringList(Vector<String>& abilities) {
	for (int i = 0; i < vector.size(); ++i) {
		Ability* ability = vector.get(i);

		String name = ability->getAbilityName();

		abilities.add(name);
	}
}

bool AbilityList::parseFromBinaryStream(ObjectInputStream* stream) {
	Vector<String> abilities;

	TypeInfo<uint32>::parseFromBinaryStream(&updateCounter, stream);
	abilities.parseFromBinaryStream(stream);

	loadFromNames(abilities);

	return true;
}

void AbilityList::loadFromNames(Vector<String>& abilities) {
	ZoneServer* server = ServerCore::getZoneServer();

	SkillManager* skillManager = server->getSkillManager();

	for (int i = 0; i < abilities.size(); ++i) {
		String name = abilities.get(i);

		Ability* ability = skillManager->getAbility(name);

		vector.add(ability);
	}
}

bool AbilityList::add(Ability* ability, DeltaMessage* message, int updates) {
	if (ability == NULL)
		return false;

	bool val = vector.add(ability);

	if (message != NULL) {
		if (updates != 0)
			message->startList(updates, updateCounter += updates);

		message->insertByte(1);
		message->insertShort(vector.size() - 1);
		ability->toBinaryStream(message);
	}

	return val;
}
