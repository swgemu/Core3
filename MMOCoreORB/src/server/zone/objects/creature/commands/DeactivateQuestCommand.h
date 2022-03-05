/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef DEACTIVATEQUESTCOMMAND_H_
#define DEACTIVATEQUESTCOMMAND_H_

class DeactivateQuestCommand : public QueueCommand {
public:

	DeactivateQuestCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		Reference<PlayerObject*> ghost = creature->getPlayerObject();
		if (ghost == nullptr || !ghost->isPrivileged()) {
			return GENERALERROR;
		}

		StringTokenizer args(arguments.toString());

		try {
			ManagedReference<SceneObject*> obj = server->getZoneServer()->getObject(target);

			if (obj == nullptr || !obj->isCreatureObject()) {
				return INVALIDTARGET;
			}

			CreatureObject* targetCreature = cast<CreatureObject*>(obj.get());

			if (targetCreature == nullptr) {
				return INVALIDTARGET;
			}

			PlayerObject* ghost = targetCreature->getPlayerObject();

			if (ghost == nullptr)
				return INVALIDTARGET;

			String questName = args.getStringToken();
			int questCRC = questName.hashCode();

			PlayerQuestData data;
			ghost->clearJournalQuest(questCRC, true);

		} catch (Exception& e) {
			creature->sendSystemMessage("SYNTAX: /deactivateQuest <questName>");

			return INVALIDPARAMETERS;
		}

		return SUCCESS;
	}

};

#endif //DEACTIVATEQUESTCOMMAND_H_
