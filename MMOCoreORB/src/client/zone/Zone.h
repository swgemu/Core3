/*
 				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef ZONE_H_
#define ZONE_H_

#include "engine/engine.h"

#include "ZoneClient.h"

#include "objects/player/PlayerCreature.h"
#include "objects/ObjectMap.h"

class LoginSession;
class ZoneClientThread;
class ObjectController;
class ObjectManager;

class Zone : public Thread, public Mutex, public Logger {
	//LoginSession* loginSession;

	//ObjectMap objectMap;

	uint64 characterID;
	uint32 accountID;
	uint32 sessionID;

	Reference<ZoneClient*> client;
	ZoneClientThread* clientThread;

	Reference<PlayerCreature*> player;

	ObjectController* objectController;

	Condition characterCreatedCondition;

	Vector<PlayerCreature*> playerArray;

	ObjectManager* objectManager;

	int instance;

	Time startTime;
	bool started;

public:
	Zone(int instance, uint64 characterObjectID, uint32 account, uint32 session);
	~Zone();

	static int createdChar;

	void run();
	//void initConnection();

	void disconnect();

	void sceneStarted();

	void follow(const String& name);
	void stopFollow();

	void lurk();

	bool doCommand(const String& command, const String& arguments);

	//LocalPlayer* createLocalPlayer(uint64 pid);

	void insertPlayer();
	void insertPlayer(PlayerCreature* player);

	//void waitFor();

	/*inline void addEvent(Event* event, uint64 time) {
		scheduler->addEvent(event, time);
	}*/

	PlayerCreature* getSelfPlayer();

	bool isSelfPlayer(SceneObject* pl) {
		if (characterID == 0)
			return false;

		return pl->getObjectID() == characterID;
	}

	bool hasSelfPlayer() {
		return characterID != 0;
	}

	SceneObject* getObject(uint64 objid);

	void setCharacterID(uint64 val) {
		lock();

		characterID = val;

		characterCreatedCondition.signal(this);
		unlock();
	}

	inline uint64 getCharacterID() {
		return characterID;
	}

	inline ZoneClient* getZoneClient() {
		return client;
	}

	inline ObjectManager* getObjectManager() {
		return objectManager;
	}

	inline ObjectController* getObjectController() {
		return objectController;
	}

	Vector<PlayerCreature*>* getNotInitiatedPlayers() {
		return &playerArray;
	}

	bool isStarted() {
		return started;
	}
};

#endif /* ZONE_H_ */
