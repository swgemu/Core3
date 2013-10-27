/*
 * DisseminateExperienceTask.h
 *
 *  Created on: Oct 27, 2013
 *      Author: swgemu
 */

#ifndef DISSEMINATEEXPERIENCETASK_H_
#define DISSEMINATEEXPERIENCETASK_H_

#include "engine/engine.h"
#include "server/zone/managers/creature/LairObserver.h"
#include "server/zone/objects/tangible/TangibleObject.h"
class DisseminateExperienceTask : public Task {

	ManagedWeakReference<TangibleObject*> lair;
	ManagedWeakReference<LairObserver*> observer;
	ManagedWeakReference<TangibleObject*> attacker;

public:

	DisseminateExperienceTask(TangibleObject* obj, TangibleObject* attacker, LairObserver* thisObserver) {
		 lair = obj;
		 this->attacker = attacker;
		 observer = thisObserver;
	}

	void run() {
		ManagedReference<TangibleObject*> strongRef = lair.get();

		if (strongRef == NULL)
			return;


		ManagedReference<LairObserver*> strongObserver = observer.get();
		ManagedReference<TangibleObject*> strongAttackerRef = attacker.get();

		if (strongObserver == NULL)
			return;

		Locker locker(strongRef);

		ThreatMap* threatMap = strongRef->getThreatMap();

		ThreatMap copyThreatMap(*threatMap);
		threatMap->removeObservers();
		threatMap->removeAll(); // we can clear the original one

		PlayerManager* playerManager = strongRef->getZoneServer()->getPlayerManager();
		playerManager->disseminateExperience(strongRef, &copyThreatMap);
	}
};


#endif /* DISSEMINATEEXPERIENCETASK_H_ */
