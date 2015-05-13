/*
 * CharacterNameMap.h
 *
 *  Created on: 03/02/2010
 *      Author: victor
 */

#ifndef CHARACTERNAMEMAP_H_
#define CHARACTERNAMEMAP_H_

#include "engine/engine.h"
#include "server/zone/objects/creature/CreatureObject.h"

class CharacterNameMap : public Object {
	HashTable<String, uint64> names;
	ReadWriteLock guard;

public:
	CharacterNameMap() : names(3000) {
	}

	void put(CreatureObject* player) {
		Locker locker(&guard);

		names.put(player->getFirstName().toLowerCase(), player->getObjectID());
	}

	bool put(const String& name, uint64 oid) {
		Locker locker(&guard);

		if (names.put(name, oid) != names.getNullValue())
			return false;

		return true;
	}

	void remove(const String& name) {
		Locker locker(&guard);

		names.remove(name.toLowerCase());
	}

	uint64& get(const String& name) {
		ReadLocker locker(&guard);

		return names.get(name);
	}

	bool containsKey(const String& name) {
		ReadLocker locker(&guard);

		return names.containsKey(name);
	}

	int size() {
		return names.size();
	}
};

#endif /* CHARACTERNAMEMAP_H_ */
