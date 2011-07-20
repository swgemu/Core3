/*
 * AuctionQueryHeadersMessageCallback.h
 *
 *  Created on: 30/01/2010
 *      Author: victor
 */

#ifndef AUCTIONQUERYHEADERSMESSAGECALLBACK_H_
#define AUCTIONQUERYHEADERSMESSAGECALLBACK_H_

#include "../MessageCallback.h"

#include "server/zone/objects/auction/Vendor.h"
#include "server/zone/objects/tangible/terminal/Terminal.h"
#include "server/zone/managers/auction/AuctionManager.h"

class AuctionQueryHeadersMessageCallback : public MessageCallback {
	int extent;
	int counter;
	int screen;
	uint32 category;
	uint64 vendorID;
	char unk1;
	int offset;

public:
	AuctionQueryHeadersMessageCallback(ZoneClientSession* client, ZoneProcessServer* server) :
			MessageCallback(client, server) {

	}

	void parse(Message* message) {
		extent = message->parseInt();
		// 0 - galaxy, 1 - planet, 2 - region, 3 - vendor
		counter = message->parseInt();
		screen = message->parseInt();
		// 2 - all items, 3 - my sales, 4 - my bids, 5 - available items,
		// 7 - for sale (vendor), 9 - offers to vendor
		category = message->parseInt();  // Bitmask
		message->shiftOffset(21);
		vendorID = message->parseLong();
		unk1 = message->parseByte(); //Becomes one when using a vendor.
		offset = message->parseShort();


	}

	void run() {
		ManagedReference<CreatureObject*> player = (CreatureObject*) client->getPlayer();

		if (player == NULL)
			return;

		AuctionManager* auctionManager = server->getZoneServer()->getAuctionManager();

		auctionManager->getData(player, extent, vendorID, screen, category, counter, offset);
	}
};


#endif /* AUCTIONQUERYHEADERSMESSAGECALLBACK_H_ */
