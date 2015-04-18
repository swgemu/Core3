/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef HEALBATTLEFATIGUEOTHER1COMMAND_H_
#define HEALBATTLEFATIGUEOTHER1COMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class HealBattleFatigueOther1Command : public QueueCommand {
public:

	HealBattleFatigueOther1Command(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		return SUCCESS;
	}

};

#endif //HEALBATTLEFATIGUEOTHER1COMMAND_H_
