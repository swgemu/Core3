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

// #define DEBUG_SELECT_CHAR_CALLBACK

class SelectCharacterCallback : public MessageCallback {
	uint64 characterID;
public:
	SelectCharacterCallback(ZoneClientSession* client, ZoneProcessServer* server) : MessageCallback(client, server), characterID(0) {
		setCustomTaskQueue("slowQueue");
	}

	void parse(Message* message) {
		characterID = message->parseLong(6);
	}

	static void connectPlayer(SceneObject* obj, uint64_t characterID, CreatureObject* player, ZoneClientSession* client, ZoneServer* zoneServer) {
		auto ghost = player->getPlayerObject();

		if (ghost == nullptr) {
			return;
		}

		// Store all of the players spawned children: Pets & vehicles, except ships (bool)
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

		// Tie client to player object
		player->setClient(client);
		client->setPlayer(player);

		// Get stored zone name
		String zoneName = ghost->getSavedTerrainName();

		auto zone = zoneServer->getZone(zoneName);

#ifdef DEBUG_SELECT_CHAR_CALLBACK
		StringBuffer debugMsg;

		debugMsg << "---------- SelectCharacterCallback ----------" << endl <<
		"Player: " << player->getDisplayedName() << endl <<
		"Zone: " << zoneName << endl;
#endif // DEBUG_SELECT_CHAR_CALLBACK

		if (zone == nullptr) {
			ErrorMessage* errMsg = new ErrorMessage("Login Error", "The planet where your character was stored is disabled!", 0x0);
			client->sendMessage(errMsg);

#ifdef DEBUG_SELECT_CHAR_CALLBACK
			player->info(true) << debugMsg.toString();
#endif // DEBUG_SELECT_CHAR_CALLBACK
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

		// Set player as teleporing and reset their movement count and timestamp
		ghost->setTeleporting(true);
		player->setMovementCounter(0);
		ghost->setClientLastMovementStamp(0);

		// Set PlayerObject on Load Screen if they are not in the world
		if (player->getZone() == nullptr) {
			ghost->setOnLoadScreen(true);
		}

		/* Select Character Callback Notes:

		Player is in a container (cell, ship, pilot chair, operations chair, ship turret):
			- If a player is LD and not in the zone both playerParent and currentParent should not be true.
			- If a player has unloaded playerParent is not null and currentParent is null.
			- Vehicles are excluded, they are stored when a player logs back in.

		Player is in the zone or was in a vehicle:
			- Both playerParent and currentParent are nullptr's, except with vehicles where playerParent is not null.

		Players can be transferred into one of the following:

		1. No parent, transferred into the zone
		2. Parent is a cell in a building
		3. Root Parent is a ship.
			3a. Parent is a ship itself
			3b. Parent is a cell in a Ship (PoB)
			3c. Parent is a pilot chair
		*/

		// Players saved parent ID
		uint64 savedParentID = ghost->getSavedParentID();
		// Players last logout position
		Vector3 lastWorldPosition = ghost->getLastLogoutWorldPosition();
		// Players current containmentType
		int playerArrangement = player->getContainmentType();

		ManagedReference<SceneObject*> playerParent = zoneServer->getObject(savedParentID, true).get();
		auto currentParent = player->getParent().get();
		ManagedReference<SceneObject*> rootParent = player->getRootParent();

#ifdef DEBUG_SELECT_CHAR_CALLBACK
		debugMsg << "Player Arrangement: " << playerArrangement << "\nsavedParentID: " << savedParentID << "\nLast Logout World Position: " << lastWorldPosition.toString() << endl;

		if (playerParent != nullptr)
			debugMsg << "playerParent: " << playerParent->getObjectName()->getFullPath() << " ID: " << playerParent->getObjectID() << endl;
		else
			debugMsg << "playerParent: nullptr" << endl;

		if (currentParent != nullptr)
			debugMsg << "currentParent: " << currentParent->getObjectName()->getFullPath() << " ID: " << currentParent->getObjectID() << endl;
		else
			debugMsg << "currentParent: nullptr" << endl;

		if (rootParent != nullptr)
			debugMsg << "rootParent: " << rootParent->getObjectName()->getFullPath() << " ID: " << rootParent->getObjectID();
		else
			debugMsg << "rootParent: nullptr";

		player->info(true) << debugMsg.toString();
#endif

		// This bool signifies a player was inside of a parent but fully unloaded from the game world (not LD).
		bool unloadedInParent = (playerParent != nullptr && currentParent == nullptr);
		bool currentParentNull = (currentParent == nullptr);

		// Lets branch for Ships First, player must still be LD in the game world or they should be sent back to their launch position. - Ship, Pilot Chair, Operatios Chair, Ship Turret.
		if (!currentParentNull && playerParent != nullptr && ((!unloadedInParent && currentParent->isValidJtlParent()) ||
			(currentParent->isCellObject() && rootParent != nullptr && rootParent->isPobShip() && rootParent->getLocalZone() != nullptr))) {

#ifdef DEBUG_SELECT_CHAR_CALLBACK
			player->info(true) << "SelectCharacterCallback -- Sending Player into Ship or child of a ship";
#endif

			playerParent->transferObject(player, playerArrangement, false, false, true);
			player->sendToOwner(true);

			if (playerParent->isShipObject()) {
				rootParent = playerParent;
			} else {
				rootParent = playerParent->getRootParent();
			}

			if (rootParent != nullptr) {
				rootParent->notifyObjectInsertedToChild(player, playerParent, nullptr);

#ifdef DEBUG_SELECT_CHAR_CALLBACK
				player->info(true) << "SelectCharacterCallback -- rootParent Ship - Notified player has been inserted.";
#endif
			}
		// Player is inside a cell
		} else if ((!currentParentNull && currentParent->isCellObject()) || (unloadedInParent && playerParent->isCellObject())) {
#ifdef DEBUG_SELECT_CHAR_CALLBACK
			player->info(true) << "SelectCharacterCallback -- Sending Player into cell";
#endif
			// playerParent shouldn't be null, but just in case update it with currentParent
			playerParent = (playerParent == nullptr ? currentParent : playerParent);

			rootParent = playerParent->getRootParent();

			rootParent = (rootParent == nullptr ? playerParent : rootParent);

			// The root parent structure or building is no longer in the game world, player will be placed in the zone at their last world logout position.
			if (rootParent->getZone() == nullptr) {
				float x = lastWorldPosition.getX();
				float y = lastWorldPosition.getY();
				float z = CollisionManager::getWorldFloorCollision(x, y, zone, false);

				player->initializePosition(lastWorldPosition.getX(), lastWorldPosition.getZ(), lastWorldPosition.getY());

				zone->transferObject(player, -1, true);

				playerParent = nullptr;
			// Structure or building exists, transfer player back into their parent cell
			} else {
				playerParent->transferObject(player, -1, true);

				player->sendToOwner(true);
			}
		// Player is LD on a vehicle. Vehicle is auto stored when player reconnects.
		} else if (!unloadedInParent && !currentParentNull && currentParent->isVehicleObject()) {
#ifdef DEBUG_SELECT_CHAR_CALLBACK
			player->info(true) << "SelectCharacterCallback -- Player is in vehicle still LD, transferring vehicle into zone.";
#endif
			if (player->getZone() == nullptr) {
				ManagedReference<SceneObject*> objectToInsert = currentParent != nullptr ? player->getRootParent() : player;

				if (objectToInsert == nullptr)
					objectToInsert = player;

				Locker clocker(objectToInsert, player);
				zone->transferObject(objectToInsert, -1, false);
			}

			player->sendToOwner(true);
		} else {
#ifdef DEBUG_SELECT_CHAR_CALLBACK
			player->info(true) << "SelectCharacterCallback -- Sending Player directly to zone";
#endif
			// Clear structure mods from the player
			player->removeAllSkillModsOfType(SkillModManager::STRUCTURE);

			// Lets make sure we clear space states
			player->clearSpaceStates();

			if (savedParentID != 0) {
				float x = lastWorldPosition.getX();
				float y = lastWorldPosition.getY();
				float z = CollisionManager::getWorldFloorCollision(x, y, zone, false);

				player->initializePosition(x, z, y);
			}

			zone->transferObject(player, -1, true);
		}

		// Player does not have a parent, clear the saved parent.
		if (playerParent == nullptr) {
			ghost->setSavedParentID(0);
		}

		// Set the player online & notify
		ghost->setOnline();
		ghost->notifyOnline();

		auto chatManager = zoneServer->getChatManager();

		if (chatManager != nullptr) {
			chatManager->addPlayer(player);
			chatManager->loadMail(player);
		}

		auto playerManager = zoneServer->getPlayerManager();

		if (playerManager != nullptr) {
			playerManager->sendLoginMessage(player);
		}

		auto reactionManager = zoneServer->getReactionManager();

		if (reactionManager != nullptr) {
			reactionManager->doReactionFineMailCheck(player);
		}

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
			if (player->getPosture() == CreaturePosture::SKILLANIMATING) {
				player->setPosture(CreaturePosture::UPRIGHT);
			}

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
