/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef COMPLETEQUESTCOMMAND_H_
#define COMPLETEQUESTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class CompleteQuestCommand : public QueueCommand {
public:

	CompleteQuestCommand(const String& name, ZoneProcessServer* server)
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

			Locker targetLock(targetCreature, creature);

			if (commandType.beginsWith("screenplaystate")) {
				String screenPlayName;
				args.getStringToken(screenPlayName);
				uint64 state = args.getLongToken();

				targetCreature->setScreenPlayState(screenPlayName, state | targetCreature->getScreenPlayState(screenPlayName));

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

				if (!args.hasMoreTokens()) {
					ghost->completeQuest(questCRC);
					creature->sendSystemMessage("Completed quest.");
				} else {
					int active = args.getIntToken();
					int completed = args.getIntToken();
					int finished = args.getIntToken();

					PlayerQuestData data;
					data.setOwnerId(ghost->getObjectID());
					data.setActiveStepBitmask(active);
					data.setCompletedStepBitmask(completed);
					data.setCompletedFlag(finished);

					ghost->setPlayerQuestData(questCRC, data, true);
					creature->sendSystemMessage("Updated quest progress.");
				}
			} else {
				creature->sendSystemMessage("SYNTAX: /completeQuest screenplaystate <screenPlayStateName> <state>");
				creature->sendSystemMessage("SYNTAX: /completeQuest quest <quest>");
				creature->sendSystemMessage("SYNTAX: /completeQuest quest <questName> <activeQuestBitmask> <completedQuestBitmask> <questCompleted>");

				return INVALIDPARAMETERS;
			}
		} catch (Exception& e) {
			creature->sendSystemMessage("SYNTAX: /completeQuest screenplaystate <screenPlayStateName> <state>");
			creature->sendSystemMessage("SYNTAX: /completeQuest quest <quest>");
			creature->sendSystemMessage("SYNTAX: /completeQuest quest <questName> <activeQuestBitmask> <completedQuestBitmask> <questCompleted>");

			return INVALIDPARAMETERS;
		}

		return SUCCESS;
	}

};

#endif //COMPLETEQUESTCOMMAND_H_
