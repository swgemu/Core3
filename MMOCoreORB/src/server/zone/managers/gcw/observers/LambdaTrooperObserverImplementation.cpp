/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.
 */

#include "server/zone/managers/combat/CombatManager.h"
#include "server/zone/managers/gcw/observers/LambdaTrooperObserver.h"
#include "server/zone/objects/creature/ai/AiAgent.h"
#include "server/zone/objects/tangible/TangibleObject.h"

int LambdaTrooperObserverImplementation::notifyObserverEvent(unsigned int eventType, Observable* observable, ManagedObject* arg1, int64 arg2) {
	ManagedReference<TangibleObject*> attacker = cast<TangibleObject*>(arg1);
	if (attacker == nullptr) {
		return 0;
	}

	for (int i = 0; i < containmentTeam->size(); i++) {
		AiAgent* npc = containmentTeam->get(i).get();
		if (npc != nullptr) {
			Locker locker(npc);
			if (!npc->isDead() && !npc->isInCombat()) {
				npc->setFollowObject(attacker);
				CombatManager::instance()->startCombat(npc, attacker);
			}
		}
	}

	return 1;
}