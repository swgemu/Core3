/*
 * CreatureThinkEvent.h
 *
 *  Created on: 23/06/2010
 *      Author: victor
 */

#ifndef CREATURETHINKEVENT_H_
#define CREATURETHINKEVENT_H_


#include "../CreatureObject.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace events {

class CreatureThinkEvent : public Task {
	ManagedWeakReference<NonPlayerCreatureObject*> creature;

public:
	CreatureThinkEvent(NonPlayerCreatureObject* pl) : Task(1000) {
		creature = pl;
	}

	~CreatureThinkEvent() {
	}

	void run() {
		ManagedReference<NonPlayerCreatureObject*> strongRef = creature.get();

		if (strongRef == NULL)
			return;

		Locker locker(strongRef);
		strongRef->doRecovery();
	}

};

}
}
}
}
}

using namespace server::zone::objects::creature::events;


#endif /* CREATURETHINKEVENT_H_ */
