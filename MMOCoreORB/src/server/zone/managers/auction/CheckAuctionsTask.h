/*
 * CheckAuctionsTask.h
 *
 *  Created on: 13/03/2010
 *      Author: victor
 */

#ifndef CHECKAUCTIONSTASK_H_
#define CHECKAUCTIONSTASK_H_

#include "engine/engine.h"

#include "AuctionManager.h"

class CheckAuctionsTask : public Task {
	ManagedWeakReference<AuctionManager*> auctionManager;

public:
	CheckAuctionsTask(AuctionManager* manager) {
		auctionManager = manager;
	}

	void run() {
		ManagedReference<AuctionManager*> strongRef = auctionManager.get();

		if (strongRef == NULL)
			return;

		strongRef->checkAuctions();
		strongRef->checkVendorItems();
	}
};

#endif /* CHECKAUCTIONSTASK_H_ */
