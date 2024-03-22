/*
 * SelectCharacterCallback.h
 *
 *  Created on: Sep 5, 2009
 *      Author: theanswer
 */

#ifndef SELECTCHARACTERCALLBACK_H_
#define SELECTCHARACTERCALLBACK_H_

#include "server/zone/packets/MessageCallback.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/Zone.h"
#include "server/zone/SpaceZone.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/managers/reaction/ReactionManager.h"
#include "server/zone/packets/creature/CreatureObjectDeltaMessage6.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/chat/ChatManager.h"
#include "server/zone/objects/player/events/DisconnectClientEvent.h"
#include "server/zone/managers/collision/CollisionManager.h"
#include "templates/params/creature/PlayerArrangement.h"

#ifdef WITH_SESSION_API
#include "server/login/SessionAPIClient.h"
#endif // WITH_SESSION_API

class SelectCharacterCallback : public MessageCallback {
	uint64 characterID;
public:
	SelectCharacterCallback(ZoneClientSession* client, ZoneProcessServer* server) :
		MessageCallback(client, server), characterID(0) {

		setCustomTaskQueue("slowQueue");
	}

	void parse(Message* message) {
		characterID = message->parseLong(6);
	}

	static void connectPlayer(SceneObject* obj, uint64_t characterID, CreatureObject* player, ZoneClientSession* client, ZoneServer* zoneServer) {
		PlayerObject* ghost = player->getPlayerObject();

		if (ghost == nullptr) {
			return;
		}

		ghost->unloadSpawnedChildren(true);

		if (ghost->getAdminLevel() == 0 && (zoneServer->getConnectionCount() >= zoneServer->getServerCap())) {
			client->sendMessage(new ErrorMessage("Login Error", "Server cap reached, please try again later", 0));
			return;
		}

		if (zoneServer->isServerLocked() && (ghost->getAdminLevel() == 0)) {
			ErrorMessage* errMsg = new ErrorMessage("Login Error", "Server is currently locked", 0);
			client->sendMessage(errMsg);

			return;
		}

#ifdef WITH_SESSION_API
		auto clientIP = client->getIPAddress();
		auto loggedInAccounts = zoneServer->getPlayerManager()->getOnlineZoneClientMap()->getAccountsLoggedIn(clientIP);

		SessionAPIClient::instance()->approvePlayerConnect(clientIP, ghost->getAccountID(), characterID, loggedInAccounts,
				[object = Reference<SceneObject*>(obj), characterID,
				playerCreature = Reference<CreatureObject*>(player),
				clientObject = Reference<ZoneClientSession*>(client),
				zoneServer](const SessionApprovalResult& result) {

			if (!result.isActionAllowed()) {
				clientObject->info(true) << "Player connect not approved: " << result.getLogMessage();

				clientObject->sendMessage(new ErrorMessage(result.getTitle(), result.getMessage(true), 0));
				return;
			}

			Locker locker(object);

			if (result.isActionDebug() && playerCreature != nullptr) {
				auto ghost = playerCreature->getPlayerObject();

				if (ghost != nullptr) {
					ghost->setLogLevel(Logger::DEBUG);
				}
			}

			connectApprovedPlayer(object, characterID, playerCreature, clientObject, zoneServer);
		});
	};

	static void connectApprovedPlayer(SceneObject* obj, uint64_t characterID, CreatureObject* player, ZoneClientSession* client, ZoneServer* zoneServer) {
		PlayerObject* ghost = player->getPlayerObject();

		if (ghost == nullptr) {
			return;
		}
#endif // WITH_SESSION_API

		player->setClient(client);
		client->setPlayer(player);

		String zoneName = ghost->getSavedTerrainName();

		Zone* zone = zoneServer->getZone(zoneName);

		if (zone == nullptr) {
			ErrorMessage* errMsg = new ErrorMessage("Login Error", "The planet where your character was stored is disabled!", 0x0);
			client->sendMessage(errMsg);

			return;
		}

		if (!zoneServer->getPlayerManager()->increaseOnlineCharCountIfPossible(client)) {
			auto maxOnline = zoneServer->getPlayerManager()->getOnlineCharactersPerAccount();
			StringBuffer msg;
			String plural = maxOnline > 1 ? "s" : "";

			msg << "\\#ffff00You have reached this server's limit of " <<  maxOnline << " character" << plural << " online per account.\\#." << endl << endl
				<< "\\#ffffffPlease logout your other character" << plural << " and try again.\\#.";

			ErrorMessage* errMsg = new ErrorMessage("Login Error", msg.toString(), 0x0);
			client->sendMessage(errMsg);

			return;
		}

		ghost->setTeleporting(true);
		player->setMovementCounter(0);
		ghost->setClientLastMovementStamp(0);

		if (player->getZone() == nullptr)
			ghost->setOnLoadScreen(true);

		uint64 savedParentID = ghost->getSavedParentID();

		ManagedReference<SceneObject*> playerParent = zoneServer->getObject(savedParentID, true);
		ManagedReference<SceneObject*> currentParent = player->getParent().get();

		player->info(true) << "SelectCharacterCallback -- playerParent - " << (playerParent == nullptr ? "nullptr" : String::valueOf(savedParentID));
		player->info(true) << "SelectCharacterCallback -- currentParent - " << (currentParent == nullptr ? "nullptr" : String::valueOf(currentParent->getObjectID()));

		/* Select Character Callback Notes:

			Player is in a container (cell, vehicle, ship, pilot chair, operations chair, ship turret):
				- If a player is LD and not in the zone both playerParent and currentParent should not be true.
				- If a player has unloaded playerParent is no null and currentParent is null.

			Player is in the zone:
				- Bother playerParent and currentParent are nullptr's

			Players can be transferred into one of the following:

			1. No parent, transferred into the zone
			2. Parent is a cell in a building
			3. Root Parent is a ship.
				3a. Parent is a ship itself
				3b. Parent is a cell in a Ship (PoB)
				3c. Parent is a pilot chair
		*/




		ManagedReference<SceneObject*> rootParent = player->getRootParent();


		if ((playerParent != nullptr && currentParent == nullptr) || (currentParent != nullptr && (currentParent->isCellObject() || player->isInShipStation() || currentParent->isShipObject()))) {
			player->info(true) << "SelectCharacterCallback -- if 1";

			playerParent = (playerParent == nullptr ? currentParent : playerParent);

			ManagedReference<SceneObject*> rootParent = playerParent->getRootParent();

			// This is probably making players root the ship
			rootParent = (rootParent == nullptr ? playerParent : rootParent);

			player->info(true) << "SelectCharacterCallback -- Root Parent: " << rootParent->getDisplayedName() << " playerParent: " << playerParent->getDisplayedName() << " Player Parent Game Type: " << playerParent->getGameObjectType() << " --  " << playerParent->getGameObjectTypeStringID();

			if (rootParent->getZone() == nullptr && rootParent->isStructureObject()) {
				player->initializePosition(rootParent->getPositionX(), rootParent->getPositionZ(), rootParent->getPositionY());

				zone->transferObject(player, -1, true);

				playerParent = nullptr;
			// Handle Ships here
			} else if (rootParent->isShipObject()) {
				player->info(true) << "SelectCharacterCallback -- rootParent is a ship, handleing in else if";

				if (rootParent->getLocalZone() == nullptr) {
					// Safety net, players root is a ship that is not launched
					auto launchCoords = ghost->getSpaceLaunchLocation();
					auto launchZone = ghost->getSpaceLaunchZone();

					ghost->setSavedTerrainName(launchZone);

					player->initializePosition(launchCoords.getX(), launchCoords.getZ(), launchCoords.getY());

					zone = zoneServer->getZone(launchZone);

					if (zone != nullptr)
						zone->transferObject(player, -1, true);

					playerParent = nullptr;
				// Player is pilotting a fightership or in a gunboat position
				} else if (playerParent == rootParent) {
					rootParent->transferObject(player, player->getContainmentType(), false, false, false);
					player->sendToOwner(true);
				// Player is in POB Ship cell
				} else if (playerParent->isCellObject()) {
					player->clearSpaceStates();
					player->setState(CreatureState::SHIPINTERIOR);

					playerParent->transferObject(player, -1, false, false, false);
					player->sendToOwner(true);
				// Player is in slotted position
				} else if (player->isInShipStation()) {
					playerParent->transferObject(player, player->getContainmentType(), false, false, false);
					player->sendToOwner(true);

					rootParent->notifyObjectInsertedToChild(player, playerParent, nullptr);
				}
			} else {
				player->info(true) << "SelectCharacterCallback -- into the else";

				if (!((playerParent->isShipObject() || playerParent->isCellObject()) && playerParent == rootParent)) {
					player->info(true) << "transferring player into ship that might not be launched!";

					playerParent->transferObject(player, -1, true);
				}

				if (player->getParent() == nullptr) {
					zone->transferObject(player, -1, true);
				} else if (rootParent->getZone() == nullptr) {
					Locker clocker(rootParent, player);
					zone->transferObject(rootParent, -1, true);
				}

				player->sendToOwner(true);
			}
		} else if (currentParent == nullptr) {
			player->info(true) << "SelectCharacterCallback -- else if 2";

			player->removeAllSkillModsOfType(SkillModManager::STRUCTURE);

			Vector3 worldPos = ghost->getLastLogoutWorldPosition();
			float x = worldPos.getX();
			float y = worldPos.getY();

			if (savedParentID != 0 && (x != 0 || y != 0)) {
				float z = CollisionManager::getWorldFloorCollision(x, y, zone, false);

				player->initializePosition(x, z, y);
			}

			zone->transferObject(player, -1, true);
		} else {
			player->info(true) << "SelectCharacterCallback -- else 3";

			if (player->getZone() == nullptr) {
				ManagedReference<SceneObject*> objectToInsert = currentParent != nullptr ? player->getRootParent() : player;

				if (objectToInsert == nullptr)
					objectToInsert = player;

				Locker clocker(objectToInsert, player);
				zone->transferObject(objectToInsert, -1, false);
			}

			player->sendToOwner(true);
		}

		if (playerParent == nullptr)
			ghost->setSavedParentID(0);

		ghost->setOnline();

		ChatManager* chatManager = zoneServer->getChatManager();
		chatManager->addPlayer(player);
		chatManager->loadMail(player);

		ghost->notifyOnline();

		PlayerManager* playerManager = zoneServer->getPlayerManager();
		playerManager->sendLoginMessage(player);

		ReactionManager* reactionManager = zoneServer->getReactionManager();
		reactionManager->doReactionFineMailCheck(player);

		//player->info("sending login Message:" + zoneServer->getLoginMessage(), true);

		// Disable music notes if player had been playing music
		if (!player->isPlayingMusic() && !player->isDancing()) {
			player->setPerformanceStartTime(0, false);
			player->setPerformanceType(0, false);

			CreatureObjectDeltaMessage6* dcreo6 = new CreatureObjectDeltaMessage6(player);
			dcreo6->updatePerformanceAnimation(player->getPerformanceAnimation());
			dcreo6->updatePerformanceStartTime(0);
			dcreo6->updatePerformanceType(0);
			dcreo6->close();
			player->broadcastMessage(dcreo6, true);

			player->setListenToID(0);

			// Stop playing music/dancing animation
			if (player->getPosture() == CreaturePosture::SKILLANIMATING)
				player->setPosture(CreaturePosture::UPRIGHT);

		}

		SkillModManager::instance()->verifyWearableSkillMods(player);
	}

	void run() {
		ZoneServer* zoneServer = server->getZoneServer();

		if (zoneServer->isServerLoading()) {
			ErrorMessage* errMsg = new ErrorMessage("Login Error", "Server is currently loading", 0);
			client->sendMessage(errMsg);

			return;
		}

		if (zoneServer->isServerShuttingDown()) {
			ErrorMessage* errMsg = new ErrorMessage("Login Error", "Server is shutting down", 0);
			client->sendMessage(errMsg);

			return;
		}

		if (!client->hasCharacter(characterID, zoneServer->getGalaxyID())) {
			ErrorMessage* errMsg = new ErrorMessage("Login Error", "You are unable to login with this character\n\nIf you feel this is an error please close your client, and try again.", 0x0);
			client->sendMessage(errMsg);

			//client->error("invalid character id " + String::valueOf(characterID) + " in account: " + String::valueOf(client->getAccountID()));
			return;
		}

		//Logger::console.info("selected char id: 0x" + String::hexvalueOf((int64)characterID), true);

		ManagedReference<SceneObject*> obj = zoneServer->getObject(characterID, true);

		if (obj != nullptr && obj->isPlayerCreature()) {
			CreatureObject* player = obj->asCreatureObject();

			Locker _locker(player);

			ManagedReference<ZoneClientSession*> oldClient = player->getClient();

			if (oldClient != nullptr && client != oldClient) {
				_locker.release();

				oldClient->disconnect();

				Reference<DisconnectClientEvent*> task = new DisconnectClientEvent(player, oldClient, DisconnectClientEvent::DISCONNECT);
				player->executeOrderedTask(task);

				static const String lambdaName = "ConnectPlayerLambda";

				auto characterID = this->characterID;
				auto client = this->client;

				player->executeOrderedTask([obj, characterID, player, client, zoneServer] () {
					Locker locker(obj);

					connectPlayer(obj, characterID, player, client, zoneServer);
				}, lambdaName);

				return;
			}

			connectPlayer(obj, characterID, player, client, zoneServer);
		} else {
			if (obj != nullptr)
				client->error("could get from zone server character id " + String::valueOf(characterID) + " but is not a player creature");
			else
				client->error("could not get from zone server character id " + String::valueOf(characterID));
		}
	}
};


#endif /* SELECTCHARACTERCALLBACK_H_ */
