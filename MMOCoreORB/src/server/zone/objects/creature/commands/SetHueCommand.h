/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SETHUECOMMAND_H_
#define SETHUECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class SetHueCommand : public QueueCommand {
public:

	SetHueCommand(const String& name, ZoneProcessServer* server)
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

#endif //SETHUECOMMAND_H_
