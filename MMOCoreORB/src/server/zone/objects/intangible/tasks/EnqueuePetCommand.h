/*
 * EnqueuePetCommand.h
 *
 *  Created on: Dec 18, 2013
 *      Author: TheAnswer
 */

#ifndef ENQUEUEPETCOMMAND_H_
#define ENQUEUEPETCOMMAND_H_

#include "engine/engine.h"
#include "server/zone/objects/creature/CreatureObject.h"

class EnqueuePetCommand : public Task {
	ManagedReference<CreatureObject*> pet;
	uint32 commandCRC;
	UnicodeString arguments;
	uint64 target;
	int priority;
public:
	EnqueuePetCommand(CreatureObject* pet, uint32 command, const String& args, uint64 target, int priority = -1) {
		this->pet = pet;
		commandCRC = command;
		arguments = args;
		this->target = target;
		this->priority = priority;
	}

	void run() {
		Locker locker(pet);

		pet->enqueueCommand(commandCRC, 0, target, arguments, priority);
	}
};


#endif /* ENQUEUEPETCOMMAND_H_ */
