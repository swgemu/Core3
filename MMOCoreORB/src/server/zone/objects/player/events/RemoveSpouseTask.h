
#ifndef REMOVESPOUSETASK_H_
#define REMOVESPOUSETASK_H_

#include "server/zone/objects/player/PlayerObject.h"

class RemoveSpouseTask : public Task {
	ManagedReference<CreatureObject*> creature;

public:
	RemoveSpouseTask(CreatureObject* creatureObject) : Task() {
		creature = creatureObject;
	}

	void run() {
		if (creature == NULL)
			return;

		Locker locker(creature);

		PlayerObject* ghost = creature->getPlayerObject().get();
		if (ghost == NULL)
			return;

		ghost->removeSpouse();
	}
};

#endif /* REMOVESPOUSETASK_H_ */
