/*
 * AttackStateComponent.h
 *
 *  Created on: May 17, 2012
 *      Author: da
 */

#ifndef ATTACKSTATECOMPONENT_H_
#define ATTACKSTATECOMPONENT_H_

#include "AiStateComponent.h"
#include "../AiActor.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "engine/core/ManagedReference.h"
#include "server/zone/objects/tangible/threat/ThreatMap.h"

class AttackStateComponent : public AiStateComponent {
public:
	uint16 onEnter(AiActor* actor);

	uint16 doRecovery(AiActor* actor);

	uint16 doMovement(AiActor* actor);

	float getMaxDistance(CreatureObject* host) {
		return host->getWeapon()->getIdealRange(true);
	}

	float getSpeed(CreatureObject* host) {
		return host->getRunSpeed();
	}
};


#endif /* ATTACKSTATECOMPONENT_H_ */
