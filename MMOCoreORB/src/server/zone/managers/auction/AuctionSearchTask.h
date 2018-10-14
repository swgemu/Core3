#ifndef AUCTIONSEARCHTASK_H_
#define AUCTIONSEARCHTASK_H_

#include "server/zone/managers/auction/AuctionManager.h"

namespace server {
namespace zone {
namespace managers {
namespace auction {

class AuctionSearchTask : public Task {
	ManagedWeakReference<AuctionManager*> auctionManager;
	ManagedWeakReference<CreatureObject*> player;
	ManagedWeakReference<SceneObject*> vendorInUse;
	ManagedWeakReference<SceneObject*> vendor;
	String planet, region;
	int screen, minPrice, maxPrice, clientCounter, offset;
	bool includeEntranceFee;
	int32 category;
	UnicodeString filterText;

public:
	AuctionSearchTask(AuctionManager* manager, CreatureObject* play, SceneObject* uVendor, const String& plnt, const String& reg, SceneObject* vend, int scr, uint32 cat, const UnicodeString& filter, int minP, int maxP, bool entFee, int counter, int off) {
		auctionManager = manager;
		player = play;
		vendorInUse = uVendor;
		vendor = vend;
		planet = plnt;
		region = reg;
		screen = scr;
		category = cat;
		minPrice = minP;
		maxPrice = maxP;
		clientCounter = counter;
		offset = off;
		filterText = filter;
		includeEntranceFee = entFee;

		setCustomTaskQueue("AuctionSearchQueue");
	}

	void run() {
		ManagedReference<AuctionManager*> strongRef = auctionManager.get();

		if (strongRef == nullptr)
			return;

		ManagedReference<CreatureObject*> strongPlayer = player.get();

		if (strongPlayer == nullptr)
			return;

		ManagedReference<SceneObject*> strongVendorInUse = vendorInUse.get();

		if (strongVendorInUse == nullptr)
			return;

		ManagedReference<SceneObject*> strongVendor = vendor.get();

		Locker locker(strongPlayer);

		strongRef->getAuctionData(strongPlayer, strongVendorInUse, planet, region, strongVendor, screen, category, filterText, minPrice, maxPrice, includeEntranceFee, clientCounter, offset);

	}
};

}
}
}
}

#endif /* AUCTIONSEARCHTASK_H_ */
