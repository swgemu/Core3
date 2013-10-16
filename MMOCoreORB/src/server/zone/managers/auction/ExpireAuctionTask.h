/*
 * ExpireAuctionTask.h
 *
 *  Created on: 6/22/2012
 *      Author: kyle
 */

#ifndef EXPIREAUCTIONTASK_H_
#define EXPIREAUCTIONTASK_H_

#include "engine/engine.h"

#include "server/zone/managers/auction/AuctionManager.h"

class ExpireAuctionTask : public Task {
	ManagedWeakReference<AuctionManager*> auctionManager;
	ManagedWeakReference<AuctionItem*> item;

public:
	ExpireAuctionTask(AuctionManager* manager, AuctionItem* it) {
		auctionManager = manager;
		item = it;
	}

	void run() {
		ManagedReference<AuctionManager*> strongRef = auctionManager.get();
		ManagedReference<AuctionItem*> strongRefItem = item.get();

		if (strongRef == NULL || strongRefItem == NULL)
			return;

		strongRef->expireAuction(strongRefItem);
	}
};

#endif /* EXPIREAUCTIONTASK_H_ */
