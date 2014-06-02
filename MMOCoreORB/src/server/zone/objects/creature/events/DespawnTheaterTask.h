
#ifndef DESPAWNTHEATERTASK_H_
#define DESPAWNTHEATERTASK_H_

#include "server/zone/objects/tangible/TangibleObject.h"

class DespawnTheaterTask : public Task {
	ManagedReference<TangibleObject*> theater;

public:
	DespawnTheaterTask(TangibleObject* tano) {
		theater = tano;
	}

	void run() {
		Locker locker(theater);

		Zone* zone = theater->getZone();

		if (zone == NULL)
			return;

		theater->destroyObjectFromWorld(true);

	}
};


#endif /* DESPAWNTHEATERTASK_H_ */
