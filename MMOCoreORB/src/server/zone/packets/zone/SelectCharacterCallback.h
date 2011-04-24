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
#include "server/zone/Zone.h"
#include "server/zone/managers/player/PlayerManager.h"

#include "server/zone/objects/player/PlayerCreature.h"
#include "server/zone/objects/player/PlayerObject.h"

#include "server/chat/ChatManager.h"

class SelectCharacterCallback : public MessageCallback {
	uint64 characterID;
public:
	SelectCharacterCallback(ZoneClientSession* client, ZoneProcessServer* server) :
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

			if (player->getPlayerObject() == NULL) {
				_locker.release();

				//oldClient->disconnect(),
				return;
			}

			ManagedReference<ZoneClientSession*> oldClient = player->getClient();

			if (oldClient != NULL && client != oldClient) {

				_locker.release();

				oldClient->disconnect();

				return;
			}

			player->setClient(client);
			client->setPlayer(obj);

			Zone* zone = player->getZone();

			if (zone != NULL && player->isInQuadTree()) {
				//reload

				player->reload(client);
				player->info("reloading");

			} else {
				String zoneName = player->getSavedTerrainName();
				uint64 savedParentID = player->getSavedParentID();

				ManagedReference<SceneObject*> parent = zoneServer->getObject(savedParentID, true);
				ManagedReference<SceneObject*> currentParent = player->getParent();

				if (currentParent != NULL && parent != NULL && parent->isCellObject() && currentParent->isCellObject()) {
					parent = currentParent;
				}

				try {
					zone = zoneServer->getZone(zoneName);
				} catch (Exception& e) {
					zone = NULL;
				}

				if (parent != NULL && (parent->isCellObject() || parent->isVehicleObject())) {
					try {
						Locker clocker(parent, player);



						if (parent->isCellObject())
							parent->addObject(player, -1, false);
						else if (parent->isVehicleObject())
							parent->addObject(player, 4, false);

					} catch (Exception& e) {

					}
				}

				if (parent != NULL) {
					zone = parent->getZone();

					if (zone == NULL) {
						SceneObject* root = parent->getRootParent();

						if (root != NULL)
							zone = root->getZone();
					}

				}

				if (zone == NULL)
					zone = zoneServer->getZone("corellia");

				player->insertToZone(zone);
			}

			player->setSavedParentID(0);
			player->setOnline();

			ChatManager* chatManager = zoneServer->getChatManager();
			chatManager->addPlayer(player);
			chatManager->loadMail(player);

			PlayerObject* ghost = player->getPlayerObject();
			if (ghost == NULL)
				return;

			ghost->notifyOnline();

			PlayerManager* playerManager = zoneServer->getPlayerManager();
			playerManager->sendMessageOfTheDay(player);

		}
	}
};


#endif /* SELECTCHARACTERCALLBACK_H_ */
