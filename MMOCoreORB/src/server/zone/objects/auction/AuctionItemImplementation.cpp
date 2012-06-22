/*
 * AuctionItemImplementation.cpp
 *
 *  Created on: 12/03/2010
 *      Author: victor
 */

#include "AuctionItem.h"
#include "server/zone/objects/region/CityRegion.h"
#include "server/zone/Zone.h"

void AuctionItemImplementation::setVendorUID(const String& uid) {
	vuid = uid;
	//printf("terminal title:%s\n", title.toString().toCharArray());
}

void AuctionItemImplementation::clearAuctionWithdraw() {
	if (auctionOptions & OPTION_WITHDRAW)
		auctionOptions &= ~OPTION_WITHDRAW;
}

void AuctionItemImplementation::notifyLoadFromDatabase() {
	/*if ((auctionOptions & OPTION_WITHDRAW)) {
		auctionOptions |= 10;
	}*/
	clearAuctionWithdraw();
}
