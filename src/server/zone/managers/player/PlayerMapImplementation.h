/*
Copyright (C) 2007 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.
*/

#ifndef PLAYERMAPIMPLEMENTATION_H_
#define PLAYERMAPIMPLEMENTATION_H_

#include "system/lang.h"

#include "PlayerMap.h"

#include "../../objects/player/Player.h"

class PlayerMapImplementation : public PlayerMapServant, private HashTable<String, Player*>, private HashTableIterator<String, Player*>, public Mutex {
	int hash(const String& key) {
        return key.hashCode();
	}

public:
	PlayerMapImplementation(int initsize) : PlayerMapServant(), HashTable<String, Player*>(initsize), HashTableIterator<String, Player*>(this), Mutex("PlayerMap") {
		setNullValue(NULL);
	}

	Player* put(const String& name, Player* player, bool doLock = true) {
		Player* play = NULL;

		lock(doLock);

		play = HashTable<String, Player*>::put(name.toLowerCase(), player);

		if (play == NULL)
			player->acquire();

		unlock(doLock);

		return play;
	}

	Player* get(const String& name, bool doLock = true) {
		Player* player = NULL;

		lock(doLock);

		player = HashTable<String, Player*>::get(name.toLowerCase());

		unlock(doLock);

		return player;
	}

	Player* remove(const String& name, bool doLock = true) {
		Player* player = NULL;

		lock(doLock);

		player = HashTable<String, Player*>::remove(name.toLowerCase());

		if (player != NULL)
			player->release();

		unlock(doLock);

		return player;
	}

	Player* getNextValue(bool doLock = true) {
		Player* player = NULL;

		lock(doLock);

		player = HashTableIterator<String, Player*>::getNextValue();

		unlock(doLock);

		return player;
	}

	Player* next(bool doLock = true) {
		return getNextValue(doLock);
	}

	bool hasNext(bool doLock = true) {
		bool res = false;

		lock(doLock);

		res = HashTableIterator<String, Player*>::hasNext();

		unlock(doLock);

		return res;
	}

	void resetIterator(bool doLock = true) {
		lock(doLock);

		HashTableIterator<String, Player*>::resetIterator();

		unlock(doLock);
	}

	int size(bool doLock = true) {
		lock(doLock);

		int res = HashTable<String, Player*>::size();

		unlock(doLock);

		return res;
	}

};

#endif /*PLAYERMAPIMPLEMENTATION_H_*/
