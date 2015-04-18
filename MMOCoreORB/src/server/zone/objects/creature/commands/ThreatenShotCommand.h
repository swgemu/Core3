/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef THREATENSHOTCOMMAND_H_
#define THREATENSHOTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class ThreatenShotCommand : public CombatQueueCommand {
public:

	ThreatenShotCommand(const String& name, ZoneProcessServer* server)
		: CombatQueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		return SUCCESS;
	}

};

#endif //THREATENSHOTCOMMAND_H_
