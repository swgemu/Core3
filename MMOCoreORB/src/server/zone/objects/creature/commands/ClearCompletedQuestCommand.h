/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CLEARCOMPLETEDQUESTCOMMAND_H_
#define CLEARCOMPLETEDQUESTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class ClearCompletedQuestCommand : public QueueCommand {
public:

	ClearCompletedQuestCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		StringTokenizer args(arguments.toString());

		try {
			String commandType;
			args.getStringToken(commandType);
			ManagedReference<SceneObject*> obj = server->getZoneServer()->getObject(target);

			if (obj == nullptr || !obj->isCreatureObject()) {
				return INVALIDTARGET;
			}

			CreatureObject* targetCreature = cast<CreatureObject*>(obj.get());

			if (targetCreature == nullptr) {
				return INVALIDTARGET;
			}

			if (commandType.beginsWith("screenplaystate")) {
				String screenPlayName = args.getStringToken();

				uint64 state = args.getLongToken();
				state = ~state; // invert state to only clear the requested state.

				Locker targetLock(targetCreature);

				targetCreature->setScreenPlayState(screenPlayName, state & targetCreature->getScreenPlayState(screenPlayName));

				creature->sendSystemMessage(targetCreature->getFirstName() + " " + screenPlayName + " set to " + String::valueOf(targetCreature->getScreenPlayState(screenPlayName)));
			} else if (commandType.beginsWith("quest")) {
				PlayerObject* ghost = targetCreature->getPlayerObject();

				if (ghost == nullptr)
					return INVALIDTARGET;

				String questName = args.getStringToken();
				int questCRC;

				if (questName.contains("quest")) {
					questCRC = questName.hashCode();
				} else {
					questCRC = Integer::valueOf(questName);
				}

				int active = 0;
				int completed = 0;

				if (args.hasMoreTokens()) {
					active = args.getIntToken();
					completed = args.getIntToken();
				}
				PlayerQuestData data;
				data.setOwnerId(ghost->getObjectID());
				data.setActiveStepBitmask(active);
				data.setCompletedStepBitmask(completed);
				data.setCompletedFlag(0);

				ghost->setPlayerQuestData(questCRC, data, true);
				if (active == 0 && completed == 0) {
					creature->sendSystemMessage("Quest progress reset.");
				} else {
					creature->sendSystemMessage("Updated quest progress.");
				}
			} else {
				creature->sendSystemMessage("SYNTAX: /clearCompletedQuest screenplaystate <screenPlayStateName> <state>");
				creature->sendSystemMessage("SYNTAX: /clearCompletedQuest quest <questName> <activeQuestBitmask> <completedQuestBitmask>");

				return INVALIDPARAMETERS;
			}
		} catch (Exception& e) {
			creature->sendSystemMessage("SYNTAX: /clearCompletedQuest screenplaystate <screenPlayStateName> <state>");
			creature->sendSystemMessage("SYNTAX: /clearCompletedQuest quest <questName> <activeQuestBitmask> <completedQuestBitmask>");

			return INVALIDPARAMETERS;
		}

		return SUCCESS;
	}

};

#endif //CLEARCOMPLETEDQUESTCOMMAND_H_
