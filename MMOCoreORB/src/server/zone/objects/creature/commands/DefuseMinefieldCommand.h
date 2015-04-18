/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef DEFUSEMINEFIELDCOMMAND_H_
#define DEFUSEMINEFIELDCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class DefuseMinefieldCommand : public QueueCommand {
public:

	DefuseMinefieldCommand(const String& name, ZoneProcessServer* server)
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

#endif //DEFUSEMINEFIELDCOMMAND_H_
