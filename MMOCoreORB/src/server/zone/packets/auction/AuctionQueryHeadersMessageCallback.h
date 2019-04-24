/*
 * AuctionQueryHeadersMessageCallback.h
 *
 *  Created on: 30/01/2010
 *      Author: victor
 */

#ifndef AUCTIONQUERYHEADERSMESSAGECALLBACK_H_
#define AUCTIONQUERYHEADERSMESSAGECALLBACK_H_

#include "server/zone/packets/MessageCallback.h"
#include "server/zone/managers/auction/AuctionManager.h"

class AuctionQueryHeadersMessageCallback : public MessageCallback {
	int locationType;
	int counter;
	int searchType;
	uint32 itemCategory;
	int unk1;
	UnicodeString filterText;
	int unk2;
	int minPrice;
	int maxPrice;
	bool includeEntranceFee;
	uint64 vendorID;
	bool isVendor;
	int offset;

public:
	AuctionQueryHeadersMessageCallback(ZoneClientSession* client, ZoneProcessServer* server) :
			MessageCallback(client, server), locationType(0), counter(0), searchType(0), itemCategory(0), unk1(0), unk2(0), minPrice(0), maxPrice(0), includeEntranceFee(0), vendorID(0), isVendor(0), offset(0) {

	}

	void parse(Message* message) {
		locationType = message->parseInt();
		counter = message->parseInt();
		searchType = message->parseInt();
		itemCategory = message->parseInt();  // Bitmask

		unk1 = message->parseInt();
		message->parseUnicode(filterText);
		unk2 = message->parseInt();
		minPrice = message->parseInt();
		maxPrice = message->parseInt();
		includeEntranceFee = message->parseByte();

		vendorID = message->parseLong();
		isVendor = message->parseByte(); //Becomes one when using a vendor.
		offset = message->parseShort();

	}

	void run() {
		ManagedReference<CreatureObject*> player = client->getPlayer();

		if (player == nullptr)
			return;
			
		Locker locker(player);

		AuctionManager* auctionManager = server->getZoneServer()->getAuctionManager();

		if (auctionManager != nullptr)
			auctionManager->getData(player, locationType, vendorID, searchType, itemCategory, filterText, minPrice, maxPrice, includeEntranceFee, counter, offset);
	}
};

#endif /* AUCTIONQUERYHEADERSMESSAGECALLBACK_H_ */
