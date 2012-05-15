/*
 * GetAuctionDetailsCallback.h
 *
 *  Created on: 13/03/2010
 *      Author: victor
 */

#ifndef GETAUCTIONDETAILSCALLBACK
#define GETAUCTIONDETAILSCALLBACK

#include "../MessageCallback.h"
#include "server/zone/managers/auction/AuctionManager.h"


class GetAuctionDetailsCallback : public MessageCallback {
	uint64 objectid;

public:
	GetAuctionDetailsCallback(ZoneClientSession* client, ZoneProcessServer* server) :
			MessageCallback(client, server) {

	}

	void parse(Message* message) {
		objectid = message->parseLong();
	}

	void run() {
		ManagedReference<CreatureObject*> player = cast<CreatureObject*>( client->getPlayer());

		if (player == NULL)
			return;

		AuctionManager* auctionManager = server->getZoneServer()->getAuctionManager();
		auctionManager->getItemAttributes(player, objectid);
	}

};

#endif

