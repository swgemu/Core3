/*
		Copyright <SWGEmu>
	See file COPYING for copying conditions.*/

/*
* CommandQueue.cpp
*
* Created on: Jan. 1, 2022
* Author: Hakry
*/

#include "CommandQueue.h"
#include "server/zone/managers/objectcontroller/ObjectController.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/commands/QueueCommand.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/objects/creature/variables/CommandQueueActionVector.h"
#include "server/zone/packets/object/CommandQueueRemove.h"
#include "server/zone/packets/object/CommandQueueAdd.h"
#include "templates/params/ObserverEventType.h"

CommandQueue::CommandQueue(CreatureObject* creature) {
#ifdef DEBUG_QUEUE
	Logger::console.info(true) << __FUNCTION__ << "() called on " << toString();
#endif // DEBUG_QUEUE
	if (creature == nullptr) {
		return;
	}

	weakCreature = creature;
	queueTask = new CommandQueueTask(this);
	state = WAITING;

	clearQueueActions(false);
#ifdef DEBUG_QUEUE
	runNumber = 1;
	Logger::console.info(true) << __FUNCTION__ << "(" << creature << ") called on " << toString();
#endif // DEBUG_QUEUE
}

CommandQueue::~CommandQueue() {
#ifdef DEBUG_QUEUE
	Logger::console.info(true) << __FUNCTION__ << "() called on " << toString();
#endif // DEBUG_QUEUE
	if (queueTask != nullptr) {
		queueTask->cancel();
		queueTask = nullptr;
	}
}

void CommandQueue::removeAction(CommandQueueAction* actionToDelete) {
	if (actionToDelete == nullptr)
		return;

	Locker guard(&queueMutex);

	for (int i = 0; i < queueVector.size(); i++) {
		CommandQueueAction* action = queueVector.get(i);

		if (action == actionToDelete) {
			queueVector.remove(i);

#ifdef DEBUG_QUEUE
			Logger::console.info(true) << " Queue action removed from " << toString();
#endif
			break;
		}
	}
}

CommandReference<CommandQueueAction*> CommandQueue::getNextAction() {
	auto creature = weakCreature.get();

	if (creature == nullptr || queueVector.size() == 0) {
		return nullptr;
	}

	auto zoneServer = creature->getZoneServer();

	if (zoneServer == nullptr) {
		return nullptr;
	}

	auto objectController = zoneServer->getObjectController();

	if (objectController == nullptr) {
		return nullptr;
	}

	bool hasFront = false;
	int frontAction = -1;

	// Check queue for immediate actions, they get executed first
	for (int i = 0; i < queueVector.size(); i++) {
		auto immediateAction = queueVector.get(i);

		if (immediateAction == nullptr)
			continue;

		auto queueCommand = objectController->getQueueCommand(immediateAction->getCommand());

		if (queueCommand != nullptr) {
			int priority = queueCommand->getDefaultPriority();

			if (priority == QueueCommand::IMMEDIATE && (!creature->hasAttackDelay() || !queueCommand->addToCombatQueue())) {
				return immediateAction;
			}

			if (!hasFront && priority == QueueCommand::FRONT) {
				hasFront = true;
				frontAction = i;
			}
		}
	}

	// No immediate commands, however a front command is present
	if (hasFront && frontAction > -1) {
		return queueVector.get(frontAction);
	}

	// None of the queue actions were immediate, select first command in the queue
	return queueVector.get(0);
}

int CommandQueue::handleRunningState() {
	auto creature = weakCreature.get();

	if (creature == nullptr) {
		return 0;
	}

	Locker guard(&queueMutex);

#ifdef DEBUG_QUEUE
	creature->info(true) << "CommandQueue - handleRunningState called on " << toString();
#endif

	if (queueVector.size() <= 0)
		return 0;

	ZoneServer* zoneServer = creature->getZoneServer();

	if (zoneServer == nullptr) {
		return 0;
	}

	auto objectController = zoneServer->getObjectController();

	if (objectController == nullptr) {
		return 0;
	}

	auto action = getNextAction();

	if (action == nullptr) {
		return 0;
	}

	guard.release();

	float time = 0.f;

	auto queueCommand = objectController->getQueueCommand(action->getCommand());

	if (queueCommand == nullptr)
		return time;

	int priority = queueCommand->getDefaultPriority();

#ifdef DEBUG_QUEUE
	creature->info(true) << "Command Name: " << queueCommand->getName() << " with a priority of " << priority;
#endif

	Locker lock(creature);

	Time* nextActionTime = creature->getNextActionTime();

	if (nextActionTime == nullptr)
		return time;

	Time currTime;
	int remainingActionTime = nextActionTime->getMiliTime() - currTime.getMiliTime();

	// Auto attack timer only applies to players
	if (creature->isPlayerCreature()) {
#ifdef DEBUG_QUEUE
		creature->info(true) << "Remaining action time = " << remainingActionTime;
#endif

		CooldownTimerMap* cooldownTimerMap = creature->getCooldownTimerMap();

		if (cooldownTimerMap != nullptr && !cooldownTimerMap->isPast("autoAttackDelay")) {
			const Time* autoAttackTime = cooldownTimerMap->getTime("autoAttackDelay");

			if (autoAttackTime != nullptr) {
				auto autoTime = fabs(autoAttackTime->miliDifference());

				if (autoTime > remainingActionTime) {
#ifdef DEBUG_QUEUE
					creature->info(true) << "Auto attack delay is > than remainingActionTime adding to delay = " << autoTime;
#endif
					nextActionTime->addMiliTime(autoTime);

					if (priority == QueueCommand::NORMAL)
						return autoTime;
				}
			}
		}
	}

	if (priority == QueueCommand::NORMAL && nextActionTime->isFuture()) {
#ifdef DEBUG_QUEUE
		creature->info(true) << "Next normal action is future returning time of " << remainingActionTime;
#endif
		return remainingActionTime;
	}

	if (queueCommand->addToCombatQueue() && ((creature->hasPostureChangeDelay() && priority != QueueCommand::IMMEDIATE) || creature->hasAttackDelay())) {
		return DEFAULTTIME;
	}

	time = objectController->activateCommand(creature, action->getCommand(), action->getActionCounter(), action->getTarget(), action->getArguments());

#ifdef DEBUG_QUEUE
	creature->info(true) << "Command Queue activateCommand called -- time = " << time;
#endif

	removeAction(action);

	if (priority == QueueCommand::NORMAL)
		nextActionTime->updateToCurrentTime();

	 if (creature->isAiAgent()) {
		if (priority == QueueCommand::NORMAL) {
			time = 2;
			nextActionTime->addMiliTime(2000);
		} else {
			return DEFAULTTIME;
		}
	} else if (time > 0) {
		uint64 miliTime = time * 1000;
#ifdef DEBUG_QUEUE
		creature->info(true) << "Command Delay Time > 0 -- adding to next action time " << miliTime;
#endif

		nextActionTime->addMiliTime(miliTime);
	}

	return time * 1000;
}

void CommandQueue::run() {
	auto creature = weakCreature.get();

	if (creature == nullptr)
		return;

#ifdef DEBUG_QUEUE
	auto debugMsg = [&]() -> LoggerHelper {
		auto msg = creature->info(true);
		msg << "CommandQueue::run() " << toString() << ": ";
		return msg;
	};

	runNumber++;
	debugMsg() << "START";
	lastRun.updateToCurrentTime();
	Timer profile;
	profile.start();
#endif // DEBUG_QUEUE

	switch (state) {
		case WAITING: {
			if (queueVector.size() == 0) {
				break;
			}

			state = RUNNING;
		}
		case RUNNING: {
			if (queueVector.size() == 0) {
				state = WAITING;
				break;
			}

			int delay = handleRunningState();
			Time* nextActionTime = creature->getNextActionTime();

			if (creature->hasAttackDelay() || creature->hasPostureChangeDelay() || (nextActionTime != nullptr && creature->isPlayerCreature() && nextActionTime->isFuture())) {
				state = DELAY;
				delay = DEFAULTTIME;
			}

			if (delay <= 0)
				delay = DEFAULTTIME;

			if (creature->isAiAgent())
				queueTask->reschedule(delay);
			else
				queueTask->reschedule(DEFAULTTIME);

			break;
		}
		case DELAY: {
			bool attackDelay = creature->hasAttackDelay();
			bool postureDelay = creature->hasPostureChangeDelay();

			Time* nextActionTime = creature->getNextActionTime();
			int actions = checkActions(creature);

			if ((!attackDelay && !postureDelay && nextActionTime != nullptr && !nextActionTime->isFuture()) || actions == QueueCommand::NOCOMBATQUEUE || actions == QueueCommand::FRONT || (!attackDelay && actions == QueueCommand::IMMEDIATE)) {
				state = RUNNING;
			}

			queueTask->reschedule(DEFAULTTIME);
		}
		default:
			break;
	}

#ifdef DEBUG_QUEUE
	debugMsg() << "FINISHED after " << Logger::nsToString(profile.stop()) << "; isScheduled=" << queueTask->isScheduled();
#endif // DEBUG_QUEUE
}

int CommandQueue::checkActions(CreatureObject* creature) {
	if (creature == nullptr)
		return 0;

	ZoneServer* zoneServer = creature->getZoneServer();

	if (zoneServer == nullptr) {
		return 0;
	}

	auto objectController = zoneServer->getObjectController();

	if (objectController == nullptr) {
		return 0;
	}

	bool hasImmediate = false;
	bool hasFront = false;

	Locker guard(&queueMutex);

	for (int i = 0; i < queueVector.size(); i++) {
		CommandQueueAction* action = queueVector.get(i);

		if (action == nullptr)
			continue;

		const QueueCommand* queueCommand = objectController->getQueueCommand(action->getCommand());

		if (queueCommand != nullptr) {
			if (!queueCommand->addToCombatQueue())
				return QueueCommand::NOCOMBATQUEUE;

			int priority = queueCommand->getDefaultPriority();

			if (priority == QueueCommand::IMMEDIATE) {
				hasImmediate = true;
			}

			if (priority == QueueCommand::FRONT) {
				hasFront = true;
			}
		}

		// Queue contains both immediate and front commands, stop iteration
		if (hasImmediate && hasFront)
			break;
	}

	if (hasFront)
		return QueueCommand::FRONT;
	else if (hasImmediate)
		return QueueCommand::IMMEDIATE;

	return 0;
}

void CommandQueue::clearQueueAction(unsigned int actioncntr, float timer, unsigned int tab1, unsigned int tab2) {
	auto creature = weakCreature.get();

	if (creature == nullptr || !creature->isPlayerCreature() || actioncntr == 0)
		return;

	creature->sendMessage(new CommandQueueRemove(creature, actioncntr, timer, tab1, tab2));
}

void CommandQueue::enqueueCommand(unsigned int actionCRC, unsigned int actionCount, uint64 targetID, const UnicodeString& arguments, int priority, int compareCounter) {
	auto creature = weakCreature.get();

	if (creature == nullptr) {
#ifdef DEBUG_QUEUE
		Logger::console.info(true) << "CommandQueue - enqueueCommand Called but creature == nullptr: " << toString();
#endif // DEBUG_QUEUE
		return;
	}

#ifdef DEBUG_QUEUE
	creature->info(true) << "CommandQueue - enqueueCommand Called: " << toString();
#endif // DEBUG_QUEUE

	ZoneServer* zoneServer = creature->getZoneServer();

	if (zoneServer == nullptr) {
		return;
	}

	auto objectController = zoneServer->getObjectController();

	if (objectController == nullptr) {
		return;
	}

	Locker guard(&queueMutex);

	const QueueCommand* queueCommand = objectController->getQueueCommand(actionCRC);

	if (queueCommand == nullptr) {
		creature->error() << "Invalid enqueueCommand call: actionCRC=" << actionCRC << "; actionCount=" << actionCount << "; targetID=" << targetID;
		return;
	}

	if (creature->isPlayerCreature() && queueCommand->addToCombatQueue()) {
		creature->notifyObservers(ObserverEventType::COMBATCOMMANDENQUEUED);
	}

	if (priority < 0) {
		priority = queueCommand->getDefaultPriority();
	}

	int size = queueVector.size();

	if (priority != QueueCommand::FRONT) {
		if ((creature->isAiAgent() && size >= 5) || size > 15) {
			clearQueueAction(actionCount, 0, 0, 0);
			return;
		}
	}

	CommandReference<CommandQueueAction*> action = new CommandQueueAction(creature, targetID, actionCRC, actionCount, arguments);

	if (compareCounter >= 0)
		action->setCompareToCounter((int)compareCounter);

#ifdef DEBUG_QUEUE
	creature->info(true) << "Enquing Command " << queueCommand->getQueueCommandName() << ": with priority - " << priority << " compareCount of " << compareCounter;

	int oldSize = queueVector.size();
#endif

	if (priority == QueueCommand::FRONT) {
		Time* nextAction = creature->getNextActionTime();

		if (nextAction != nullptr && queueVector.size() > 0 && !nextAction->isPast()) {
			action->setCompareToCounter(queueVector.get(0)->getCompareToCounter() - 1);
		}
	}

	queueVector.put(action.get());

#ifdef DEBUG_QUEUE
	creature->info() << "Queue Vector size changed from " << oldSize << " to " << queueVector.size();
#endif

	if (state == WAITING && !queueTask->isScheduled()) {
#ifdef DEBUG_QUEUE
		creature->info(true) << "Scheduling for DEFAULTTIME";
#endif // DEBUG_QUEUE
		queueTask->schedule(DEFAULTTIME);
	}

#ifdef DEBUG_QUEUE
	creature->info(true) << "enqueueCommand finished: " << toString();
#endif // DEBUG_QUEUE
}

void CommandQueue::sendCommand(uint32 crc, const UnicodeString& args, uint64 targetID, int priority) {
	auto creature = weakCreature.get();

	if (creature == nullptr)
		return;

	uint32 nextCounter = creature->incrementLastActionCounter();

	CommandQueueAdd* msg = new CommandQueueAdd(creature, crc, nextCounter);
	creature->sendMessage(msg);

	int compareCnt = -1;

	if (queueVector.size() == 0 || priority == QueueCommand::FRONT)
		compareCnt = 0;
	else if (priority == QueueCommand::NORMAL) {
		Locker guard(&queueMutex);
		compareCnt = queueVector.get(queueVector.size() - 1)->getCompareToCounter() + 1;
	}

	enqueueCommand(crc, nextCounter, targetID, args, priority, compareCnt);
}

void CommandQueue::clearQueueActions(bool combatOnly) {
	auto creature = weakCreature.get();

	if (creature == nullptr)
		return;

	Locker guard(&queueMutex);

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

			const QueueCommand* queueCommand = objectController->getQueueCommand(command->getCommand());
			if (queueCommand == nullptr)
				continue;

			if (!queueCommand->isCombatCommand())
				continue;
		}

		if (command->getActionCounter() != 0)
			clearQueueAction(command->getActionCounter(), 0, 0, 0);

		queueVector.remove(i);
	}
}

void CommandQueue::deleteQueueAction(uint32 actionCount) {
	Locker guard(&queueMutex);

	for (int i = 0; i < queueVector.size(); ++i) {
		CommandQueueAction* action = queueVector.get(i);

		if (action->getActionCounter() == actionCount) {
			queueVector.remove(i);
			break;
		}
	}
}

String CommandQueue::toString() const {
	auto creo = weakCreature.get();

	StringBuffer buf;

	buf <<"CommandQueue(state=";

	// clang-format off
	switch (state) {
	case NONE:    buf << "NONE";    break;
	case WAITING: buf << "WAITING"; break;
	case RUNNING: buf << "RUNNING"; break;
	case DELAY:   buf << "DELAY";   break;
	}
	// clang-format on

	buf << ", creature=" << (creo != nullptr ? creo->getObjectID() : 0)
#ifdef DEBUG_QUEUE
		<< ", runNumber=" << runNumber << ", lastRunMs=" << lastRun.miliDifference()
#endif // DEBUG_QUEUE
	<< ", queueVector.size=" << queueVector.size() << ", queueTask=" << hex << queueTask;

	if (queueTask != nullptr) {
		buf << "[" << (queueTask->isScheduled() ? "isScheduled" : "!isScheduled") << "]";
	}

	buf << ")";

	return buf.toString();
}
