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
	MissionAbortCallback(ObjectControllerMessageCallback* objectControllerCallback) :
		MessageCallback(objectControllerCallback->getClient(), objectControllerCallback->getServer()),
		missionObjectID(0), objectControllerMain(objectControllerCallback) {

	}

	void parse(Message* message) {
		//System::out << message->toStringData() << endl;
		message->parseInt();
		missionObjectID = message->parseLong();

	}

	void run() {
		ManagedReference<CreatureObject*> player = client->getPlayer();

		if (player == NULL)
			return;

		ManagedReference<SceneObject*> mission = server->getZoneServer()->getObject(missionObjectID);

		if (mission == NULL)
			return;

		if (!mission->isMissionObject())
			return;

		MissionObject* missionObject = cast<MissionObject*>( mission.get());

		MissionManager* manager = server->getZoneServer()->getMissionManager();
		manager->handleMissionAbort(missionObject, player);

		// MissionAbortResponse
		ObjectControllerMessage* mar = new ObjectControllerMessage(player->getObjectID(), 0x0B, 0x142);
		mar->insertLong(missionObject->getObjectID());
		player->sendMessage(mar);
	}
};


#endif /* MISSIONABORTCALLBACK_H_ */
