/*
 * SpaceCommTimerTask.h
 *
 *  Created on: Jan 31, 2023
 *      Author: Phoenix
 */

#ifndef SPACECOMMTIMERTASK_H_
#define SPACECOMMTIMERTASK_H_

#include "server/zone/Zone.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/packets/object/StopNpcConversation.h"


class SpaceCommTimerTask : public Task, public Logger {
	ManagedWeakReference<SceneObject*> playerObject;
    uint64 shipID;

protected:
    int convoLength;

public:
	SpaceCommTimerTask(SceneObject* player, uint64 oid) : Task() {

		playerObject = player;
        shipID = oid;

        convoLength = 10000;

		Logger::setLoggingName("SpaceCommTimerTask");
	}

	void run() {
		SceneObject* playerSCNO = playerObject.get();

        CreatureObject* creature = playerSCNO->asCreatureObject();

		if (playerSCNO == nullptr) {
			error() << " run() - player strongReference has a nullptr.";
			return;
		}

		ZoneServer* zoneServer = playerSCNO->getZoneServer();

		if (zoneServer != nullptr && zoneServer->isServerShuttingDown()) {
			cancel();
			return;
		}

		Locker _lock(playerSCNO);

        if (convoLength > 0) {
            convoLength -= 1000;
		    reschedule(1000);
        } else {
            playerSCNO->sendMessage(new StopNpcConversation(creature, shipID));
        }

	}
};

#endif /* SPACECOMMTIMERTASK_H_ */
