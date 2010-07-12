/*
 * CreatureMoveEvent.h
 *
 *  Created on: 10/07/2010
 *      Author: victor
 */

#ifndef CREATUREMOVEEVENT_H_
#define CREATUREMOVEEVENT_H_

#include "../CreatureObject.h"
#include "../PatrolPoint.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace events {

class CreatureMoveEvent : public Task {
	ManagedWeakReference<NonPlayerCreatureObject*> creature;

	//Vector<PatrolPoint> waypoints;

	//PatrolPoint homeLocation;
	//float nextPosition

public:
	CreatureMoveEvent(NonPlayerCreatureObject* pl) : Task(1000) {
		creature = pl;
	}

	~CreatureMoveEvent() {
	}

	void run() {
		ManagedReference<NonPlayerCreatureObject*> strongRef = creature.get();

		if (strongRef == NULL)
			return;

		Locker locker(strongRef);

		strongRef->doMovement();
	}

};

}
}
}
}
}

using namespace server::zone::objects::creature::events;



#endif /* CREATUREMOVEEVENT_H_ */
