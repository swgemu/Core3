#include "server/zone/objects/creature/CreatureObject.h"
#include "PlayerMap.h"

PlayerMap::PlayerMap(int initsize) : Mutex("PlayerMap"), players(initsize), iter(&players) {
}

void PlayerMap::put(const String& name, CreatureObject* player, bool doLock) {
	lock(doLock);

	try {
		players.put(name.toLowerCase(), player);
	}
	catch (Exception & e) {
		System::out << e.getMessage();
		e.printStackTrace();
	}
	catch (...) {
		unlock(doLock);

		throw;
	}

	unlock(doLock);
}

CreatureObject* PlayerMap::get(const String& name, bool doLock ) {
	CreatureObject* player = nullptr;

	lock(doLock);

	try {

		player = players.get(name.toLowerCase());

	}
	catch (Exception & e) {
		System::out << e.getMessage();
		e.printStackTrace();
	}
	catch (...) {
		unlock(doLock);

		throw;
	}

	unlock(doLock);

	return player;
}

CreatureObject* PlayerMap::remove(const String& name, bool doLock) {
	CreatureObject* player = nullptr;

	lock(doLock);

	try {

		player = players.remove(name.toLowerCase());

	}
	catch (Exception & e) {
		System::out << e.getMessage();
		e.printStackTrace();
	}
	catch (...) {
		unlock(doLock);

		throw;
	}

	unlock(doLock);

	return player;
}

CreatureObject* PlayerMap::getNextValue(bool doLock ) {
	CreatureObject* player = nullptr;

	lock(doLock);

	player = iter.getNextValue();

	unlock(doLock);

	return player;
}

CreatureObject* PlayerMap::next(bool doLock) {
	return getNextValue(doLock);
}

bool PlayerMap::hasNext(bool doLock) {
	bool res = false;

	lock(doLock);

	res = iter.hasNext();

	unlock(doLock);

	return res;
}

void PlayerMap::resetIterator(bool doLock) {
	lock(doLock);

	iter.resetIterator();

	unlock(doLock);
}

int PlayerMap::size(bool doLock) {
	lock(doLock);

	int res = players.size();

	unlock(doLock);

	return res;
}