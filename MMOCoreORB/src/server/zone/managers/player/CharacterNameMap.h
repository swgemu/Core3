/*
 * CharacterNameMap.h
 *
 *  Created on: 03/02/2010
 *      Author: victor
 */

#ifndef CHARACTERNAMEMAP_H_
#define CHARACTERNAMEMAP_H_

#include "engine/engine.h"
#include "server/zone/objects/player/PlayerCreature.h"

class CharacterNameMap : public Object {
	HashTable<String, uint64> hashTable;
public:
	CharacterNameMap() {

	}

	void put(PlayerCreature* player) {
		hashTable.put(player->getFirstName().toLowerCase(), player->getObjectID());
	}

	void put(const String& name, uint64 oid) {
		hashTable.put(name, oid);
	}

	uint64 get(const String& key) {
		return hashTable.get(key);
	}

	bool containsKey(const String& key) {
		return hashTable.containsKey(key);
	}

	int size() {
		return hashTable.size();
	}


};

#endif /* CHARACTERNAMEMAP_H_ */
