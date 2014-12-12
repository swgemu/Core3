/*
 * DroidTrapTask.h
 */

#ifndef DROIDTRAPTASK_H_
#define DROIDTRAPTASK_H_

#include "engine/util/u3d/Coordinate.h"
#include "server/zone/objects/creature/AiAgent.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/managers/player/PlayerManager.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace events {

class DroidTrapTask : public Task {
	ManagedReference<CreatureObject* > droid;
	ManagedReference<CreatureObject* > player;
	ManagedReference<CreatureObject* > target;
	ManagedReference<Buff*> buff;
	StringIdChatParameter message;
	int damage;
	short pool;
	bool hit;
public:
	DroidTrapTask(CreatureObject* p, CreatureObject* t,	CreatureObject* dr, Buff* b, StringIdChatParameter m, short po, int d, bool h) : Task(2300) {
		player = p;
		target = t;
		droid = dr;
		buff = b;
		message = m;
		damage = d;
		pool = po;
		hit = h;
	}

	virtual ~DroidTrapTask() {
	}

	void run() {
		if (player == NULL || target == NULL || droid == NULL)
			return;

		Locker locker2(droid);
		droid->removePendingTask("throwtrap");
		droid->sendSystemMessage(message);

		if(hit) {
			Locker locker(target, droid);

			if(buff != NULL) {
				target->addBuff(buff);
			}

			target->inflictDamage(droid, pool, damage, true);

			//Players get the full trap xp, as per http://www.swgemu.com/archive/scrapbookv51/data/20070127195942/
			// Players get 1/2 rating according to http://wiki.swganh.org/index.php/Scout_Trap_Projectile_Unit_Module_Usage_%28Game_Mechanics%29
			// i learn towards the offical forum posts
			int xp = target->getLevel() * 15;
			ManagedReference<PlayerManager*> playerManager = player->getZoneServer()->getPlayerManager();
			if(playerManager != NULL) {
				locker.release(); // release the target
				Locker clock(player,droid);
				playerManager->awardExperience(player, "trapping", xp, true);
			}
		}

	}
};

}
}
}
}
}

using namespace server::zone::objects::creature::events;

#endif /* DROIDTRAPTASK_H_ */
