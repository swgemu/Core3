/*
 * CenterOfBeingEvent.h
 *
 *  Created on: 01/06/2010
 *      Author: victor
 */

#ifndef CENTEROFBEINGEVENT_H_
#define CENTEROFBEINGEVENT_H_

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"

class CenterOfBeingEvent : public Task {
	ManagedReference<CreatureObject*> player;

public:
	CenterOfBeingEvent(CreatureObject* pl) {
		player = pl;
	}

	void run() {
		Locker _locker(player);

		PlayerObject* ghost = player->getPlayerObject();

		player->removePendingTask("centerofbeing");
		player->sendSystemMessage("combat_effects", "center_stop");
		player->showFlyText("combat_effects", "center_stop_fly", 255, 0, 0);
		ghost->setCenteredBonus(0);
	}
};


#endif /* CENTEROFBEINGEVENT_H_ */
