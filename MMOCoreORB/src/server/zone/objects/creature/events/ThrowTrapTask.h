/*
 * ThrowTrapTask.h
 *
 *  Created on: Nov 20, 2010
 *      Author: da
 */

#ifndef THROWTRAPTASK_H_
#define THROWTRAPTASK_H_

#include "engine/util/u3d/Coordinate.h"
#include "../AiAgent.h"
#include "../CreatureObject.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace events {

class ThrowTrapTask : public Task {
	ManagedReference<CreatureObject* > player;
	ManagedReference<CreatureObject* > target;
	ManagedReference<Buff*> buff;
	StringIdChatParameter message;
	int damage;
	short pool;
public:
	ThrowTrapTask(CreatureObject* p, CreatureObject* t,
			Buff* b, StringIdChatParameter m, short po, int d) : Task(2700) {
		player = p;
		target = t;
		buff = b;
		message = m;
		damage = d;
		pool = po;
	}

	virtual ~ThrowTrapTask() {
	}

	void run() {
		if (player == NULL || target == NULL)
			return;

		Locker locker2(player);

		player->removePendingTask("throwtrap");
		player->sendSystemMessage(message);

		Locker locker(target);

		if(buff != NULL) {
			target->addBuff(buff);
		}

		target->inflictDamage(player, pool, damage, true);

	}
};

}
}
}
}
}

using namespace server::zone::objects::creature::events;

#endif /* THROWTRAPTASK_H_ */
