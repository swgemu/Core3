/*
* CommandQueue.h
*
* Created on: Jan. 1, 2022
* Author: Hakry
*/

#ifndef COMMANDQUEUE_H_
#define COMMANDQUEUE_H_

#include "engine/engine.h"
#include "server/zone/objects/creature/variables/CommandQueueActionVector.h"

class CommandQueue {
	enum State {
		WAITING, RUNNING, POSTUREDELAYED, ATTACKDELAYED
	};

	ManagedWeakReference<CreatureObject*> weakCreature;
	WeakReference<CommandQueueActionVector*> queue;
	State state = WAITING;

public:
	int run();
	void handleRunningState(CreatureObject* creature, Reference<CommandQueueActionVector*> queue);

	void enqueueCommand(unsigned int actionCRC, unsigned int actionCount, uint64 targetID, const UnicodeString& arguments, int priority, int compareCounter);
	void sendCommand(uint32 crc, const UnicodeString& args, uint64 targetID, int priority);
	void clearQueueAction(unsigned int actioncntr, float timer, unsigned int tab1, unsigned int tab2);
	void clearQueueActions(bool combatOnly);
	int getQueueSize();
	void deleteQueueAction(uint32 actionCount);
};

#endif /* COMMANDQUEUE_H_ */