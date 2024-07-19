/*
 * LairAggroTask.h
 *
 * Created on: Jul 6, 2013
 * Author: swgemu
 */

#ifndef LAIRAGGROTASK_H_
#define LAIRAGGROTASK_H_

#include "server/zone/managers/creature/LairObserver.h"
#include "server/zone/objects/tangible/TangibleObject.h"

class LairAggroTask : public Task {
	ManagedWeakReference<TangibleObject*> weakLair;
	ManagedWeakReference<LairObserver*> weakObserver;
	ManagedWeakReference<TangibleObject*> weakAttacker;
	bool allAttack;

public:
	LairAggroTask(TangibleObject* lair, TangibleObject* attacker, LairObserver* lairObserver, bool allAgentsAttack) {
		weakLair = lair;
		weakObserver = lairObserver;
		weakAttacker = attacker;
		allAttack = allAgentsAttack;
	}

	void run() {
		ManagedReference<TangibleObject*> lair = weakLair.get();

		if (lair == nullptr) {
			return;
		}

		ManagedReference<LairObserver*> lairObserver = weakObserver.get();
		ManagedReference<TangibleObject*> attacker = weakAttacker.get();

		if (lairObserver == nullptr || attacker == nullptr) {
			return;
		}

		Locker locker(lair);

		lairObserver->doAggro(lair, attacker, allAttack);
	}
};

#endif /* LAIRAGGROTASK_H_ */
