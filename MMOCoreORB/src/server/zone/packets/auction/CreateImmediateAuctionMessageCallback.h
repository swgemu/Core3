/*
 * CreateImmediateAuctionMessageCallback.h
 *
 *  Created on: 13/03/2010
 *      Author: victor
 */

#ifndef CREATEIMMEDIATEAUCTIONMESSAGECALLBACK_H_
#define CREATEIMMEDIATEAUCTIONMESSAGECALLBACK_H_

#include "../MessageCallback.h"
#include "server/zone/managers/auction/AuctionManager.h"


class CreateImmediateAuctionMessageCallback : public MessageCallback {
	uint64 objectID;
	uint64 vendorID;

	uint32 price;
	uint32 duration;
	byte premium;

	UnicodeString description;
public:
	CreateImmediateAuctionMessageCallback(ZoneClientSession* client, ZoneProcessServer* server) :
			MessageCallback(client, server), objectID(0), vendorID(0), price(0), duration(0), premium(0) {

	}

	void parse(Message* message) {

		objectID = message->parseLong(); // object for sale
		vendorID = message->parseLong(); // vendor

		price = message->parseInt(); // Sale price
		duration = message->parseInt(); // How long to sell for in seconds

		message->parseUnicode(description);

		premium = message->parseByte(); // Preium Sale flag

	}

	void run() {
		ManagedReference<CreatureObject*> player = client->getPlayer().get().castTo<CreatureObject*>();
		ManagedReference<TangibleObject*> vendor = server->getZoneServer()->getObject(vendorID).castTo<TangibleObject*>();

		if (player == NULL || vendor == NULL || (!vendor->isVendor() && !vendor->isBazaarTerminal()))
			return;

		Locker locker(player);

		AuctionManager* auctionManager = server->getZoneServer()->getAuctionManager();

		auctionManager->addSaleItem(player, objectID, vendor, description, price, duration, false, premium);
	}

};

#endif /* CREATEIMMEDIATEAUCTIONMESSAGECALLBACK_H_ */
