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

class Player;

#include "PlayerMap.h"

class PlayerMapImplementation : public PlayerMapServant, private HashTable<string, Player*>, private HashTableIterator<string, Player*>, public Mutex {
	int hash(const string& key) {
        return String::hashCode(key);
	}

public:
	PlayerMapImplementation(int initsize) : PlayerMapServant(), HashTable<string, Player*>(initsize), HashTableIterator<string, Player*>(this), Mutex("PlayerMap") {
		setNullValue(NULL);
	}

	Player* put(string name, Player* player, bool doLock = true) {
		Player* play = NULL;
		String::toLower(name);

		lock(doLock);

		play = HashTable<string, Player*>::put(name, player);

		unlock(doLock);

		return play;
	}

	Player* get(string name, bool doLock = true) {
		Player* player = NULL;
		String::toLower(name);

		lock(doLock);

		player = HashTable<string, Player*>::get(name);

		unlock(doLock);

		return player;
	}

	Player* remove(string name, bool doLock = true) {
		Player* player = NULL;
		String::toLower(name);

		lock(doLock);

		player = HashTable<string, Player*>::remove(name);

		unlock(doLock);

		return player;
	}

	Player* getNextValue(bool doLock = true) {
		Player* player = NULL;

		lock(doLock);

		player = HashTableIterator<string, Player*>::getNextValue();

		unlock(doLock);

		return player;
	}

	Player* next(bool doLock = true) {
		return getNextValue(doLock);
	}

	bool hasNext(bool doLock = true) {
		bool res = false;

		lock(doLock);

		res = HashTableIterator<string, Player*>::hasNext();

		unlock(doLock);

		return res;
	}

	void resetIterator(bool doLock = true) {
		lock(doLock);

		HashTableIterator<string, Player*>::resetIterator();

		unlock(doLock);
	}

	int size(bool doLock = true) {
		lock(doLock);

		int res = HashTable<string, Player*>::size();

		unlock(doLock);

		return res;
	}

};

#endif /*PLAYERMAPIMPLEMENTATION_H_*/
