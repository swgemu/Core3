/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef PLAYERMAP_H_
#define PLAYERMAP_H_

namespace server {
namespace zone {
namespace managers {
namespace player {

class PlayerMap : public Mutex, public Object {
	HashTable<String, ManagedReference<CreatureObject*> > players;
	HashTableIterator<String, ManagedReference<CreatureObject*> > iter;

public:
	PlayerMap(int initsize) : Mutex("PlayerMap"), players(initsize), iter(&players) {
	}

	void put(const String& name, CreatureObject* player, bool doLock = true) {
		lock(doLock);

		try {
			players.put(name.toLowerCase(), player);
		} catch (Exception& e) {
			System::out << e.getMessage();
			e.printStackTrace();
		} catch (...) {
			unlock(doLock);

			throw;
		}

		unlock(doLock);
	}

	CreatureObject* get(const String& name, bool doLock = true) {
		CreatureObject* player = NULL;

		lock(doLock);

		try {

			player = players.get(name.toLowerCase());

		} catch (Exception& e) {
			System::out << e.getMessage();
			e.printStackTrace();
		} catch (...) {
			unlock(doLock);

			throw;
		}

		unlock(doLock);

		return player;
	}

	CreatureObject* remove(const String& name, bool doLock = true) {
		CreatureObject* player = NULL;

		lock(doLock);

		try {

			player = players.remove(name.toLowerCase());

		} catch (Exception& e) {
			System::out << e.getMessage();
			e.printStackTrace();
		} catch (...) {
			unlock(doLock);

			throw;
		}

		unlock(doLock);

		return player;
	}

	CreatureObject* getNextValue(bool doLock = true) {
		CreatureObject* player = NULL;

		lock(doLock);

		player = iter.getNextValue();

		unlock(doLock);

		return player;
	}

	CreatureObject* next(bool doLock = true) {
		return getNextValue(doLock);
	}

	bool hasNext(bool doLock = true) {
		bool res = false;

		lock(doLock);

		res = iter.hasNext();

		unlock(doLock);

		return res;
	}

	void resetIterator(bool doLock = true) {
		lock(doLock);

		iter.resetIterator();

		unlock(doLock);
	}

	int size(bool doLock = true) {
		lock(doLock);

		int res = players.size();

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
