/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef ACTIVATEQUESTCOMMAND_H_
#define ACTIVATEQUESTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/player/PlayerObject.h"

class ActivateQuestCommand : public QueueCommand {
public:

	ActivateQuestCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		StringTokenizer args(arguments.toString());

		try {
			ManagedReference<SceneObject*> obj = server->getZoneServer()->getObject(target);

			if (obj == NULL || !obj->isCreatureObject()) {
				return INVALIDTARGET;
			}

			CreatureObject* targetCreature = cast<CreatureObject*>(obj.get());

			if (targetCreature == NULL) {
				return INVALIDTARGET;
			}

			Locker targetLock(targetCreature, creature);

			PlayerObject* ghost = targetCreature->getPlayerObject();

			if (ghost == NULL)
				return INVALIDTARGET;

			int quest = args.getIntToken();

			ghost->activateQuest(quest);

		} catch (Exception& e) {
			creature->sendSystemMessage("SYNTAX: /activateQuest <quest>");

			return INVALIDPARAMETERS;
		}

		return SUCCESS;
	}

};

#endif //ACTIVATEQUESTCOMMAND_H_
