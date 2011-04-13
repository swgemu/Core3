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

class CharacterNameMap : public HashTable<String, uint64> {
public:
	CharacterNameMap() : HashTable<String, uint64>(3000) {

	}

	void put(PlayerCreature* player) {
		HashTable<String, uint64>::put(player->getFirstName().toLowerCase(), player->getObjectID());
	}

	void put(const String& name, uint64 oid) {
		HashTable<String, uint64>::put(name, oid);
	}
};

#endif /* CHARACTERNAMEMAP_H_ */
