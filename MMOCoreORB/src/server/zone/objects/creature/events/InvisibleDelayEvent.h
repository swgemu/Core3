/*
 				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

/**
 * file InvisibleDelayEvent.h
 * author Polonel
 * date 10.01.2010
 */

#ifndef INVISIBLEDELAYEVENT_H_
#define INVISIBLEDELAYEVENT_H_

#include "engine/engine.h"
#include "server/zone/managers/objectcontroller/ObjectController.h"
#include "server/zone/packets/chat/ChatSystemMessage.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/packets/tangible/UpdatePVPStatusMessage.h"

class InvisibleDelayEvent: public Task {
	ManagedReference<CreatureObject*> player;

public:
	InvisibleDelayEvent(CreatureObject* pl) {
		player = pl;
	}

	void run() {
		Locker playerLocker(player);

		PlayerObject* targetGhost = player->getPlayerObject();

		try {
			if (player->isOnline() && !targetGhost->isLoggingOut()) {
				player->removePendingTask("invisibledelayevent");

				ManagedReference<Zone*> zone = player->getZone();

				if (zone == NULL)
					return;

				player->switchZone(zone->getZoneName(), player->getPositionX(), player->getPositionZ(), player->getPositionY(), player->getParentID(), true);

				if (player->isInvisible()) {
					player->sendSystemMessage("You are now invisible to other players and creatures.");

				} else {
					player->sendSystemMessage("You are now visible to all players and creatures.");
				}

			}

		} catch (Exception& e) {
			player->error("unreported exception caught in InvisibleDelayEvent::run");
		}

	}

};

#endif /* INVISIBLEDELAYEVENT_H_ */
