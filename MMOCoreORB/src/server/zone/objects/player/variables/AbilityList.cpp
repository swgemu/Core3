/*
 * SkillList.cpp
 *
 *  Created on: 28/12/2009
 *      Author: victor
 */

#include "AbilityList.h"
#include "Ability.h"

#include "server/zone/ZoneServer.h"
#include "server/ServerCore.h"
#include "server/zone/managers/skill/SkillManager.h"

bool AbilityList::contains(const String& element) const {
	String lowCase = element.toLowerCase();

	for (int i = 0; i < vector.size(); ++i) {
		Ability* ability = vector.get(i);

		if (ability == nullptr)
			continue;

		String skill = ability->getAbilityName().toLowerCase();

		if (lowCase == skill)
			return true;
	}

	return false;
}

void AbilityList::insertToMessage(BaseMessage* msg) const {
	ReadLocker locker(getLock());

	msg->insertInt(size());
	msg->insertInt(updateCounter);

	for (int i = 0; i < size(); ++i) {
		Ability* ability = get(i);

		msg->insertAscii(ability->getAbilityName());
	}
}

bool AbilityList::toBinaryStream(ObjectOutputStream* stream) {
	TypeInfo<uint32>::toBinaryStream(&updateCounter, stream);

#ifdef ODB_SERIALIZATION
	abilities.toBinaryStream(stream);
#else
	Vector<String> names;
	getStringList(names);

	names.toBinaryStream(stream);
#endif

	return true;
}

void to_json(nlohmann::json& j, const AbilityList& l) {
	Vector<String> names;
	l.getStringList(names);

	j["updateCounter"] = l.updateCounter;
	j["names"] = names;
}

void AbilityList::getStringList(Vector<String>& abilities) const {
#ifdef ODB_SERIALIZATION
	abilities = this->abilities;
#else
	for (int i = 0; i < vector.size(); ++i) {
		Ability* ability = vector.getUnsafe(i);

		const auto& name = ability->getAbilityName();

		abilities.emplace(name);
	}
#endif
}

bool AbilityList::parseFromBinaryStream(ObjectInputStream* stream) {
	TypeInfo<uint32>::parseFromBinaryStream(&updateCounter, stream);

#ifdef ODB_SERIALIZATION
	abilities.parseFromBinaryStream(stream);
#else
	Vector<String> abilities;
	abilities.parseFromBinaryStream(stream);

	loadFromNames(abilities);
#endif

	return true;
}

void AbilityList::loadFromNames(Vector<String>& abilities) {
	ZoneServer* server = ServerCore::getZoneServer();

	SkillManager* skillManager = server->getSkillManager();

	for (int i = 0; i < abilities.size(); ++i) {
		const String& name = abilities.get(i);

		Ability* ability = skillManager->getAbility(name);

		if (ability == nullptr) {
			Logger::console.error(name + " is null when trying to load from database");
		} else {
			vector.add(ability);
		}
	}
}

bool AbilityList::add(Ability* const& ability, DeltaMessage* message, int updates) {
	if (ability == nullptr)
		return false;

	bool val = vector.add(ability);

	if (message != nullptr) {
		if (updates != 0)
			message->startList(updates, updateCounter += updates);

		message->insertByte(1);
		message->insertShort(vector.size() - 1);
		ability->toBinaryStream(message);
	}

	return val;
}
