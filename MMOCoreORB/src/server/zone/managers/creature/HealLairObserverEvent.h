/*
 * HealLairObserverEvent.h
 *
 * Created on: 10/12/2011
 * Author: victor
 *
 */

#ifndef HEALLAIROBSERVEREVENT_H_
#define HEALLAIROBSERVEREVENT_H_

#include "server/zone/managers/creature/LairObserver.h"
#include "server/zone/objects/tangible/TangibleObject.h"
#include "server/zone/objects/creature/ai/AiAgent.h"

namespace server {
namespace zone {
namespace managers {
namespace creature {

class HealLairObserverEvent : public Task {
	ManagedWeakReference<TangibleObject*> weakLair;
	ManagedWeakReference<TangibleObject*> weakAttacker;
	ManagedWeakReference<LairObserver*> weakObserver;
	ManagedWeakReference<AiAgent*> weakHealer;

public:
	HealLairObserverEvent() {
	}

	void run() {
		ManagedReference<TangibleObject*> lair = weakLair.get();
		ManagedReference<AiAgent*> healerAgent = weakHealer.get();
		ManagedReference<LairObserver*> lairObserver = weakObserver.get();

		// Logger::console.info(true) << "HealLairEvent called -- lair: " << lair->getDisplayedName() << " ID: " << lair->getObjectID();

		if (lair == nullptr || healerAgent == nullptr || lairObserver == nullptr) {
			clearTaskObjects();
			return;
		}

		ManagedReference<TangibleObject*> attacker = weakAttacker.get();

		Locker locker(lair);

		// Logger::console.info(true) << "HealLairEvent -- attempting to heal lair";

		// Attempt the heal, if the agent is out of range it will fail and repeat until successful
		if (!lairObserver->healLair(lair, healerAgent, attacker)) {
			reschedule(1000);
			return;
		}

		// Heal was succesful, clear healer and attacker
		clearTaskObjects();
	}

	void setLair(TangibleObject* lair) {
		weakLair = lair;
	}

	void setLairObserver(LairObserver* observer) {
		weakObserver = observer;
	}

	void setAttacker(TangibleObject* attacker) {
		weakAttacker = attacker;
	}

	void setHealerAgent(AiAgent* healer) {
		weakHealer = healer;
	}

	bool isActivelyHealing() {
		return (weakHealer.get() != nullptr);
	}

	void clearTaskObjects() {
		weakHealer = nullptr;
		weakAttacker = nullptr;
	}
};

} // namespace creature
} // namespace managers
} // namespace zone
} // namespace server

using namespace server::zone::managers::creature;

#endif /* HEALLAIROBSERVEREVENT_H_ */
