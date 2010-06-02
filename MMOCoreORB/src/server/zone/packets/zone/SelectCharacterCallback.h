/*
 * SelectCharacterCallback.h
 *
 *  Created on: Sep 5, 2009
 *      Author: theanswer
 */

#ifndef SELECTCHARACTERCALLBACK_H_
#define SELECTCHARACTERCALLBACK_H_

#include "../MessageCallback.h"

#include "server/zone/ZoneServer.h"
#include "server/zone/managers/player/PlayerManager.h"

#include "server/zone/objects/player/PlayerCreature.h"
#include "server/zone/objects/player/PlayerObject.h"

#include "server/chat/ChatManager.h"

class SelectCharacterCallback : public MessageCallback {
	uint64 characterID;
public:
	SelectCharacterCallback(ZoneClientSession* client, ZoneProcessServerImplementation* server) :
		MessageCallback(client, server) {

	}

	void parse(Message* message) {
		characterID = message->parseLong(6);
	}

	void run() {
		ZoneServer* zoneServer = server->getZoneServer();
		//ObjectManager* objectManager = zoneServer->getObjectManager();

		ManagedReference<SceneObject*> obj = zoneServer->getObject(characterID, true);

		if (obj != NULL && obj->isPlayerCreature()) {
			PlayerCreature* player = (PlayerCreature*) obj.get();

			Locker _locker(player);

			player->setClient(client);
			client->setPlayer(obj);

			Zone* zone = player->getZone();

			if (zone != NULL) {
				//reload

				player->reload(client);

			} else {
				int zoneID = player->getSavedZoneID();
				uint64 savedParentID = player->getSavedParentID();

				ManagedReference<SceneObject*> parent = zoneServer->getObject(savedParentID, true);

				if (parent != NULL) {
					try {
						parent->wlock(player);

						parent->addObject(player, -1);

						parent->unlock();
					} catch (...) {
						parent->unlock();
					}
				}

				zone = zoneServer->getZone(zoneID);

				player->insertToZone(zone);
			}

			player->setOnline();

			ChatManager* chatManager = zoneServer->getChatManager();
			chatManager->addPlayer(player);
			chatManager->loadMail(player);

			PlayerObject* ghost = player->getPlayerObject();
			ghost->notifyOnline();

			PlayerManager* playerManager = zoneServer->getPlayerManager();
			playerManager->sendMessageOfTheDay(player);

		}
	}
};


#endif /* SELECTCHARACTERCALLBACK_H_ */
