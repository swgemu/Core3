/*
 * LoginSession.h
 *
 *  Created on: Sep 6, 2009
 *      Author: theanswer
 */

#ifndef LOGINSESSION_H_
#define LOGINSESSION_H_

#include "system/lang.h"
#include "engine/log/Logger.h"
#include "server/login/objects/GalaxyList.h"
#include "server/login/objects/CharacterListEntry.h"

class LoginClient;

class LoginSession : public Mutex, public Runnable, public Logger, public Object {
	Condition sessionFinalized;

	uint32 accountID;
	String sessionID;
	String username;
	String password;

	Vector<CharacterListEntry> characters;

	int instance;

	class LoginClientThread* loginThread;

	Reference<LoginClient*> login;

	VectorMap<uint32, Galaxy> galaxies;

public:
	LoginSession(int instance, const String& username, const String& password);

	~LoginSession();

	void run();

	void addCharacter(const CharacterListEntry& entry) {
		characters.add(entry);
	}

	void signalCompletion() {
		lock();
		sessionFinalized.signal(this);
		unlock();
	}

	void setAccountID(uint32 id) {
		accountID = id;
	}

	void setSessionID(const String& sessionID) {
		this->sessionID = sessionID;
	}

	uint32 getAccountID() {
		return accountID;
	}

	const String& getSessionID() {
		return sessionID;
	}

	const CharacterListEntry& getCharacterByOID(uint32 id) {
		return characters.get(id);
	}

	const CharacterListEntry& getCharacterByIndex(int index) {
		return characters.get(index);
	}

	uint32 getCharacterListSize() {
		return characters.size();
	}

	Galaxy& getGalaxy(uint32 galaxyId) {
		if (!galaxies.contains(galaxyId)) {
			galaxies.put(galaxyId, Galaxy(galaxyId));
		}

		return galaxies.get(galaxyId);
	}
};


#endif /* LOGINSESSION_H_ */
