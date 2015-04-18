/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef PEACECOMMAND_H_
#define PEACECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/managers/combat/CombatManager.h"


class PeaceCommand : public QueueCommand {
public:

	PeaceCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		CombatManager::instance()->attemptPeace(creature);

		return SUCCESS;
	}

};

#endif //PEACECOMMAND_H_
