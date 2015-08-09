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
#include "server/zone/templates/tangible/PlayerCreatureTemplate.h"

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

				PlayerCreatureTemplate* playerTemplate = dynamic_cast<PlayerCreatureTemplate*>(player->getObjectTemplate());

				if (playerTemplate == NULL)
					return;

				ManagedReference<ImageDesignSession*> session = player->getActiveSession(SessionFacadeType::IMAGEDESIGN).castTo<ImageDesignSession*>();

				if (session != NULL) {
					session->sessionTimeout();
				}

				float height = player->getHeight();

				if (!player->isInvisible()) {
					if (playerTemplate->getMinScale() <= height) {
						player->setHeight(height * 0.25f);
					}

					player->sendSystemMessage("You are now invisible to other players and creatures.");

				} else {
					if (playerTemplate->getMinScale() > height) {
						player->setHeight(height * 4.0f);
					}

					player->sendSystemMessage("You are now visible to all players and creatures.");
				}

				player->switchZone(zone->getZoneName(), player->getPositionX(), player->getPositionZ(), player->getPositionY(), player->getParentID(), true);
			}

		} catch (Exception& e) {
			player->error("unreported exception caught in InvisibleDelayEvent::run");
		}

	}

};

#endif /* INVISIBLEDELAYEVENT_H_ */
