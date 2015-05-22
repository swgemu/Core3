
#ifndef STORESPAWNEDCHILDRENTASK_H_
#define STORESPAWNEDCHILDRENTASK_H_

#include "server/zone/objects/creature/CreatureObject.h"

class StoreSpawnedChildrenTask : public Task {
	ManagedReference<CreatureObject*> player;
	Vector<ManagedReference<CreatureObject*> > children;
public:
	StoreSpawnedChildrenTask(CreatureObject* creo, Vector<ManagedReference<CreatureObject*> >& ch) :
		player(creo), children(ch) {

	}

	void run() {
		Locker locker(player);

		for (int i = 0; i < children.size(); ++i) {
			CreatureObject* child = children.get(i);

			if (child == NULL)
				continue;

			Locker clocker(child, player);

			ManagedReference<ControlDevice*> controlDevice = child->getControlDevice().get();

			if (controlDevice != NULL) {
				Locker deviceLocker(controlDevice);
				controlDevice->storeObject(player, true);
			}
		}

	}
};



#endif /* STORESPAWNEDCHILDRENTASK_H_ */
