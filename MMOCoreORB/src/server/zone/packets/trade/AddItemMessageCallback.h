/*
 * AddItemMessageCallback.h
 *
 *  Created on: 07/06/2010
 *      Author: victor
 */

#ifndef ADDITEMMESSAGECALLBACK_H_
#define ADDITEMMESSAGECALLBACK_H_

#include "server/zone/packets/MessageCallback.h"
#include "server/zone/managers/player/PlayerManager.h"

class AddItemMessageCallback : public MessageCallback {
	uint64 id;

public:
	AddItemMessageCallback(ZoneClientSession* client, ZoneProcessServer* server) : MessageCallback(client, server), id(0) {
	}

	void parse(Message* message) {
		id = message->parseLong();
	}

	void run() {
		ManagedReference<CreatureObject*> player = client->getPlayer();

		if (player == nullptr)
			return;

		auto zoneServer = server->getZoneServer();

		if (zoneServer == nullptr)
			return;

		auto playerMan = zoneServer->getPlayerManager();

		if (playerMan == nullptr)
			return;

		Locker lock(player);

		playerMan->handleAddItemToTradeWindow(player, id);
	}
};

#endif /* ADDITEMMESSAGECALLBACK_H_ */
