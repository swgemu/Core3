/*
 * ThrowTrapTask.h
 *
 *  Created on: Nov 20, 2010
 *      Author: da
 */

#ifndef THROWTRAPTASK_H_
#define THROWTRAPTASK_H_

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/managers/combat/CombatManager.h"

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
	bool hit;
public:
	ThrowTrapTask(CreatureObject* p, CreatureObject* t,
			Buff* b, const StringIdChatParameter& m, short po, int d, bool h) : Task(2300) {
		player = p;
		target = t;
		buff = b;
		message = m;
		damage = d;
		pool = po;
		hit = h;
	}

	virtual ~ThrowTrapTask() {
	}

	void run() {
		if (player == NULL || target == NULL)
			return;

		Locker locker2(player);

		player->removePendingTask("throwtrap");

		Locker locker(target, player);

		if(!CombatManager::instance()->startCombat(player, target))
			return;

		player->sendSystemMessage(message);

		if(hit) {

			if(buff != NULL) {
				Locker buffLocker(buff);

				target->addBuff(buff);
			}

			target->inflictDamage(player, pool, damage, true);

			//Not sure on exact xp value, estimate now and update later
			int xp = target->getLevel() * 15;
			ManagedReference<PlayerManager*> playerManager = player->getZoneServer()->getPlayerManager();
			if(playerManager != NULL)
				playerManager->awardExperience(player, "trapping", xp, true);
		}

	}
};

}
}
}
}
}

using namespace server::zone::objects::creature::events;

#endif /* THROWTRAPTASK_H_ */
