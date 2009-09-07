/*
 * LoginSession.h
 *
 *  Created on: Sep 6, 2009
 *      Author: theanswer
 */

#ifndef LOGINSESSION_H_
#define LOGINSESSION_H_

#include "engine/engine.h"

class LoginSession : public Mutex, public Runnable, public Logger {
	Condition sessionFinalized;

	uint32 accountID;

	Vector<uint64> characterObjectIds;
	uint32 selectedCharacter;

	int instance;

public:
	LoginSession(int instance);

	void run();

	void addCharacter(uint64 objectID) {
		characterObjectIds.add(objectID);
	}

	void setSelectedCharacter(uint32 id) {
		lock();

		selectedCharacter = id;

		sessionFinalized.signal(this);

		unlock();
	}

	void setAccountID(uint32 id) {
		accountID = id;
	}

	uint32 getAccountID() {
		return accountID;
	}

	uint32 getSelectedCharacter() {
		return selectedCharacter;
	}

	uint64 getCharacterObjectID(uint32 id) {
		return characterObjectIds.get(id);
	}
};


#endif /* LOGINSESSION_H_ */
