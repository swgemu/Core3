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
