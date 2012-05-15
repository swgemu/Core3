/*
 * FriendList.h
 *
 *  Created on: 05/02/2010
 *      Author: victor
 */

#ifndef FRIENDLIST_H_
#define FRIENDLIST_H_

#include "PlayerList.h"

class FriendList : public PlayerList<7> {
protected:
	Vector<String> reverseTable;

public:
	FriendList() {
		addSerializableVariable("reverseTable", &reverseTable);
	}

	FriendList(const FriendList& list) : Object(), PlayerList<7>(list) {
		reverseTable = list.reverseTable;

		addSerializableVariable("reverseTable", &reverseTable);
	}

	void addReversePlayer(const String& name) {
		String low = name.toLowerCase();

		int idx = -1;

		for (int i = 0; i < reverseTable.size(); ++i) {
			if (low == reverseTable.get(i)) {
				idx = i;
				break;
			}
		}

		if (idx == -1)
			reverseTable.add(low);
	}

	void removeReversePlayer(const String& name) {
		String low = name.toLowerCase();

		int idx = -1;

		for (int i = 0; i < reverseTable.size(); ++i) {
			if (low == reverseTable.get(i)) {
				idx = i;
				break;
			}
		}

		if (idx != -1)
			reverseTable.remove(idx);
	}

	Vector<String>* getReverseTable() {
		return &reverseTable;
	}

};

#endif /* FRIENDLIST_H_ */
