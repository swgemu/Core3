/*
 * StructureConstructionCompleteTask.h
 *
 *  Created on: Jun 13, 2011
 *      Author: crush
 */


#ifndef STRUCTURECONSTRUCTIONCOMPLETETASK_H_
#define STRUCTURECONSTRUCTIONCOMPLETETASK_H_

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/sessions/PlaceStructureSession.h"

class StructureConstructionCompleteTask : public Task {
	ManagedReference<CreatureObject*> creatureObject;

public:
	StructureConstructionCompleteTask(CreatureObject* creature) : Task() {
		creatureObject = creature;
	}

	void run() {
		Locker lock(creatureObject);

		ManagedReference<PlaceStructureSession*> session = creatureObject->getActiveSession(SessionFacadeType::PLACESTRUCTURE).castTo<PlaceStructureSession*>();

		if (session == NULL)
			return;

		session->completeSession();
	}
};

#endif /*STRUCTURECONSTRUCTIONCOMPLETETASK_H_*/
