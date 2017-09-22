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
	DenyTradeMessageCallback(ZoneClientSession *session, ZoneProcessServer *server) : MessageCallback(session, server) {

	}

	void parse(Message* message) {

	}

	void run() {
		Reference<CreatureObject*> object = client->getPlayer();

		if (object == NULL)
			return;

		Locker _locker(object);
		Reference<TradeSession*> tradeContainer = object->getActiveSession(SessionFacadeType::TRADE).castTo<TradeSession*>();

		if (tradeContainer == NULL) {
			object->error("DenyTradeMessage without TradeSession");
			return;
                }

		uint64 targetID = tradeContainer->getTradeTargetPlayer();

		Reference<ZoneServer*> zone = getServer()->getZoneServer();
		if (zone == NULL)
			return;

		Reference<CreatureObject*> target = zone->getObject(targetID).castTo<CreatureObject*>();
		if (target != NULL)
			target->sendMessage(new DenyTradeMessage());
	}
};

#endif /*DENYTRADEMESSAGE_H_*/
