/*
 * DizzyFallDownEvent.h
 *
 *  Created on: 02/06/2010
 *      Author: victor
 */

#ifndef POSTUREUPDATEEVENT_H_
#define POSTUREUPDATEEVENT_H_

#include "server/zone/objects/creature/CreatureObject.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace events {

class PostureUpdateTask : public Task {
	ManagedReference<CreatureObject*> creature;
public:

	PostureUpdateTask(CreatureObject* creat) : Task() {
		creature = creat;
	}

	void run() {
		Locker locker(creature);

		PostureMessage* octrl = new PostureMessage(creature);
		creature->broadcastMessage(octrl, true);
	}
};

}
}
}
}
}


#endif /* POSTUREUPDATEEVENT_H_ */
