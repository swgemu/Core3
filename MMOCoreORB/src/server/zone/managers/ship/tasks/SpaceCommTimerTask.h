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
	SpaceCommTimerTask(SceneObject* player, uint64 oid, int length) : Task() {

		playerObject = player;
		shipID = oid;
		convoLength = length;

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

		ManagedReference<Facade*> session = playerSCNO->getActiveSession(SessionFacadeType::CONVERSATION);

		Locker _lock(playerSCNO);

		if (convoLength != 0 && session != nullptr) {
			reschedule(convoLength);
			convoLength -= convoLength;
		} else {
			if (session == nullptr) {
			playerSCNO->dropActiveSession(SessionFacadeType::CONVERSATION);
				return;
			} else {
				playerSCNO->sendMessage(new StopNpcConversation(creature, shipID));
			}
		}

	}
};

#endif /* SPACECOMMTIMERTASK_H_ */
