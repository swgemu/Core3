/*
 * CenterOfBeingEvent.h
 *
 *  Created on: 01/06/2010
 *      Author: victor
 */

#ifndef CENTEROFBEINGEVENT_H_
#define CENTEROFBEINGEVENT_H_

#include "server/zone/objects/player/PlayerCreature.h"

class CenterOfBeingEvent : public Task {
	ManagedReference<PlayerCreature*> player;

public:
	CenterOfBeingEvent(PlayerCreature* pl) {
		player = pl;
	}

	void run() {
		Locker _locker(player);

		player->removePendingTask("centerofbeing");
		player->sendSystemMessage("combat_effects", "center_stop");
		player->showFlyText("combat_effects", "center_stop_fly", 255, 0, 0);
		player->setCenteredBonus(0);
	}
};


#endif /* CENTEROFBEINGEVENT_H_ */
