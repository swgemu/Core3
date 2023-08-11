/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef DENYTRADEMESSAGE_H_
#define DENYTRADEMESSAGE_H_
#include "server/zone/packets/MessageCallback.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/sessions/TradeSession.h"

class DenyTradeMessage : public BaseMessage {
public:
	DenyTradeMessage() : BaseMessage(6) {
		insertShort(1);
		insertInt(0x6EC28670);
	}
};

class DenyTradeMessageCallback : public MessageCallback {
public:
	DenyTradeMessageCallback(ZoneClientSession* session, ZoneProcessServer* server) : MessageCallback(session, server) {
	}

	void parse(Message *message) {
	}

	void run() {
		ManagedReference<CreatureObject*> player = client->getPlayer();

		if (player == nullptr)
			return;

		Locker _locker(player);

		Reference<TradeSession *> tradeContainer = player->getActiveSession(SessionFacadeType::TRADE).castTo<TradeSession *>();

		if (tradeContainer == nullptr) {
			player->error() << player->getDisplayedName() << " ID: " << player->getObjectID() << " - DenyTradeMessage without TradeSession.";
			return;
		}

		uint64 targetID = tradeContainer->getTradeTargetPlayer();

		Reference<ZoneServer*> zoneServer = player->getZoneServer();

		if (zoneServer == nullptr)
			return;

		ManagedReference<CreatureObject*> target = zoneServer->getObject(targetID).castTo<CreatureObject*>();

		if (target != nullptr)
			target->sendMessage(new DenyTradeMessage());
	}
};

#endif /*DENYTRADEMESSAGE_H_*/
