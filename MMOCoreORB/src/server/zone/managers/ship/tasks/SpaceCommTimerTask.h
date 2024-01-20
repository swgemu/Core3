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
#include "server/zone/objects/player/sessions/ConversationSession.h"


class SpaceCommTimerTask : public Task, public Logger {
	ManagedWeakReference<CreatureObject*> play;
	uint64 shipID;

protected:
	int convoLength;

public:
	SpaceCommTimerTask(CreatureObject* playerCreo, uint64 oid) : Task() {
		play = playerCreo;
		shipID = oid;

		Logger::setLoggingName("SpaceCommTimerTask");
	}

	void run() {
		auto player = play.get();

		if (player == nullptr) {
			return;
		}

		ZoneServer* zoneServer = player->getZoneServer();

		if (zoneServer != nullptr && zoneServer->isServerShuttingDown()) {
			cancel();
			return;
		}

		Locker lock(player);

		player->executeObjectControllerAction(STRING_HASHCODE("npcconversationstop"), shipID, "");
	}
};

#endif /* SPACECOMMTIMERTASK_H_ */
