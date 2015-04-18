/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef GMFSVILLAGECOMMAND_H_
#define GMFSVILLAGECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class GmFsVillageCommand : public QueueCommand {
public:

	GmFsVillageCommand(const String& name, ZoneProcessServer* server)
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

#endif //GMFSVILLAGECOMMAND_H_
