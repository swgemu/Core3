/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SEGOGGLESCOMMAND_H_
#define SEGOGGLESCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class SeGogglesCommand : public QueueCommand {
public:

	SeGogglesCommand(const String& name, ZoneProcessServer* server)
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

#endif //SEGOGGLESCOMMAND_H_
