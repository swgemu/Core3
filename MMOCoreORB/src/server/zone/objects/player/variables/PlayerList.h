/*
 * PlayerList.h
 *
 *  Created on: 05/02/2010
 *      Author: victor
 */

#ifndef PLAYERLIST_H_
#define PLAYERLIST_H_

#include "engine/util/json_utils.h"

#include "server/zone/objects/scene/variables/DeltaVector.h"

template <int DeltaUpdate>
class PlayerList : public DeltaVector<String> {

public:
	const static int MAXSIZE = 100;

public:

	PlayerList() {

	}

	PlayerList(const PlayerList& list) : DeltaVector<String>(list) {

	}

	PlayerList& operator=(const PlayerList& list) {
		if (this == &list) {
			return *this;
		}

		DeltaVector<String>::operator=(list);

		return *this;
	}

	friend void to_json(nlohmann::json& j, const PlayerList& l) {
		const DeltaVector<String>& dv = l;

		to_json(j, dv);
	}

	bool addPlayer(const String& player) {
		Locker locker(getLock());

		String lowerCase = player.toLowerCase();

		if (contains(lowerCase))
			return false;

		add(lowerCase);

		return true;
	}

	bool removePlayer(const String& player) {
		Locker locker(getLock());

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


	void insertToListMessage(Message* message) const {
		message->insertInt(size());

		for (int i = 0; i < size(); ++i) {
			message->insertAscii("SWG");
			message->insertAscii("Core3");
			message->insertAscii(get(i));
		}
	}

	inline bool canAddMorePlayers() const {
		return size() < MAXSIZE;
	}

};

#endif /* PLAYERLIST_H_ */
