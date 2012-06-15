/*
 * CommandQueueTask.h
 *
 *  Created on: Jun 14, 2012
 *      Author: da
 */

#ifndef COMMANDQUEUETASK_H_
#define COMMANDQUEUETASK_H_

#include "server/zone/objects/creature/CreatureObject.h"
#include "engine/core/ManagedReference.h"
#include "engine/core/ManagedWeakReference.h"

class CommandQueueTask : public Task {
	ManagedWeakReference<CreatureObject*> creature;
	uint32 attackCRC;
	uint64 targetID;
	String args;

public:
	CommandQueueTask(CreatureObject* pl, uint32 crc, uint64 oid, String a = "") : Task() {
		creature = pl;
		attackCRC = crc;
		targetID = oid;
		args = a;
	}

	void run() {
		ManagedReference<CreatureObject*> strongRef = creature.get();
		if (strongRef == NULL)
			return;

		Locker _locker(strongRef);

		strongRef->enqueueCommand(attackCRC, 0, targetID, args);
	}

};


#endif /* COMMANDQUEUETASK_H_ */
