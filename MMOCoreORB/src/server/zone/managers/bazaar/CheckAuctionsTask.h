/*
 * CheckAuctionsTask.h
 *
 *  Created on: 13/03/2010
 *      Author: victor
 */

#ifndef CHECKAUCTIONSTASK_H_
#define CHECKAUCTIONSTASK_H_

#include "engine/engine.h"

#include "BazaarManager.h"

class CheckAuctionsTask : public Task {
	ManagedWeakReference<BazaarManager*> bazaarManager;

public:
	CheckAuctionsTask(BazaarManager* bazaar) {
		bazaarManager = bazaar;
	}

	void run() {
		ManagedReference<BazaarManager*> strongRef = bazaarManager.get();

		if (strongRef == NULL)
			return;

		strongRef->checkAuctions();
	}
};

#endif /* CHECKAUCTIONSTASK_H_ */
