/*
* CommandQueue.h
*
* Created on: Jan. 1, 2022
* Author: Hakry
*/

#ifndef COMMANDQUEUE_H_
#define COMMANDQUEUE_H_

#include "server/zone/managers/objectcontroller/ObjectController.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/commands/QueueCommand.h"
#include "server/zone/ZoneServer.h"

class CommandQueue : public Task {

#define DEBUG_QUEUE

private:
	ManagedWeakReference<CreatureObject*> weakCreature;
	WeakReference<CommandQueueActionVector*> commandQueue;

	enum QueueState {
		WAITING,
		RUNNING,
		POSTUREDELAYED,
		ATTACKDELAYED
	};

	QueueState state;

	void updateQueueState(CreatureObject* creature) {
		if (creature == nullptr)
			return;

		if (creature->hasAttackDelay()) {
			state = ATTACKDELAYED;
		} else if (creature->hasPostureChangeDelay()) {
			state = POSTUREDELAYED;
		} else {
			state = RUNNING;
		}
	}

	//unused -- for notes
	float calculateDelay(CreatureObject* creature) {
		float delay = 0.f;

		/*if (creature->hasAttackDelay()) {
			const Time* attackDelay = creature->getCooldownTime("nextAttackDelay");
			float attackTime = ((float)attackDelay->miliDifference() / 1000) * -1;

			if (attackTime > delay) {
				delay += attackTime;
			}

#ifdef DEBUG_QUEUE
			StringBuffer timeMsg;
			timeMsg << "  attackDelay time =  " << delay;
			creature->sendSystemMessage(timeMsg.toString());
#endif
		}

		if (creature->hasPostureChangeDelay()) {
			const Time* postureDelay = creature->getCooldownTime("postureChangeDelay");
			float postureTime = ((float)postureDelay->miliDifference() / 1000) * -1;

			if (postureTime > delay) {
				delay += postureTime;
			}

#ifdef DEBUG_QUEUE
			StringBuffer timeMsg;
			timeMsg << "  postureDelay time =  " << delay;
			creature->sendSystemMessage(timeMsg.toString());
#endif
		}*/

		return delay;
	}

public:
	CommandQueue(CreatureObject* creature, Reference<CommandQueueActionVector*> queue) {
		weakCreature = creature;
		commandQueue = queue;

		state = WAITING;
	}

	void run() {
		ManagedReference<CreatureObject*> creature = weakCreature.get();
		Reference<CommandQueueActionVector*> queue = commandQueue.get();

		if (creature == nullptr || queue == nullptr || state == RUNNING) {
			return;
		}

		try {
			Locker lock(creature);

#ifdef DEBUG_QUEUE
			creature->info("Command Queue Started with a state of: " + String::valueOf(state), true);
#endif

			if (queue->size() == 0) {
#ifdef DEBUG_QUEUE
				creature->info("Queue Size = 0 - returned", true);
#endif
				return;
			}

			updateQueueState(creature);

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

					reschedule(nextAction->getMiliTime() - currTime.getMiliTime());
#ifdef DEBUG_QUEUE
					creature->info("Next action is future rescheduling " + String::valueOf(nextAction->getMiliTime() - currTime.getMiliTime()), true);
#endif
				}
				return;
			}

#ifdef DEBUG_QUEUE
			creature->info("Queue size = " + String::valueOf(queue->size()), true);
#endif

			Reference<CommandQueueAction*> action = nullptr;
			const QueueCommand* queueCommand = nullptr;

			// Check queue for immediate actions, they get executed first
			for (int i = 0; i < queue->size(); i++) {
				Reference<CommandQueueAction*> immediateAction = queue->get(i);

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
				action = queue->get(0);
			}

			float time = 0.f;

			if (action != nullptr) {
				queueCommand = objectController->getQueueCommand(action->getCommand());

				if (queueCommand == nullptr)
					return;

				if (state == POSTUREDELAYED && queueCommand->getDefaultPriority() != QueueCommand::IMMEDIATE && queueCommand->addToCombatQueue()) {
					//time = calculateDelay(creature);

#ifdef DEBUG_QUEUE
					creature->info("Queue delayed by postureDelay", true);
#endif
					reschedule(500);
					return;
				} else if (state == ATTACKDELAYED && queueCommand->addToCombatQueue()) {
#ifdef DEBUG_QUEUE
					creature->info("Queue delayed by attackDelay", true);
#endif
					reschedule(500);
					return;
				}

				// Passed delay checks
				time = objectController->activateCommand(creature, action->getCommand(), action->getActionCounter(), action->getTarget(), action->getArguments());

#ifdef DEBUG_QUEUE
				creature->info("Command Queue activateCommand called -- time = " + String::valueOf(time) + ". ", true);
#endif

				for (int i = 0; i < queue->size(); i++) {
					Reference<CommandQueueAction*> actionToDelete = queue->get(i);

					if (action == actionToDelete) {
						queue->remove(i);

#ifdef DEBUG_QUEUE
						creature->info(" Queue action removed", true);
#endif
						break;
					}
				}

				nextAction->updateToCurrentTime();
				nextAction->addMiliTime((uint32)(time * 1000));
			}

			if (queue->size() > 0) {
				reschedule(time * 1000);
			} else {
				state = WAITING;
			}

#ifdef DEBUG_QUEUE
			creature->info("Command Queue Complete with End state of: " + String::valueOf(state), true);
#endif
		} catch (Exception& e) {
			creature->error(e.getMessage());
			e.printStackTrace();
		} catch (...) {
			throw;
		}
	}
};

#endif /* COMMANDQUEUE_H_ */