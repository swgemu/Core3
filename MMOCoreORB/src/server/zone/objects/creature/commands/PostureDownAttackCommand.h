/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef POSTUREDOWNATTACKCOMMAND_H_
#define POSTUREDOWNATTACKCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "CombatQueueCommand.h"

class PostureDownAttackCommand : public CombatQueueCommand {
public:

	PostureDownAttackCommand(const String& name, ZoneProcessServer* server) : CombatQueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isAiAgent())
			return GENERALERROR;

		return doCombatAction(creature, target, arguments);
	}

};

#endif //POSTUREDOWNATTACKCOMMAND_H_
