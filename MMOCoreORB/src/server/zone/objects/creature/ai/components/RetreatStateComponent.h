/*
 * RetreatStateComponent.h
 *
 *  Created on: Jun 3, 2012
 *      Author: da
 */

#ifndef RETREATSTATECOMPONENT_H_
#define RETREATSTATECOMPONENT_H_

#include "AiStateComponent.h"
#include "../AiActor.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "engine/core/ManagedReference.h"

class RetreatStateComponent : public AiStateComponent {
	uint16 onEnter(AiActor* actor);

	uint16 doRecovery(AiActor* actor);

	uint16 doMovement(AiActor* actor);

	void onExit(AiActor* actor);

	float getSpeed(CreatureObject* host);

};


#endif /* RETREATSTATECOMPONENT_H_ */
