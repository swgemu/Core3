
#ifndef STRUCTURESETOWNERTASK_H_
#define STRUCTURESETOWNERTASK_H_

#include "server/zone/objects/structure/StructureObject.h"

class StructureSetOwnerTask : public Task {
	ManagedReference<StructureObject*> structure;
	uint64 newOwnerID;

public:
	StructureSetOwnerTask(StructureObject* structureObject, uint64 newID) : Task() {
		structure = structureObject;
		newOwnerID = newID;
	}

	void run() {
		if (structure == NULL)
			return;

		Locker locker(structure);

		structure->setOwner(newOwnerID);
	}
};

#endif /* STRUCTURESETOWNERTASK_H_ */
