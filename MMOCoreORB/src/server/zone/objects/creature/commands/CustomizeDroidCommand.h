/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CUSTOMIZEDROIDCOMMAND_H_
#define CUSTOMIZEDROIDCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class CustomizeDroidCommand : public QueueCommand {
public:

	CustomizeDroidCommand(const String& name, ZoneProcessServer* server)
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

#endif //CUSTOMIZEDROIDCOMMAND_H_
