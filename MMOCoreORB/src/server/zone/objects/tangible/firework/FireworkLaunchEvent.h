/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef FIREWORKLAUNCHEVENT_H_
#define FIREWORKLAUNCHEVENT_H_


#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/tangible/firework/FireworkObject.h"
#include "server/zone/ZoneServer.h"

class FireworkLaunchEvent : public Task {
	ManagedWeakReference<FireworkObject*> firework;
	ManagedWeakReference<CreatureObject*> player;
	int removeDelay;

public:
	FireworkLaunchEvent(CreatureObject* player, FireworkObject* firework, int removeDelay) : Task(1000) {
		this->firework = firework;
		this->player = player;
		this->removeDelay = removeDelay;
	}

	void run() {
		ManagedReference<FireworkObject*> firework = this->firework.get();
		ManagedReference<CreatureObject*> player = this->player.get();

		if (firework == NULL || player == NULL)
			return;

		try {
			Locker locker(firework);

			firework->completeLaunch(player, removeDelay);
		} catch (Exception& e) {
			player->error("unreported exception on FireworkLaunchEvent::run()");
		}

		this->firework = NULL;
		this->player = NULL;
	}
};


#endif /* FIREWORKLAUNCHEVENT_H_ */
