/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef ANIMALCALMCOMMAND_H_
#define ANIMALCALMCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class AnimalCalmCommand : public QueueCommand {
public:

	AnimalCalmCommand(const String& name, ZoneProcessServer* server)
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

#endif //ANIMALCALMCOMMAND_H_
