/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.
 */

#include "server/zone/managers/gcw/observers/ContainmentTeamObserver.h"

#include "server/zone/managers/combat/CombatManager.h"
#include "server/zone/objects/creature/ai/AiAgent.h"
#include "server/zone/objects/tangible/TangibleObject.h"

int ContainmentTeamObserverImplementation::notifyObserverEvent(unsigned int eventType, Observable* observable, ManagedObject* arg1, int64 arg2) {
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

void ContainmentTeamObserverImplementation::removeMember(unsigned int teamMemberIndex) {
	Locker locker(&containmentTeamLock);
	teamMembers.remove(teamMemberIndex);
}

bool ContainmentTeamObserverImplementation::despawnMembersCloseToLambdaShuttle(SceneObject* lambdaShuttle, bool forcedCleanup) {
	// Do not lock containmentTeamLock in this method to avoid deadlocks. Use the minimal locking methods above.
	for (int i = size() - 1; i >= 0; i--) {
		auto npc = getMember(i);
		if (npc != nullptr) {
			Locker npcLock(npc);
			if ((!npc->isInCombat() && npc->getWorldPosition().distanceTo(lambdaShuttle->getWorldPosition()) < 2) || forcedCleanup) {
				if (!npc->isDead()) {
					npc->destroyObjectFromWorld(true);
				}
				removeMember(i);
			} else if (!npc->isInCombat() && !npc->isDead() && !forcedCleanup) {
				npc->setFollowObject(lambdaShuttle);
			}
		} else {
			removeMember(i);
		}
	}
	return teamMembers.size() == 0;
}

void ContainmentTeamObserverImplementation::attack(TangibleObject* object) {
	// Do not lock containmentTeamLock in this method to avoid deadlocks. Use the minimal locking methods above.
	for (int i = size() - 1; i >= 0; i--) {
		auto npc = getMember(i);
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