/*
 * DestroyStructureTask.h
 *
 *  Created on: Jun 29, 2013
 *      Author: TheAnswer
 */

#ifndef DESTROYQUESTSTRUCTURETASK_H_
#define DESTROYQUESTSTRUCTURETASK_H_

#include "engine/engine.h"
#include "server/zone/objects/structure/StructureObject.h"
#include "server/zone/objects/cell/CellObject.h"
#include "server/zone/objects/tangible/components/vendor/VendorDataComponent.h"
#include "server/zone/managers/structure/tasks/DestroyStructureTask.h"
#include "server/zone/packets/object/PlayClientEffectObjectMessage.h"
#include "server/zone/packets/scene/PlayClientEffectLocMessage.h"

class DestroyQuestStructureTask: public Task {
protected:
	ManagedReference<StructureObject*> structureObject;

public:
	DestroyQuestStructureTask(StructureObject* structure) {
		structureObject = structure;
	}

	void run() {
		PlayClientEffectObjectMessage* explode = new PlayClientEffectObjectMessage(structureObject, "clienteffect/lair_damage_heavy.cef", "");
		structureObject->broadcastMessage(explode, false);

		PlayClientEffectLoc* explodeLoc = new PlayClientEffectLoc("clienteffect/lair_damage_heavy.cef", structureObject->getZone()->getZoneName(), structureObject->getPositionX(), structureObject->getPositionZ(), structureObject->getPositionY());
		structureObject->broadcastMessage(explodeLoc, false);

		Reference<Task*> task = new DestroyStructureTask(structureObject);
		task->execute();
	}
};

#endif /* DESTROYQUESTSTRUCTURETASK_H_ */
