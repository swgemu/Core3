/*
 * CheckAuctionsTask.h
 *
 *  Created on: 13/03/2010
 *      Author: victor
 */

#ifndef CHECKAUCTIONSTASK_H_
#define CHECKAUCTIONSTASK_H_

#include "server/zone/managers/auction/AuctionManager.h"

class CheckAuctionsTask : public Task {
	ManagedWeakReference<AuctionManager*> auctionManager;

public:
	CheckAuctionsTask(AuctionManager* manager) {
		auctionManager = manager;

		setCustomTaskQueue("slowQueue");
	}

	void run() {
		ManagedReference<AuctionManager*> strongRef = auctionManager.get();

		if (strongRef == NULL)
			return;

		ZoneServer* server = strongRef->getZoneServer();

		if (server == NULL || server->isServerShuttingDown())
			return;

		strongRef->checkAuctions();
		strongRef->checkVendorItems();
	}
};

#endif /* CHECKAUCTIONSTASK_H_ */
