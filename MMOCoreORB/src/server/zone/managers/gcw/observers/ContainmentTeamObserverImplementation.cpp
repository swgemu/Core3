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
	if (teamMemberIndex < teamMembers.size()) {
		return teamMembers.get(teamMemberIndex);
	} else {
		return nullptr;
	}
}

void ContainmentTeamObserverImplementation::removeMember(unsigned int teamMemberIndex) {
	Locker locker(&containmentTeamLock);
	if (teamMemberIndex < teamMembers.size()) {
		teamMembers.remove(teamMemberIndex);
	}
}

bool ContainmentTeamObserverImplementation::despawnMembersCloseToLambdaShuttle(const Vector3& landingPosition, bool forcedCleanup) {
	// Do not lock containmentTeamLock in this method to avoid deadlocks. Use the minimal locking methods above.
	for (int i = size() - 1; i >= 0; i--) {
		auto npc = getMember(i);
		if (npc != nullptr) {
			Locker npcLock(npc);
			auto distance = npc->getWorldPosition().distanceTo(landingPosition);
			if ((!npc->isInCombat() && distance < 4) || forcedCleanup) {
				if (!npc->isDead()) {
					npc->destroyObjectFromWorld(true);
				}
				removeMember(i);
			} else if (!npc->isInCombat() && !npc->isDead() && !forcedCleanup) {
				npc->getCooldownTimerMap()->updateToCurrentAndAddMili("reaction_chat", 60000);
				npc->setHomeLocation(landingPosition.getX(), landingPosition.getZ(), landingPosition.getY());
				npc->leash();
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