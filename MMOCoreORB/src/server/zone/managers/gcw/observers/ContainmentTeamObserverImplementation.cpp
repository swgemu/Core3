/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.
 */

#include "server/zone/managers/gcw/observers/ContainmentTeamObserver.h"

#include "server/zone/managers/combat/CombatManager.h"
#include "server/zone/objects/creature/ai/AiAgent.h"
#include "server/zone/objects/tangible/TangibleObject.h"

int ContainmentTeamObserverImplementation::notifyObserverEvent(unsigned int eventType, Observable* observable, ManagedObject* arg1, int64 arg2) {
	Locker locker(&containmentTeamLock);

	ManagedReference<TangibleObject*> attacker = cast<TangibleObject*>(arg1);
	if (attacker == nullptr) {
		return 0;
	}

	attack(attacker);

	return 1;
}

void ContainmentTeamObserverImplementation::addMember(AiAgent* member) {
	Locker locker(&containmentTeamLock);
	teamMembers.add(member);
}

int ContainmentTeamObserverImplementation::size() {
	Locker locker(&containmentTeamLock);
	return teamMembers.size();
}

AiAgent* ContainmentTeamObserverImplementation::getMember(unsigned int teamMemberIndex) {
	Locker locker(&containmentTeamLock);
	return teamMembers.get(teamMemberIndex);
}

bool ContainmentTeamObserverImplementation::despawnMembersCloseToLambdaShuttle(SceneObject* lambdaShuttle, bool forcedCleanup) {
	Locker locker(&containmentTeamLock);

	for (int i = teamMembers.size() - 1; i >= 0; i--) {
		auto npc = teamMembers.get(i);
		if (npc != nullptr) {
			Locker npcLock(npc);
			if ((!npc->isInCombat() && npc->getWorldPosition().distanceTo(lambdaShuttle->getWorldPosition()) < 2) || forcedCleanup) {
				if (!npc->isDead()) {
					npc->destroyObjectFromWorld(true);
				}
				teamMembers.remove(i);
			} else if (!npc->isInCombat() && !npc->isDead() && !forcedCleanup) {
				npc->setFollowObject(lambdaShuttle);
			}
		} else {
			teamMembers.remove(i);
		}
	}
	return teamMembers.size() == 0;
}

void ContainmentTeamObserverImplementation::attack(TangibleObject* object) {
	Locker locker(&containmentTeamLock);
	for (int i = teamMembers.size() - 1; i >= 0; i--) {
		auto npc = teamMembers.get(i);
		if (npc != nullptr) {
			Locker npcLock(npc);

			if (!npc->isDead() && !npc->isInCombat()) {
				Locker clocker(object, npc);
				npc->setFollowObject(object);
				CombatManager::instance()->startCombat(npc, object);
			}
		}
	}
}