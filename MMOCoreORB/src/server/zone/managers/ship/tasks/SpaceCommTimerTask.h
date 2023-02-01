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
	ManagedWeakReference<CreatureObject*> creo;
	uint64 shipID;

protected:
	int convoLength;

public:
	SpaceCommTimerTask(CreatureObject* player, uint64 oid, int length) : Task() {

		creo = player;
		shipID = oid;
		convoLength = length;

		Logger::setLoggingName("SpaceCommTimerTask");
	}

	void run() {

		CreatureObject* creature = creo.get();

		if (creature == nullptr) {
			error() << " run() - creature strongReference has a nullptr.";
			return;
		}

		ZoneServer* zoneServer = creature->getZoneServer();

		if (zoneServer != nullptr && zoneServer->isServerShuttingDown()) {
			cancel();
			return;
		}

		ManagedReference<ConversationSession*> session = creature->getActiveSession(SessionFacadeType::CONVERSATION).castTo<ConversationSession*>();

		Locker _lock(creature);

		if (convoLength != 0 && session != nullptr) {
			reschedule(convoLength);
			convoLength -= convoLength;
		} else {
			if (session == nullptr) {
				return;
			} else {
				creature->dropActiveSession(SessionFacadeType::CONVERSATION);
				creature->sendMessage(new StopNpcConversation(creature, shipID));
			}
		}

	}
};

#endif /* SPACECOMMTIMERTASK_H_ */
