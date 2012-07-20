/*
 * CreateAuctionMessageCallback.h
 *
 *  Created on: 13/03/2010
 *      Author: victor
 */

#ifndef CREATEAUCTIONMESSAGECALLBACK_H_
#define CREATEAUCTIONMESSAGECALLBACK_H_


#include "../MessageCallback.h"
#include "server/zone/managers/auction/AuctionManager.h"


class CreateAuctionMessageCallback : public MessageCallback {
	uint64 objectID;
	uint64 vendorID;

	uint32 price;
	uint32 duration;

	UnicodeString description;

	byte premium;
public:
	CreateAuctionMessageCallback(ZoneClientSession* client, ZoneProcessServer* server) :
			MessageCallback(client, server) {

	}

	void parse(Message* message) {

		objectID = message->parseLong(); // object for sale
		vendorID = message->parseLong(); // vendor

		price = message->parseInt(); // Sale price
		duration = message->parseInt(); // How long to sell for in minutes

		message->parseUnicode(description);

		premium = message->parseByte();

	}

	void run() {
		ManagedReference<CreatureObject*> player = cast<CreatureObject*>( client->getPlayer().get().get());
		ManagedReference<TangibleObject*> vendor = cast<TangibleObject*>(server->getZoneServer()->getObject(vendorID));

		if (player == NULL || vendor == NULL)
			return;

		if (!vendor->isBazaarTerminal() && !vendor->isVendor())
			return;

		Locker locker(player);

		AuctionManager* auctionManager = server->getZoneServer()->getAuctionManager();

		auctionManager->addSaleItem(player, objectID, vendor, description, price, duration, true, premium);
	}

};


#endif /* CREATEAUCTIONMESSAGECALLBACK_H_ */
