/*
 * DeathStateComponent.h
 *
 *  Created on: May 17, 2012
 *      Author: da
 */

#ifndef DEATHSTATECOMPONENT_H_
#define DEATHSTATECOMPONENT_H_

#include "AiStateComponent.h"
#include "../AiActor.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "engine/core/ManagedReference.h"
#include "server/zone/objects/creature/events/RespawnCreatureTask.h"

class DeathStateComponent : public AiStateComponent {
public:
	uint16 onEnter(AiActor* actor);

	uint16 doRecovery(AiActor* actor);

	uint16 doMovement(AiActor* actor);
};


#endif /* DEATHSTATECOMPONENT_H_ */
