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
#include "server/zone/objects/player/PlayerObject.h"

#include "server/zone/objects/group/GroupObject.h"

int SquadLeaderBuffObserverImplementation::notifyObserverEvent(unsigned int eventType, Observable* observable, ManagedObject* arg1, int64 arg2) {
	if (eventType != ObserverEventType::PARENTCHANGED && eventType != ObserverEventType::BHTEFCHANGED && eventType != ObserverEventType::FACTIONCHANGED && eventType != ObserverEventType::OBJECTDESTRUCTION && eventType != ObserverEventType::CREATUREREVIVED)
		return 0;

	ManagedReference<SquadLeaderBuff* > strongBuff = buff.get();

	if (strongBuff == NULL)
		return 1;

	ManagedReference<CreatureObject*> player = strongBuff->getPlayer();
	if (player == NULL)
		return 1;

	ManagedReference<CreatureObject*> leader = strongBuff->getLeader();

	if (leader == NULL || player->getGroup() == NULL || player->getGroup()->getLeader() != leader) {
		Core::getTaskManager()->executeTask([=] () {
			Locker locker(player);
			Locker clocker(strongBuff, player);
			player->removeBuff(strongBuff->getBuffCRC());
		}, "SquadLeaderObserverRemoveBuffLambda");
		return 1;
	}

	Reference<SquadLeaderBuffObserver*> thisObserver = _this.getReferenceUnsafeStaticCast();

	Core::getTaskManager()->executeTask([=] () {
		thisObserver->handleObserverEvent(player, strongBuff);
	}, "HandleSquadLeaderObserverEventLambda");

	return 0;
}

void SquadLeaderBuffObserverImplementation::handleObserverEvent(CreatureObject* player, SquadLeaderBuff* slBuff) {
	Locker locker(player);
	Locker clocker(slBuff, player);

	if (player->getBuff(slBuff->getBuffCRC()) != slBuff)
		return;

	if (slBuff->qualifiesForActivation()) {
		if (!slBuff->isActive()) {
			slBuff->doActivate(false);
		}
	} else if (slBuff->isActive()) {
		slBuff->deactivate();
	}
}
