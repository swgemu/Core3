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

				Locker zoneLocker(zone);

				if (!player->isInvisible()) {

					SortedVector<ManagedReference<QuadTreeEntry*> >* closeObjects = player->getCloseObjects();

					for (int i = 0; i < closeObjects->size(); ++i) {
						SceneObject* scno = cast<SceneObject*>( closeObjects->get(i).get());

						if (scno != player && !scno->isBuildingObject())
								scno->notifyDissapear(player);

					}

					player->setInvisible(true);

					player->sendSystemMessage("You are now invisible to other players and creatures.");

				} else {
					player->setInvisible(false);

					SortedVector<ManagedReference<QuadTreeEntry*> >* closeObjects = player->getCloseObjects();

					for (int i = 0; i < closeObjects->size(); ++i) {
						SceneObject* scno = cast<SceneObject*>( closeObjects->get(i).get());

						if (scno != player && !scno->isBuildingObject())
								scno->notifyInsert(player);

					}

					player->sendSystemMessage("You are now visible to all players and creatures.");

				}

				UpdatePVPStatusMessage* mess = new UpdatePVPStatusMessage(player, player->getPvpStatusBitmask());
				player->broadcastMessage(mess, true, false);

			}

		} catch (Exception& e) {
			player->error("unreported exception caught in InvisibleDelayEvent::activate");
		}

	}

};

#endif /* INVISIBLEDELAYEVENT_H_ */
