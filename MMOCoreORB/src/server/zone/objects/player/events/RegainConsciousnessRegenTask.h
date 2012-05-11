/*
 * RegainConsciousnessRegenTask.h
 *
 *  Created on: Aug 18, 2011
 *      Author: swgemu
 */

#ifndef REGAINCONSCIOUSNESSREGENTASK_H_
#define REGAINCONSCIOUSNESSREGENTASK_H_


#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/creature/CreatureObject.h"

class RegainConsciousnessRegenTask : public Task {
	ManagedReference<PlayerObject*> playero;
	ManagedReference<CreatureObject*> creature;
public:

	RegainConsciousnessRegenTask(CreatureObject* creo, PlayerObject* playerObject) {
		playero = playerObject;
		creature = creo;
	}

	void run() {
		Locker locker(creature);

		playero->setForcePowerRegen(playero->getForcePowerRegen() * 2);
		creature->removePendingTask("regainConsciousnessRegenTask");
	}
};


#endif /* REGAINCONSCIOUSNESSREGENTASK_H_ */
