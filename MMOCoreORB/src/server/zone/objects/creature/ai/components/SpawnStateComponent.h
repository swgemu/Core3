/*
 * SpawnStateComponent.h
 *
 *  Created on: May 17, 2012
 *      Author: da
 */

#ifndef SPAWNSTATECOMPONENT_H_
#define SPAWNSTATECOMPONENT_H_

#include "AiStateComponent.h"
#include "../AiActor.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "engine/core/ManagedReference.h"
#include "server/zone/managers/creature/CreatureManager.h"

class SpawnStateComponent : public AiStateComponent {
public:
	uint16 onEnter(AiActor* actor);

	uint16 doRecovery(AiActor* actor);

	uint16 doMovement(AiActor* actor);
};


#endif /* SPAWNSTATECOMPONENT_H_ */
