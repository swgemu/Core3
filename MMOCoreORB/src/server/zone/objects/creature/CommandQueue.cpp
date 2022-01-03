/*
 				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#include "CommandQueue.h"
#include "server/zone/managers/objectcontroller/ObjectController.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/commands/QueueCommand.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/objects/creature/variables/CommandQueueActionVector.h"
#include "server/zone/packets/object/CommandQueueRemove.h"
#include "server/zone/packets/object/CommandQueueAdd.h"

// #define DEBUG_QUEUE

class QueueTask : public Task {

private:
	ManagedWeakReference<CreatureObject*> weakCreo;

public:
	QueueTask(CreatureObject* creature) {
		weakCreo = creature;
	}

	void run() {
		ManagedReference<CreatureObject*> creature = weakCreo.get();

		if (creature == nullptr) {
			return;
		}

		try {

#ifdef DEBUG_QUEUE
			creature->info("Queue Task called", true);
#endif
			creature->updateQueue();

		} catch (Exception& e) {
			creature->error(e.getMessage());
			e.printStackTrace();
		} catch (...) {
			throw;
		}
	}
};

void CommandQueue::initialize(CreatureObject* creature) {
	if (creature == nullptr) {
		return;
	}

#ifdef DEBUG_QUEUE
	if (creature->isPlayerCreature())
		creature->info("CommandQueue initialize called ", true);
#endif

	weakCreature = creature;
	state = WAITING;

	clearQueueActions(false);
}

void CommandQueue::removeAction(CommandQueueAction* actionToDelete) {
	if (actionToDelete == nullptr)
		return;

	for (int i = 0; i < queueVector.size(); i++) {
		CommandQueueAction* action = queueVector.get(i);

		if (action == actionToDelete) {
			queueVector.remove(i);

#ifdef DEBUG_QUEUE
			creature->info(" Queue action removed", true);
#endif
			break;
		}
	}
}

int CommandQueue::handleDelayState() {
	ManagedReference<CreatureObject*> creature = weakCreature.get();

	if (creature == nullptr || queueVector.size() == 0)
		return 0;

	Time* nextAction = creature->getNextActionTime();

	if (nextAction == nullptr)
		return 0;

	if (nextAction->isFuture()) {
		Time currTime;
		int nextActionTime = nextAction->getMiliTime() - currTime.getMiliTime();

#ifdef DEBUG_QUEUE
	creature->info("Next action is future returning time of " + String::valueOf(nextActionTime), true);
#endif

		return nextActionTime;
	}

	ZoneServer* zoneServer = creature->getZoneServer();

	if (zoneServer == nullptr) {
		return 0;
	}

	ManagedReference<ObjectController*> objectController = zoneServer->getObjectController();

	if (objectController == nullptr) {
		return 0;
	}

	Reference<CommandQueueAction*> action = nullptr;
	const QueueCommand* queueCommand = nullptr;

	// Check queue for immediate or non combat queue actions
	for (int i = 0; i < queueVector.size(); i++) {
		CommandQueueAction* nonDelayAction = queueVector.get(i);

		if (nonDelayAction == nullptr)
			continue;

		queueCommand = objectController->getQueueCommand(nonDelayAction->getCommand());

		if (queueCommand != nullptr && (queueCommand->getDefaultPriority() == QueueCommand::IMMEDIATE || !queueCommand->addToCombatQueue())) {

			action = nonDelayAction;
			break;
		}
	}

	// None of the queue actions were immediate, select first command in the queue
	if (action == nullptr) {
		return DELAYCHECK;
	}

	float time = 0.f;

	time = objectController->activateCommand(creature, action->getCommand(), action->getActionCounter(), action->getTarget(), action->getArguments());

#ifdef DEBUG_QUEUE
	creature->info("Command Queue DELAYED activateCommand called -- time = " + String::valueOf(time) + ". ", true);
#endif

	removeAction(action);

	return time;
}

int CommandQueue::handleRunningState() {
	ManagedReference<CreatureObject*> creature = weakCreature.get();

	if (creature == nullptr || queueVector.size() == 0)
		return 0;

#ifdef DEBUG_QUEUE
	creature->info("CommandQueue - handleRunningState called", true);
#endif

	Time* nextAction = creature->getNextActionTime();

	if (nextAction == nullptr)
		return 0;

	if (nextAction->isFuture()) {
		Time currTime;
		int nextActionTime = nextAction->getMiliTime() - currTime.getMiliTime();

#ifdef DEBUG_QUEUE
	creature->info("Next action is future returning time of " + String::valueOf(nextActionTime), true);
#endif

		return nextActionTime;
	}

	ZoneServer* zoneServer = creature->getZoneServer();

	if (zoneServer == nullptr) {
		return 0;
	}

	ManagedReference<ObjectController*> objectController = zoneServer->getObjectController();

	if (objectController == nullptr) {
		return 0;
	}

	Reference<CommandQueueAction*> action = nullptr;
	const QueueCommand* queueCommand = nullptr;

	// Check queue for immediate actions, they get executed first
	for (int i = 0; i < queueVector.size(); i++) {
		CommandQueueAction* immediateAction = queueVector.get(i);

		if (immediateAction == nullptr)
			continue;

		queueCommand = objectController->getQueueCommand(immediateAction->getCommand());

		if (queueCommand != nullptr && queueCommand->getDefaultPriority() == QueueCommand::IMMEDIATE) {

			action = immediateAction;
			break;
		}
	}

	// None of the queue actions were immediate, select first command in the queue
	if (action == nullptr) {
		action = queueVector.get(0);
	}

	float time = 0.f;

	if (action != nullptr) {
		queueCommand = objectController->getQueueCommand(action->getCommand());

		if (queueCommand == nullptr)
			return time;

		if (queueCommand->addToCombatQueue()) {
			if (creature->hasPostureChangeDelay() && queueCommand->getDefaultPriority() != QueueCommand::IMMEDIATE) {

				return DELAYCHECK;
			} else if (creature->hasAttackDelay()) {

				return DELAYCHECK;
			}
		}

		time = objectController->activateCommand(creature, action->getCommand(), action->getActionCounter(), action->getTarget(), action->getArguments());

#ifdef DEBUG_QUEUE
		creature->info("Command Queue activateCommand called -- time = " + String::valueOf(time) + ". ", true);
#endif

		removeAction(action);

		nextAction->updateToCurrentTime();
		nextAction->addMiliTime((uint32)(time * 1000));
	}

	return time;
}

void CommandQueue::run() {
	ManagedReference<CreatureObject*> creature = weakCreature.get();

#ifdef DEBUG_QUEUE
	creature->info("CommandQueue - run() called with a state of " + String::valueOf(state) + ". ", true);
#endif

	if (creature == nullptr)
		return;

	Locker lock(creature);

	int time = 0.f;

	switch (state) {
		case WAITING:
			if (queueVector.size() > 0) {
				state = RUNNING;
				run();
				return;
			}
		case RUNNING: {
			if (queueVector.size() == 0) {
				state = WAITING;
				break;
			}

			if (creature->hasAttackDelay() || creature->hasPostureChangeDelay()) {
				state = DELAY;
				run();
				break;
			}

			time = handleRunningState();

			QueueTask* queueTask = new QueueTask(creature);

			if (queueTask != nullptr) {
#ifdef DEBUG_QUEUE
				creature->info("RUNNING Que Task Scheduled", true);
#endif
				queueTask->schedule(time);
			}
			break;
		}
		case DELAY: {
			if (!creature->hasAttackDelay() && !creature->hasPostureChangeDelay()) {
				state = WAITING;
				run();
				break;
			}

			time = handleDelayState();

			if (time == 0)
				time += DELAYCHECK;

			QueueTask* queueTask = new QueueTask(creature);

			if (queueTask != nullptr) {
#ifdef DEBUG_QUEUE
				creature->info("DELAY Que Task Scheduled", true);
#endif
				queueTask->schedule(time);
			}
		}
		default:
			state = WAITING;
			break;
	}

#ifdef DEBUG_QUEUE
	creature->info("CommandQueue - run() finished with a state of " + String::valueOf(state) + ". ", true);
#endif
}

void CommandQueue::clearQueueAction(unsigned int actioncntr, float timer, unsigned int tab1, unsigned int tab2) {
	ManagedReference<CreatureObject*> creature = weakCreature.get();

	if (actioncntr == 0 || creature == nullptr || !creature->isPlayerCreature())
		return;

	BaseMessage* queuemsg = new CommandQueueRemove(creature, actioncntr, timer, tab1, tab2);
	creature->sendMessage(queuemsg);
}

void CommandQueue::enqueueCommand(unsigned int actionCRC, unsigned int actionCount, uint64 targetID, const UnicodeString& arguments, int priority, int compareCounter) {
	ManagedReference<CreatureObject*> creature = weakCreature.get();

	if (creature == nullptr) {
		return;
	}

#ifdef DEBUG_QUEUE
	creature->info("CommandQueue - enqueueCommand Called", true);
#endif

	ZoneServer* zoneServer = creature->getZoneServer();

	if (zoneServer == nullptr)
		return;

	ManagedReference<ObjectController*> objectController = zoneServer->getObjectController();

	if (objectController == nullptr)
		return;

	const QueueCommand* queueCommand = objectController->getQueueCommand(actionCRC);

	if (queueCommand == nullptr) {
		return;
	}

	if (queueCommand->addToCombatQueue()) {
		creature->removeBuff(STRING_HASHCODE("private_feign_buff"));
	}

	if (priority < 0) {
		priority = queueCommand->getDefaultPriority();
	}

	Reference<CommandQueueAction*> action = nullptr;

	if (queueVector.size() > 15 && priority != QueueCommand::FRONT) {
		clearQueueAction(actionCount, 0, 0, 0);

		return;
	}

	action = new CommandQueueAction(creature, targetID, actionCRC, actionCount, arguments);

	if (compareCounter >= 0)
		action->setCompareToCounter((int)compareCounter);

#ifdef DEBUG_QUEUE
	creature->info("Enquing Command " + queueCommand->getQueueCommandName() + ": with priority - " + String::valueOf(priority) + " compareCount of " + String::valueOf(compareCounter), true);
#endif

	Time* nextAction = creature->getNextActionTime();

	if (queueVector.size() != 0 || (nextAction != nullptr && !nextAction->isPast())) {
		if (priority == QueueCommand::FRONT) {
			action->setCompareToCounter(queueVector.get(0)->getCompareToCounter() - 1);
		}

		queueVector.put(action.get());

#ifdef DEBUG_QUEUE
		creature->info("Queue Vector size after added command: " + String::valueOf(queueVector.size()), true);
#endif
	} else {
		nextAction->updateToCurrentTime();

		queueVector.put(action.get());

#ifdef DEBUG_QUEUE
		creature->info("Queue Vector size after added command: " + String::valueOf(queueVector.size()), true);
#endif
	}

	if (state == WAITING) {
		run();
	}
}

void CommandQueue::sendCommand(uint32 crc, const UnicodeString& args, uint64 targetID, int priority) {
	ManagedReference<CreatureObject*> creature = weakCreature.get();

	if (creature == nullptr)
		return;

	uint32 nextCounter = creature->incrementLastActionCounter();
	CommandQueueAdd* msg = new CommandQueueAdd(creature, crc, nextCounter);
	creature->sendMessage(msg);

	int compareCnt = -1;
	if (queueVector.size() == 0 || priority == QueueCommand::FRONT)
		compareCnt = 0;
	else if (priority == QueueCommand::NORMAL)
		compareCnt = queueVector.get(queueVector.size() - 1)->getCompareToCounter() + 1;

	enqueueCommand(crc, nextCounter, targetID, args, priority, compareCnt);
}

void CommandQueue::clearQueueActions(bool combatOnly) {
	ManagedReference<CreatureObject*> creature = weakCreature.get();

	if (creature == nullptr)
		return;

	for (int i = queueVector.size() - 1; i >= 0; i--) {
		CommandQueueAction* command = queueVector.get(i);

		if (command == nullptr)
			continue;

		if (combatOnly) {
			ZoneServer* zoneServer = creature->getZoneServer();
			if (zoneServer == nullptr)
				continue;

			ObjectController* objectController = zoneServer->getObjectController();
			if (objectController == nullptr)
				continue;

			const QueueCommand* qc = objectController->getQueueCommand(command->getCommand());
			if (qc == nullptr)
				continue;

			if (!qc->isCombatCommand())
				continue;
		}

		if (command->getActionCounter() != 0)
			clearQueueAction(command->getActionCounter(), 0, 0, 0);

		queueVector.remove(i);
	}
}

void CommandQueue::deleteQueueAction(uint32 actionCount) {

	for (int i = 0; i < queueVector.size(); ++i) {
		CommandQueueAction* action = queueVector.get(i);

		if (action->getActionCounter() == actionCount) {
			queueVector.remove(i);
			break;
		}
	}

	run();
}
