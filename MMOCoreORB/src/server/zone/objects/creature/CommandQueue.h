/*
		Copyright <SWGEmu>
	See file COPYING for copying conditions.*/

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

//#define DEBUG_QUEUE

class CommandQueueTask;

class CommandQueue : public Object {
	mutable Mutex queueMutex;

	enum State {
		NONE, WAITING, RUNNING, DELAY
	};

	WeakReference<CreatureObject*> weakCreature;
	CommandQueueActionVector queueVector;
	Reference<CommandQueueTask*> queueTask;
	State state = NONE;
	static const int DEFAULTTIME = 100;
#ifdef DEBUG_QUEUE
	uint64 runNumber = 0;
	Time lastRun;
#endif // DEBUG_QUEUE

private:
	void removeAction(CommandQueueAction* actionToDelete);
	CommandReference<CommandQueueAction*> getNextAction();

public:
	CommandQueue(CreatureObject* creature);

	~CommandQueue();

	void run();
	void handleRunningState();

	int checkActions(CreatureObject* creature);
	void enqueueCommand(unsigned int actionCRC, unsigned int actionCount, uint64 targetID, const UnicodeString& arguments, int priority, int compareCounter);
	void sendCommand(uint32 crc, const UnicodeString& args, uint64 targetID, int priority);
	void clearQueueAction(unsigned int actioncntr, float timer, unsigned int tab1, unsigned int tab2);
	void clearQueueActions(bool combatOnly);

	int getQueueSize() const {
		return queueVector.size();
	}

	void deleteQueueAction(uint32 actionCount);

	String toString() const;

	String toStringData() const {
		return toString();
	}
};

class CommandQueueTask : public Task {
	private:
		WeakReference<CommandQueue*> weakQueue;

	public:
		CommandQueueTask(CommandQueue* queue) {
			weakQueue = queue;
		}

	void run() {

		auto commandQueue = weakQueue.get();

		if (commandQueue == nullptr) {
#ifdef DEBUG_QUEUE
			Logger::console.info(true) << __PRETTY_FUNCTION__ << ":" << __LINE__ << " weakQueue.get() == nullptr!";
#endif // DEBUG_QUEUE
			return;
		}

		try {
#ifdef DEBUG_QUEUE
			Logger::console.info(true) << "######################################## Task Start";
#endif // DEBUG_QUEUE
			commandQueue->run();
#ifdef DEBUG_QUEUE
			Logger::console.info(true) << "######################################## Task Complete\n";
#endif // DEBUG_QUEUE

		} catch (Exception& e) {
			e.printStackTrace();
		} catch (...) {
			throw;
		}
	}
};

#endif /* COMMANDQUEUE_H_ */
