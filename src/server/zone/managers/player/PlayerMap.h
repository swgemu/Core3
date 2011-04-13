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

#ifndef PLAYERMAP_H_
#define PLAYERMAP_H_

#include "system/lang.h"

//#include "PlayerMap.h"

//#include "../../objects/player/PlayerCreature.h"

namespace server {
namespace zone {
namespace managers {
namespace player {

class PlayerMap : private HashTable<String, ManagedReference<PlayerCreature*> >, private HashTableIterator<String, ManagedReference<PlayerCreature*> >, public Mutex {
public:
	PlayerMap(int initsize) : HashTable<String, ManagedReference<PlayerCreature*> >(initsize), HashTableIterator<String, ManagedReference<PlayerCreature*> >(this), Mutex("PlayerMap") {
		setNullValue(NULL);
	}

	PlayerCreature* put(const String& name, PlayerCreature* player, bool doLock = true) {
		PlayerCreature* play = NULL;

		lock(doLock);

		try {

			play = HashTable<String, ManagedReference<PlayerCreature*> >::put(name.toLowerCase(), player);

		} catch (Exception& e) {
			System::out << e.getMessage();
			e.printStackTrace();
		} catch (...) {
			System::out << "unreported exception caught in PlayerMap::put";

			unlock(doLock);

			throw;
		}

		unlock(doLock);

		return play;
	}

	PlayerCreature* get(const String& name, bool doLock = true) {
		PlayerCreature* player = NULL;

		lock(doLock);

		try {

			player = HashTable<String, ManagedReference<PlayerCreature*> >::get(name.toLowerCase());

		} catch (Exception& e) {
			System::out << e.getMessage();
			e.printStackTrace();
		} catch (...) {
			System::out << "unreported exception caught in PlayerMapImpl::get";

			unlock(doLock);

			throw;
		}

		unlock(doLock);

		return player;
	}

	PlayerCreature* remove(const String& name, bool doLock = true) {
		PlayerCreature* player = NULL;

		lock(doLock);

		try {

			player = HashTable<String, ManagedReference<PlayerCreature*> >::remove(name.toLowerCase());

		} catch (Exception& e) {
			System::out << e.getMessage();
			e.printStackTrace();
		} catch (...) {
			System::out << "unreported exception caught in PlayerMapImpl::remove";

			unlock(doLock);

			throw;
		}

		unlock(doLock);

		return player;
	}

	PlayerCreature* getNextValue(bool doLock = true) {
		PlayerCreature* player = NULL;

		lock(doLock);

		player = HashTableIterator<String, ManagedReference<PlayerCreature*> >::getNextValue();

		unlock(doLock);

		return player;
	}

	PlayerCreature* next(bool doLock = true) {
		return getNextValue(doLock);
	}

	bool hasNext(bool doLock = true) {
		bool res = false;

		lock(doLock);

		res = HashTableIterator<String, ManagedReference<PlayerCreature*> >::hasNext();

		unlock(doLock);

		return res;
	}

	void resetIterator(bool doLock = true) {
		lock(doLock);

		HashTableIterator<String, ManagedReference<PlayerCreature*> >::resetIterator();

		unlock(doLock);
	}

	int size(bool doLock = true) {
		lock(doLock);

		int res = HashTable<String, ManagedReference<PlayerCreature*> >::size();

		unlock(doLock);

		return res;
	}

};


}
}
}
}

using namespace server::zone::managers::player;


#endif /*PLAYERMAPIMPLEMENTATION_H_*/
