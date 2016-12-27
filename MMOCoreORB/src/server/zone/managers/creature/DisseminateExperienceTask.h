/*
 * DisseminateExperienceTask.h
 *
 *  Created on: Oct 27, 2013
 *      Author: swgemu
 */

#ifndef DISSEMINATEEXPERIENCETASK_H_
#define DISSEMINATEEXPERIENCETASK_H_

#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/objects/tangible/TangibleObject.h"
#include "system/util/SynchronizedVector.h"

class DisseminateExperienceTask : public Task {
	ManagedWeakReference<TangibleObject*> lair;

	ThreatMap copyThreatMap;

	SynchronizedVector<ManagedReference<CreatureObject*> > spawnedCreatures;

public:

	DisseminateExperienceTask(TangibleObject* obj, ThreatMap* threatMap, SynchronizedVector<ManagedReference<CreatureObject*> >* creatures) : lair(obj),
		copyThreatMap(*threatMap), spawnedCreatures(*creatures) {
	}

	void run() {
		ManagedReference<TangibleObject*> strongRef = lair.get();

		if (strongRef == NULL)
			return;

		Locker locker(strongRef);

		PlayerManager* playerManager = strongRef->getZoneServer()->getPlayerManager();
		playerManager->disseminateExperience(strongRef, &copyThreatMap, &spawnedCreatures);
	}
};

#endif /* DISSEMINATEEXPERIENCETASK_H_ */
