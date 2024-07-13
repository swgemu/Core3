/*
 * HealLairObserverEvent.h
 *
 *  Created on: 10/12/2011
 *      Author: victor
 */

#ifndef HEALLAIROBSERVEREVENT_H_
#define HEALLAIROBSERVEREVENT_H_

#include "server/zone/managers/creature/LairObserver.h"
#include "server/zone/objects/tangible/TangibleObject.h"

namespace server {
namespace zone {
namespace managers {
namespace creature {

class HealLairObserverEvent : public Task {
	ManagedWeakReference<TangibleObject*> weakLair;
	ManagedWeakReference<TangibleObject*> weakAttacker;
	ManagedWeakReference<LairObserver*> weakObserver;

public:
	HealLairObserverEvent(TangibleObject* obj, TangibleObject* attacker, LairObserver* observer) {
		weakLair = obj;
		weakAttacker = attacker;
		weakObserver = observer;
	}

	void run() {
		ManagedReference<TangibleObject*> lair = weakLair.get();

		if (lair == nullptr) {
			return;
		}

		ManagedReference<TangibleObject*> attacker = weakAttacker.get();
		ManagedReference<LairObserver*> lairObserver = weakObserver.get();

		if (lairObserver == nullptr) {
			return;
		}

		Locker locker(lair);

		lairObserver->healLair(lair, attacker);

		// No looping heal
		// if (strongRef->getConditionDamage() > 0)
		//	strongObserver->checkForHeal(strongRef, strongAttackerRef, true);
	}

	void setAttacker(TangibleObject* attacker) {
		weakAttacker = attacker;
	}
};

} // namespace creature
} // namespace managers
} // namespace zone
} // namespace server

using namespace server::zone::managers::creature;

#endif /* HEALLAIROBSERVEREVENT_H_ */
