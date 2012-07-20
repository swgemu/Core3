/*
 * CancelLiveAuctionMessageCallback.h
 *
 *  Created on: Mar 17, 2011
 *      Author: polonel
 */

#ifndef CANCELLIVEAUCTIONMESSAGECALLBACK_H_
#define CANCELLIVEAUCTIONMESSAGECALLBACK_H_

#include "../MessageCallback.h"
#include "server/zone/managers/auction/AuctionManager.h"


class CancelLiveAuctionMessageCallback : public MessageCallback {
	uint64 objectid;

public:
	CancelLiveAuctionMessageCallback(ZoneClientSession* client, ZoneProcessServer* server) :
			MessageCallback(client, server) {

	}

	void parse(Message* message) {
		objectid = message->parseLong(); // object being canceled

	}

	void run() {
		ManagedReference<CreatureObject*> player = cast<CreatureObject*>( client->getPlayer().get().get());

		if (player == NULL)
			return;

		Locker locker(player);

		AuctionManager* auctionManager = server->getZoneServer()->getAuctionManager();

		auctionManager->cancelItem(player, objectid);
	}

};

#endif /* CANCELLIVEAUCTIONMESSAGECALLBACK_H_ */
