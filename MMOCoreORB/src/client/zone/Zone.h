/*
 				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef ZONE_H_
#define ZONE_H_

#include "ZoneClient.h"
#include "client/zone/ZoneClientThread.h"
#include "engine/util/JSONSerializationType.h"

class ObjectController;
class ObjectManager;
class SceneObject;

class Zone : public Thread, public Mutex, public Logger {
	uint32 accountID;
	String sessionID;
	String galaxyAddress;
	uint32 galaxyPort;

	Reference<ZoneClient*> client;
	ZoneClientThread* clientThread;

	ObjectController* objectController;

	Condition characterCreatedCondition;
	Condition sceneReadyCondition;

	ObjectManager* objectManager;

	Time startTime;
	bool started;
	bool sceneReady;

	// Character creation state
	bool characterCreated;
	bool characterCreationFailed;
	uint64 createdCharacterOID;

	// Client permissions from server
	bool canLogin;
	bool canCreateRegularCharacter;
	bool canCreateJediCharacter;
	bool canSkipTutorial;

	String lastError;
	uint16 lastErrorCode;

public:
	Zone(uint32 account, const String& sessionID, const String& galaxyAddress, uint32 galaxyPort);
	~Zone();

	void run();

	void disconnect() {
		if (client != nullptr) {
			client->disconnect();
			clientThread = nullptr;
		}
	}

	void setSceneStarted() {
		info(true) << __FUNCTION__ << " in " << startTime.miliDifference() << "ms";
	}

	void setSceneReady() {
		Locker locker(this);

		info(true) << __FUNCTION__ << " in " << startTime.miliDifference() << "ms";
		sceneReady = true;

		sceneReadyCondition.signal(this);
	}

	bool waitForSceneReady(int timeoutMs) {
		Locker locker(this);

		if (sceneReady) {
			return true;
		}

		Time timeout;
		timeout.addMiliTime(timeoutMs);
		bool success = !sceneReadyCondition.timedWait(this, &timeout);

		return success && sceneReady;
	}

	SceneObject* getObject(uint64 objid);

	inline const String& getGalaxyAddress() {
		return galaxyAddress;
	}

	inline uint32 getGalaxyPort() {
		return galaxyPort;
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

	bool isStarted() {
		return started;
	}

	bool isSceneReady() {
		return sceneReady;
	}

	void setCharacterCreated(uint64 oid) {
		characterCreated = true;
		createdCharacterOID = oid;
	}

	void setCharacterCreationFailed() {
		characterCreationFailed = true;
	}

	bool isCharacterCreated() const {
		return characterCreated;
	}

	bool hasCharacterCreationFailed() const {
		return characterCreationFailed;
	}

	uint64 getCreatedCharacterOID() const {
		return createdCharacterOID;
	}

	void setPermissions(bool login, bool createRegular, bool createJedi, bool skipTutorial) {
		canLogin = login;
		canCreateRegularCharacter = createRegular;
		canCreateJediCharacter = createJedi;
		canSkipTutorial = skipTutorial;
	}

	bool getCanLogin() const {
		return canLogin;
	}

	bool getCanCreateCharacter() const {
		return canCreateRegularCharacter;
	}

	bool getCanCreateJedi() const {
		return canCreateJediCharacter;
	}

	bool getCanSkipTutorial() const {
		return canSkipTutorial;
	}

	bool isConnected() const {
		return client != nullptr && client->getClient() != nullptr && client->getClient()->isAvailable();
	}

	const String& getLastError() const {
		return lastError;
	}

	uint16 getLastErrorCode() const {
		return lastErrorCode;
	}

	void setError(const String& msg, uint16 code) {
		lastError = msg;
		lastErrorCode = code;
	}

	void clearError() {
		lastError = "";
		lastErrorCode = 0;
	}

	JSONSerializationType collectStats();
};

#endif /* ZONE_H_ */
