/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SETCHARGECOMMAND_H_
#define SETCHARGECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class SetChargeCommand : public QueueCommand {
public:

	SetChargeCommand(const String& name, ZoneProcessServer* server)
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

#endif //SETCHARGECOMMAND_H_
