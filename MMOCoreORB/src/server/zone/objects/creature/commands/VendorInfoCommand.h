/*
 * VendorInfoCommand.h
 *
 *  Created on: Apr 6, 2011
 *      Author: polonel
 */

#ifndef VENDORINFOCOMMAND_H_
#define VENDORINFOCOMMAND_H_

#include "engine/engine.h"
#include "server/zone/managers/vendor/VendorManager.h"
#include "server/zone/managers/auction/AuctionManager.h"
#include "server/zone/managers/auction/AuctionsMap.h"

class VendorInfoCommand {
public:
	static int executeCommand(CreatureObject* creature, uint64 target, const UnicodeString& arguments) {
		if (!creature->isPlayerCreature())
			return 1;

		ManagedReference<CreatureObject*> player = cast<CreatureObject*>(creature);
		ManagedReference<AuctionManager*> auctionManager = player->getZoneServer()->getAuctionManager();
		ManagedReference<AuctionsMap*> amap = auctionManager->getAuctionMap();

		int totalVendors = VendorManager::instance()->getVendorMapSize();
		int totalVendorItems = amap->getVendorItemCount();
		int totalBazaarItems = amap->getAuctionCount();
		player->sendSystemMessage("Vendor / Bazaar Information");
		player->sendSystemMessage("---------------------------");
		player->sendSystemMessage("Total Number of Items: " + String::valueOf(totalVendorItems + totalBazaarItems));
		player->sendSystemMessage("Total Number of Vendors: " + String::valueOf(totalVendors));
		player->sendSystemMessage("Total Number of Vendor Items: " + String::valueOf(totalVendorItems));
		player->sendSystemMessage("Total Number of Bazaar Items: " + String::valueOf(totalBazaarItems));

		return 0;
	}

};

#endif /* VENDORINFOCOMMAND_H_ */
