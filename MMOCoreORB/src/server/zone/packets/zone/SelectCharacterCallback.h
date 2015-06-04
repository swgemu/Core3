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
#include "server/zone/managers/reaction/ReactionManager.h"

#include "server/zone/objects/player/sessions/EntertainingSession.h"
#include "server/zone/packets/creature/CreatureObjectDeltaMessage6.h"

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"

#include "server/chat/ChatManager.h"
#include "server/login/account/Account.h"

#include "server/zone/objects/player/events/DisconnectClientEvent.h"

class SelectCharacterCallback : public MessageCallback {
	uint64 characterID;
public:
	SelectCharacterCallback(ZoneClientSession* client, ZoneProcessServer* server) :
		MessageCallback(client, server), characterID(0) {

	}

	void parse(Message* message) {
		characterID = message->parseLong(6);
	}

	void run() {
		ZoneServer* zoneServer = server->getZoneServer();
		
		if (zoneServer->isServerLocked()) {
			ErrorMessage* errMsg = new ErrorMessage("Login Error", "Server is currently locked", 0);
			client->sendMessage(errMsg);

			return;
		}

		if (zoneServer->isServerLoading()) {
			ErrorMessage* errMsg = new ErrorMessage("Login Error", "Server is currently loading", 0);
			client->sendMessage(errMsg);
			
			return;
		}

		if(!client->hasCharacter(characterID, zoneServer->getGalaxyID())) {
			ErrorMessage* errMsg = new ErrorMessage("Login Error", "You are unable to login with this character\n\nIf you feel this is an error please close your client, and try again.", 0x0);
			client->sendMessage(errMsg);

			//client->error("invalid character id " + String::valueOf(characterID) + " in account: " + String::valueOf(client->getAccountID()));
			return;
		}

		//ObjectManager* objectManager = zoneServer->getObjectManager();

		//Logger::console.info("selected char id: 0x" + String::hexvalueOf((int64)characterID), true);

		ManagedReference<SceneObject*> obj = zoneServer->getObject(characterID, true);

		if (obj != NULL && obj->isPlayerCreature()) {
			CreatureObject* player = cast<CreatureObject*>( obj.get());
			PlayerObject* ghost = player->getPlayerObject();

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

				Reference<DisconnectClientEvent*> task = new DisconnectClientEvent(player, oldClient, DisconnectClientEvent::DISCONNECT);
				Core::getTaskManager()->executeTask(task);

				return;
			}
			
			if (ghost->getAdminLevel() == 0 && (zoneServer->getConnectionCount() >= zoneServer->getServerCap())) {
				client->sendMessage(new ErrorMessage("Login Error", "Server cap reached, please try again later", 0));
				return;				
			}

			if (!zoneServer->getPlayerManager()->increaseOnlineCharCountIfPossible(client)) {
				ErrorMessage* errMsg = new ErrorMessage("Login Error", "You reached the max online character count.", 0x0);
				client->sendMessage(errMsg);

				return;
			}

			player->setClient(client);
			client->setPlayer(obj);

			String zoneName = ghost->getSavedTerrainName();
			uint64 savedParentID = ghost->getSavedParentID();
			ManagedReference<SceneObject*> playerParent = zoneServer->getObject(savedParentID, true);

			Zone* zone = zoneServer->getZone(zoneName);

			if (zone == NULL) {
				ErrorMessage* errMsg = new ErrorMessage("Login Error", "The planet where your character was stored is disabled!", 0x0);
				client->sendMessage(errMsg);

				return;
			}

			ManagedReference<SceneObject*> currentParent = player->getParent();

			if ((playerParent != NULL && currentParent == NULL) || (currentParent != NULL && currentParent->isCellObject())) {
				ghost->setTeleporting(true);
				ghost->setOnLoadScreen(true);
				player->setMovementCounter(0);
				ghost->setClientLastMovementStamp(0);

				playerParent = playerParent == NULL ? currentParent : playerParent;

				ManagedReference<SceneObject*> root = playerParent->getRootParent();

				root = root == NULL ? playerParent : root;

				//ghost->updateLastValidatedPosition();

				if (root->getZone() == NULL && root->isStructureObject()) {
					player->initializePosition(root->getPositionX(), root->getPositionZ(), root->getPositionY());

					zone->transferObject(player, -1, true);

					playerParent = NULL;
				} else {
					playerParent->transferObject(player, -1, false);

					if (player->getParent() == NULL) {
						zone->transferObject(player, -1, false);
					} else if (root->getZone() == NULL) {
						zone->transferObject(root, -1, false);
					}

					player->sendToOwner(true);
				}

			} else if (currentParent == NULL) {
				zone->transferObject(player, -1, true);
			} else {
				if (player->getZone() == NULL) {
					ManagedReference<SceneObject*> objectToInsert = currentParent != NULL ? player->getRootParent().get() : player;

					if (objectToInsert == NULL)
						objectToInsert = player;

					zone->transferObject(objectToInsert, -1, false);
				}

				player->sendToOwner(true);
			}

			if (playerParent == NULL)
				ghost->setSavedParentID(0);

			ghost->setOnline();

			ChatManager* chatManager = zoneServer->getChatManager();
			chatManager->addPlayer(player);
			chatManager->loadMail(player);

			// Join auction chat room
			ManagedReference<ChatRoom*> auctionChat = chatManager->getAuctionRoom();
			if( auctionChat != NULL ){
				auctionChat->sendTo(player);
				auctionChat->addPlayer(player);
			}

			// Join General chat room
			ManagedReference<ChatRoom*> generalChat = chatManager->getGeneralRoom();
			if (generalChat != NULL) {
				generalChat->sendTo(player);
				generalChat->addPlayer(player);
			}

			ghost->notifyOnline();

			PlayerManager* playerManager = zoneServer->getPlayerManager();
			playerManager->sendLoginMessage(player);

			ReactionManager* reactionManager = zoneServer->getReactionManager();
			reactionManager->doReactionFineMailCheck(player);

			//player->info("sending login Message:" + zoneServer->getLoginMessage(), true);

			// Disable music notes if player had been playing music
			if (!player->isPlayingMusic() && !player->isDancing()) {
				player->setPerformanceCounter(0, false);
				player->setInstrumentID(0, false);

				CreatureObjectDeltaMessage6* dcreo6 = new CreatureObjectDeltaMessage6(player);
				dcreo6->updatePerformanceAnimation(player->getPerformanceAnimation());
				dcreo6->updatePerformanceCounter(0);
				dcreo6->updateInstrumentID(0);
				dcreo6->close();
				player->broadcastMessage(dcreo6, true);

				player->setListenToID(0);

				// Stop playing music/dancing animation
				if (player->getPosture() == CreaturePosture::SKILLANIMATING)
					player->setPosture(CreaturePosture::UPRIGHT);

			}

			SkillModManager::instance()->verifyWearableSkillMods(player);

		} else {
			if (obj != NULL)
				client->error("could get from zone server character id " + String::valueOf(characterID) + " but is not a player creature");
			else
				client->error("could not get from zone server character id " + String::valueOf(characterID));
		}
	}
};


#endif /* SELECTCHARACTERCALLBACK_H_ */
