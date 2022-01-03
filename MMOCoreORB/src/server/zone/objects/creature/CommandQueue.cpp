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

//#define DEBUG_QUEUE

class QueueTask : public Task {

private:
	ManagedWeakReference<CreatureObject*> weakCreo;
	CommandQueueActionVector commandQ;

public:
	QueueTask(CreatureObject* creature, CommandQueueActionVector queue) {
		weakCreo = creature;
		commandQ = queue;
	}

	void run() {
		ManagedReference<CreatureObject*> creature = weakCreo.get();
		CommandQueueActionVector commandQueue = commandQ;

		if (creature == nullptr) {
			return;
		}

		try {
			Locker lock(creature);

#ifdef DEBUG_QUEUE
			creature->info("Command Queue Started ", true);
#endif

			if (commandQueue.size() == 0) {
				return;
			}

			ZoneServer* zoneServer = creature->getZoneServer();

			if (zoneServer == nullptr) {
				return;
			}

			ManagedReference<ObjectController*> objectController = zoneServer->getObjectController();

			if (objectController == nullptr) {
				return;
			}

			Time* nextAction = creature->getNextActionTime();

			if (nextAction->isFuture()) {
				if (!isScheduled()) {
					Time currTime;

					schedule(nextAction->getMiliTime() - currTime.getMiliTime());
#ifdef DEBUG_QUEUE
					creature->info("Next action is future rescheduling " + String::valueOf(nextAction->getMiliTime() - currTime.getMiliTime()), true);
#endif
				}

				creature->updateQueue();
				return;
			}

#ifdef DEBUG_QUEUE
			creature->info("Queue size = " + String::valueOf(commandQueue.size()), true);
#endif

			Reference<CommandQueueAction*> action = nullptr;
			const QueueCommand* queueCommand = nullptr;

			// Check queue for immediate actions, they get executed first
			for (int i = 0; i < commandQueue.size(); i++) {
				CommandQueueAction* immediateAction = commandQueue.get(i);

				if (immediateAction == nullptr)
					continue;

				queueCommand = objectController->getQueueCommand(immediateAction->getCommand());

				if (queueCommand != nullptr && queueCommand->getDefaultPriority() == QueueCommand::IMMEDIATE) {
#ifdef DEBUG_QUEUE
					creature->info("Immediate command selected", true);
#endif
					action = immediateAction;
					break;
				}
			}

			// None of the queue actions were immediate, select first command in the queue
			if (action == nullptr) {
#ifdef DEBUG_QUEUE
				creature->info("Selecting queue 0", true);
#endif
				action = commandQueue.get(0);
			}

			float time = 0.f;

			if (action != nullptr) {
				queueCommand = objectController->getQueueCommand(action->getCommand());

				if (queueCommand == nullptr)
					return;

				if (creature->hasPostureChangeDelay() && queueCommand->getDefaultPriority() != QueueCommand::IMMEDIATE && queueCommand->addToCombatQueue()) {
#ifdef DEBUG_QUEUE
					creature->info("Queue delayed by postureDelay", true);
#endif
					reschedule(500);
					return;
				} else if (creature->hasAttackDelay() && queueCommand->addToCombatQueue()) {
#ifdef DEBUG_QUEUE
					creature->info("Queue delayed by attackDelay", true);
#endif
					reschedule(500);
					return;
				}

				time = objectController->activateCommand(creature, action->getCommand(), action->getActionCounter(), action->getTarget(), action->getArguments());

#ifdef DEBUG_QUEUE
				creature->info("Command Queue activateCommand called -- time = " + String::valueOf(time) + ". ", true);
#endif

				for (int i = 0; i < commandQueue.size(); i++) {
					CommandQueueAction* actionToDelete = commandQueue.get(i);

					if (action == actionToDelete) {
						commandQueue.remove(i);

#ifdef DEBUG_QUEUE
						creature->info(" Queue action removed", true);
#endif
						break;
					}
				}

				nextAction->updateToCurrentTime();
				nextAction->addMiliTime((uint32)(time * 1000));
			}

			if (commandQueue.size() > 0) {
				reschedule(time * 1000);
			}

			creature->updateQueue();

#ifdef DEBUG_QUEUE
			creature->info("Command Queue Complete", true);
#endif
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
	//queueVector = new CommandQueueActionVector();
	state = WAITING;

	clearQueueActions(false);
}

void CommandQueue::handleRunningState() {
	ManagedReference<CreatureObject*> creature = weakCreature.get();

	if (creature == nullptr)
		return;

#ifdef DEBUG_QUEUE
	creature->info("CommandQueue - handleRunningState called", true);
#endif

	QueueTask* queueTask = new QueueTask(creature, queueVector);

	if (queueTask != nullptr)
		Core::getTaskManager()->executeTask(queueTask);
}

int CommandQueue::run() {
	ManagedReference<CreatureObject*> creature = weakCreature.get();

#ifdef DEBUG_QUEUE
	creature->info("CommandQueue - run() called with a state of " + String::valueOf(state) + ". ", true);
#endif

	if (creature == nullptr)
		return 0;

	switch (state) {
		case WAITING:
			if (queueVector.size() > 0) {
				state = RUNNING;
				handleRunningState();
				run();
			}
			break;
		case RUNNING:
			if (queueVector.size() == 0) {
				state = WAITING;
				break;
			}

			if (creature->hasPostureChangeDelay() || creature->hasAttackDelay()) {
				state = DELAYED;
				run();
				break;
			}

			break;
		case DELAYED:
			if (!creature->hasPostureChangeDelay() && !creature->hasAttackDelay()) {
				state = WAITING;
				run();
				break;
			}

			break;
		default:
			state = WAITING;
			run();
			break;
	}

	return 0;
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

	run();
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
