/*
 * AuctionItemImplementation.cpp
 *
 *  Created on: 12/03/2010
 *      Author: victor
 */

#include "AuctionItem.h"
#include "server/zone/objects/region/CityRegion.h"
#include "server/zone/Zone.h"


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
