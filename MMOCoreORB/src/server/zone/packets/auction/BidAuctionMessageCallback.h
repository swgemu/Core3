/*
 * BidAuctionMessageCallback.h
 *
 *  Created on: 14/03/2010
 *      Author: victor
 */

#ifndef BIDAUCTIONMESSAGECALLBACK_H_
#define BIDAUCTIONMESSAGECALLBACK_H_


#include "../MessageCallback.h"
#include "server/zone/managers/auction/AuctionManager.h"


class BidAuctionMessageCallback : public MessageCallback {
	uint64 objectid;
	uint32 price1;
	uint32 price2;

public:
	BidAuctionMessageCallback(ZoneClientSession* client, ZoneProcessServer* server) :
			MessageCallback(client, server) {

	}

	void parse(Message* message) {
		objectid = message->parseLong();
		price1 = message->parseInt();
		price2 = message->parseInt();
	}

	void run() {
		ManagedReference<CreatureObject*> player = cast<CreatureObject*>( client->getPlayer().get().get());

		if (player == NULL)
			return;

		AuctionManager* auctionManager = server->getZoneServer()->getAuctionManager();
		auctionManager->buyItem(player, objectid, price1, price2);
	}

};

#endif /* BIDAUCTIONMESSAGECALLBACK_H_ */
