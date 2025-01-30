/*
 * MissionAbortCallback.h
 *
 *  Created on: 22/06/2010
 *      Author: victor
 */

#ifndef MISSIONABORTCALLBACK_H_
#define MISSIONABORTCALLBACK_H_

#include "server/zone/objects/creature/CreatureObject.h"
#include "ObjectControllerMessageCallback.h"
#include "server/zone/managers/mission/MissionManager.h"
#include "server/zone/objects/mission/MissionObject.h"

class MissionAbortCallback : public MessageCallback {
	uint64 missionObjectID;

	ObjectControllerMessageCallback* objectControllerMain;

public:
	MissionAbortCallback(ObjectControllerMessageCallback* objectControllerCallback) : MessageCallback(objectControllerCallback->getClient(), objectControllerCallback->getServer()), missionObjectID(0), objectControllerMain(objectControllerCallback) {
	}

	void parse(Message* message) {
		// System::out << message->toStringData() << endl;
		message->parseInt();
		missionObjectID = message->parseLong();
	}

	void run() {
		ManagedReference<CreatureObject*> player = client->getPlayer();

		if (player == nullptr) {
			return;
		}

		auto zoneServer = player->getZoneServer();

		if (zoneServer == nullptr) {
			return;
		}

		ManagedReference<SceneObject*> mission = zoneServer->getObject(missionObjectID);

		if (mission == nullptr) {
			return;
		}

		if (!mission->isMissionObject()) {
			return;
		}

		MissionObject* missionObject = cast<MissionObject*>(mission.get());

		if (missionObject == nullptr) {
			return;
		}

		MissionManager* missionMan = zoneServer->getMissionManager();

		if (missionMan == nullptr) {
			return;
		}

		Locker lock(player);
		Locker clock(missionObject, player);

		missionMan->handleMissionAbort(missionObject, player, true);

		// MissionAbortResponse
		ObjectControllerMessage* abortResponse = new ObjectControllerMessage(player->getObjectID(), 0x0B, 0x142);

		if (abortResponse != nullptr) {
			abortResponse->insertLong(missionObject->getObjectID());
			player->sendMessage(abortResponse);
		}
	}
};

#endif /* MISSIONABORTCALLBACK_H_ */
