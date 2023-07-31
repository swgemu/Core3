/*
 * ItemDropTradeCallback.h
 *
 *  Created on: 07/06/2010
 *      Author: victor
 */

#ifndef ITEMDROPTRADECALLBACK_H_
#define ITEMDROPTRADECALLBACK_H_

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/packets/trade/BeginTradeMessage.h"
#include "ObjectControllerMessageCallback.h"
#include "server/zone/objects/player/sessions/TradeSession.h"

class ItemDropTradeCallback : public MessageCallback {
	uint64 targetToTrade;

	ObjectControllerMessageCallback* objectControllerMain;

public:
	ItemDropTradeCallback(ObjectControllerMessageCallback* objectControllerCallback) : MessageCallback(objectControllerCallback->getClient(), objectControllerCallback->getServer()), targetToTrade(0), objectControllerMain(objectControllerCallback) {
	}

	void parse(Message* message) {
		//Logger::console.info(true) << message->toStringData();

		message->shiftOffset(16);
		targetToTrade = message->parseLong();
	}

	void run() {
		ManagedReference<CreatureObject*> player = client->getPlayer();

		// Player is not null and player is not in combat
		if (player == nullptr || player->isInCombat())
			return;

		uint64 playerID = player->getObjectID();

		// Player is not attempting to trade themselves
		if (targetToTrade == playerID)
			return;

		auto zoneServer = server->getZoneServer();

		if (zoneServer == nullptr)
			return;

		ManagedReference<SceneObject*> targetObject = zoneServer->getObject(targetToTrade);

		if (targetObject == nullptr) {
			StringIdChatParameter stringId("ui_trade", "request_player_unreachable_no_obj"); // "The person you want to trade with is unreachable."
			player->sendSystemMessage(stringId);

			return;
		}

		if (!targetObject->isPlayerCreature()) {
			StringIdChatParameter stringId("ui_trade", "start_fail_target_not_player"); // "You can only trade with other players."
			player->sendSystemMessage(stringId);

			return;
		}

		CreatureObject* targetPlayer = targetObject->asCreatureObject();

		if (targetPlayer == nullptr)
			return;

		// Check if target to trade is ignoring player
		auto targetGhost = targetPlayer->getPlayerObject();

		if (targetGhost != nullptr && targetGhost->isIgnoring(player->getFirstName()))
			return;

		ManagedReference<TradeSession*> playerTradeContainer = player->getActiveSession(SessionFacadeType::TRADE).castTo<TradeSession*>();

		// Player already has an active trade session
		if (playerTradeContainer != nullptr && playerTradeContainer->getTradeTargetPlayer() != targetToTrade) {
			StringIdChatParameter stringIdReq("ui_trade", "start_fail_target_other_prose"); // "You cannot start a trade with %TT while you are trading with %TO."
			stringIdReq.setTT(targetPlayer->getFirstName());

			CreatureObject* otherTarget = zoneServer->getObject(playerTradeContainer->getTradeTargetPlayer()).castTo<CreatureObject*>();

			if (otherTarget != nullptr) {
				stringIdReq.setTT(targetPlayer->getFirstName());
			}

			// Send already trading message
			player->sendSystemMessage(stringIdReq);

			return;
		}

		// Set trade target ID to target creO
		player->setTradeTargetID(targetToTrade);

		// Send trade message
		StringIdChatParameter stringIdReq("ui_trade", "requested_prose");
		stringIdReq.setTU(player->getFirstName());

		targetPlayer->sendSystemMessage(stringIdReq);

		ManagedReference<TradeSession*> targetTradeContainer = targetPlayer->getActiveSession(SessionFacadeType::TRADE).castTo<TradeSession*>();

		// check player's tradeTarget for their tradeTargetID
		uint64 tradeTargetTradeID = targetPlayer->getTradeTargetID();

		if (playerID != tradeTargetTradeID) {
			// Player has other trade target
			if (tradeTargetTradeID > 0 && targetTradeContainer != nullptr) {
				StringIdChatParameter stringId("ui_trade", "request_player_busy_prose"); // "%TU is already trading with someone else."
				stringId.setTU(targetPlayer->getFirstName());

				player->sendSystemMessage(stringId);
			}

			return;
		}

		// Trade has passed all the checks and each player has each other as a trade target
		Locker clocker(targetPlayer, player);

		// Setup players trade container
		if (playerTradeContainer == nullptr) {
			playerTradeContainer = new TradeSession();
			player->addActiveSession(SessionFacadeType::TRADE, playerTradeContainer);
		} else {
			playerTradeContainer->clearSession();
		}

		// Set the trade session on the target player
		playerTradeContainer->setTradeTargetPlayer(targetToTrade);

		// Setup targets trade container
		if (targetTradeContainer == nullptr) {
			targetTradeContainer = new TradeSession();
			targetPlayer->addActiveSession(SessionFacadeType::TRADE, targetTradeContainer);
		} else {
			targetTradeContainer->clearSession();
		}

		// Set the targetstrade session on the this player
		targetTradeContainer->setTradeTargetPlayer(playerID);

		BeginTradeMessage* msg = new BeginTradeMessage(targetPlayer->getObjectID());

		if (msg != nullptr)
			player->sendMessage(msg);

		BeginTradeMessage* msg2 = new BeginTradeMessage(player->getObjectID());

		if (msg2 != nullptr)
			targetPlayer->sendMessage(msg2);
	}
};

#endif /* ITEMDROPTRADECALLBACK_H_ */
