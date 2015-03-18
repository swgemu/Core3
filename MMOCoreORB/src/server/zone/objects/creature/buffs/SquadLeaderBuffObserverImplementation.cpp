/*
 * SquadLeaderBuffObserverImplementation.cpp
 *
 *  Created on: Mar 18, 2015
 *      Author: dannuic
 */

#include "server/zone/objects/creature/buffs/SquadLeaderBuffObserver.h"
#include "server/zone/objects/creature/buffs/SquadLeaderBuff.h"

#include "server/zone/objects/scene/SceneObjectType.h"

#include "server/zone/objects/creature/CreatureObject.h"

int SquadLeaderBuffObserverImplementation::notifyObserverEvent(unsigned int eventType, Observable* observable, ManagedObject* arg1, int64 arg2) {
	ManagedReference<SquadLeaderBuff* > buff = this->buff.get();

	if (buff == NULL)
		return 1;

	ManagedReference<CreatureObject*> player = buff->getPlayer();
	ManagedReference<CreatureObject*> leader = buff->getLeader();
	if (player == NULL || leader == NULL)
		return 1;

	if (player->getParentRecursively(SceneObjectType::BUILDING) == leader->getParentRecursively(SceneObjectType::BUILDING)) {
		if (!buff->isActive())
			buff->activate();
	} else if (buff->isActive())
		buff->deactivate();

	return 0;
}



