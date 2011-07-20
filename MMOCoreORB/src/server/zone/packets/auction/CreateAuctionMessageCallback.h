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
#include "server/zone/objects/tangible/terminal/vendor/VendorTerminal.h"
#include "server/zone/objects/creature/vendor/VendorCreature.h"


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
		ManagedReference<CreatureObject*> player = (CreatureObject*) client->getPlayer();
		ManagedReference<SceneObject*> sceno = server->getZoneServer()->getObject(vendorID);

		if (player == NULL || sceno == NULL || !sceno->isVendor())
			return;

		// And now we figure out what Vendor Class
		Vendor* vendor = NULL;

		if (sceno->isTerminal()) {
			Terminal* term = (Terminal*) sceno.get();
			if (term->isVendorTerminal()) {
				VendorTerminal* terminal = (VendorTerminal*) term;
				vendor = terminal->getVendor();
			}

		} else if (sceno->isCreatureObject()) {
			CreatureObject* cero = (CreatureObject*) sceno.get();
			if (!cero->isVendorCreature())
				return;

			VendorCreature* vendorCreature = (VendorCreature*) cero;
			vendor = vendorCreature->getVendor();

		} else
			return;

		if (vendor == NULL)
			return;

		AuctionManager* auctionManager = server->getZoneServer()->getAuctionManager();
		//duration = 60;
		auctionManager->addSaleItem(player, objectID, vendor, description, price, duration, true, premium);
	}

};


#endif /* CREATEAUCTIONMESSAGECALLBACK_H_ */
