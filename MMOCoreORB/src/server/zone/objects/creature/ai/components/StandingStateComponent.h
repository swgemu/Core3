/*
 * StandingStateComponent.h
 *
 *  Created on: May 17, 2012
 *      Author: da
 */

#ifndef STANDINGSTATECOMPONENT_H_
#define STANDINGSTATECOMPONENT_H_

#include "AiStateComponent.h"
#include "../AiActor.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "engine/core/ManagedReference.h"

class StandingStateComponent : public AiStateComponent {
public:
	uint16 onEnter(AiActor* actor);

	uint16 doRecovery(AiActor* actor);

	uint16 doMovement(AiActor* actor);
};


#endif /* STANDINGSTATECOMPONENT_H_ */
