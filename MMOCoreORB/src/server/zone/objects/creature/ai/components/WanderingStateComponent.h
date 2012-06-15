/*
 * WanderingStateComponent.h
 *
 *  Created on: May 17, 2012
 *      Author: da
 */

#ifndef WANDERINGSTATECOMPONENT_H_
#define WANDERINGSTATECOMPONENT_H_

#include "AiStateComponent.h"
#include "../AiActor.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "engine/core/ManagedReference.h"
#include "server/zone/managers/creature/CreatureTemplateManager.h"

class WanderingStateComponent : public AiStateComponent {
public:
	uint16 onEnter(AiActor* actor);

	uint16 doRecovery(AiActor* actor);

	float getSpeed(CreatureObject* host);
};


#endif /* WANDERINGSTATECOMPONENT_H_ */
