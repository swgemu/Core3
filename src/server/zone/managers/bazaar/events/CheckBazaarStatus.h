#ifndef CHECKBAZAARSTATUS_H_
#define CHECKBAZAARSTATUS_H_

#include "../BazaarManagerImplementation.h"

class CheckBazaarStatus : public Event {
	BazaarManagerImplementation* bazaarManager;

public:
	CheckBazaarStatus(BazaarManagerImplementation* manager) : Event() {
		bazaarManager = manager;

		setKeeping(true);
	}

	bool activate() {
		try {
			bazaarManager->lock();

			bazaarManager->checkAuctions();

			bazaarManager->unlock();
		} catch (...) {
			bazaarManager->unlock();
		}

		return true;
	}
};

#endif /*CHECKBAZAARSTATUS_H_*/
