/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef TENDDAMAGETOOLCOMMAND_H_
#define TENDDAMAGETOOLCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class TendDamageToolCommand : public QueueCommand {
public:

	TendDamageToolCommand(const String& name, ZoneProcessServer* server)
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

#endif //TENDDAMAGETOOLCOMMAND_H_
