/*
 * AuctionQueryHeadersMessageCallback.h
 *
 *  Created on: 30/01/2010
 *      Author: victor
 */

#ifndef AUCTIONQUERYHEADERSMESSAGECALLBACK_H_
#define AUCTIONQUERYHEADERSMESSAGECALLBACK_H_

#include "../MessageCallback.h"

class AuctionQueryHeadersMessageCallback : public MessageCallback {
public:
	AuctionQueryHeadersMessageCallback(ZoneClientSession* client, ZoneProcessServerImplementation* server) :
			MessageCallback(client, server) {

	}

	void parse(Message* message) {
		/*int extent = pack->parseInt();
		// 0 - galaxy, 1 - planet, 2 - region, 3 - vendor
		int counter = pack->parseInt();
		int screen = pack->parseInt();
		// 2 - all items, 3 - my sales, 4 - my bids, 5 - available items,
		// 7 - for sale, 9 - offers to vendor
		uint32 category = pack->parseInt();  // Bitmask
		pack->shiftOffset(21);
		uint64 bazaarId = pack->parseLong();
		char unk1 = pack->parseByte();
		int offset = pack->parseShort();

		BazaarManager* bazaarManager = server->getBazaarManager();
		if (extent == 0)
			bazaarManager->getBazaarData(player, bazaarId, screen, extent, category, counter, offset);
		else if (extent == 1) {
			BazaarPlanetManager* planetManager = bazaarManager->getPlanet(bazaarId);

			if (planetManager != NULL)
				planetManager->getBazaarData(player, bazaarId, screen, extent, category, counter, offset);
		}
		else if (extent == 2) {
			RegionBazaar* bazaar = bazaarManager->getBazaar(bazaarId);
			if (bazaar != NULL)
				bazaar->getBazaarData(player, bazaarId, screen, extent, category, counter, offset);
		}*/
	}

	void run() {

	}
};


#endif /* AUCTIONQUERYHEADERSMESSAGECALLBACK_H_ */
