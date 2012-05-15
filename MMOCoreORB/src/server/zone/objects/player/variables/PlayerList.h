/*
 * PlayerList.h
 *
 *  Created on: 05/02/2010
 *      Author: victor
 */

#ifndef PLAYERLIST_H_
#define PLAYERLIST_H_

#include "server/zone/objects/scene/SceneObject.h"

template <int DeltaUpdate>
class PlayerList : public DeltaVector<String> {

public:
	const static int MAXSIZE = 100;

public:

	PlayerList() {

	}

	PlayerList(const PlayerList& list) : Object(), DeltaVector<String>(list) {

	}

	bool addPlayer(const String& player) {
		String lowerCase = player.toLowerCase();

		if (contains(lowerCase))
			return false;

		add(lowerCase);

		return true;
	}

	bool removePlayer(const String& player) {
		String lowerCase = player.toLowerCase();

		int idx = find(lowerCase);

		if (idx == -1)
			return false;

		remove(idx);

		return true;
	}

	void insertToDeltaMessage(DeltaMessage* delta) {
		delta->startUpdate(DeltaUpdate);
		delta->insertInt(size() + 1);
		delta->insertInt(updateCounter += size() + 1);
		delta->insertByte(3);

		delta->insertShort(size());

		for (int i = 0; i < size(); ++i)
			delta->insertAscii(get(i));
	}


	void insertToListMessage(Message* message) {
		message->insertInt(size());

		for (int i = 0; i < size(); ++i) {
			message->insertAscii("SWG");
			message->insertAscii("Core3");
			message->insertAscii(get(i));
		}
	}

	inline bool canAddMorePlayers() {
		return size() < MAXSIZE;
	}

};

#endif /* PLAYERLIST_H_ */
