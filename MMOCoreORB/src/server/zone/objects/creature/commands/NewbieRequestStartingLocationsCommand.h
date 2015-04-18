/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef NEWBIEREQUESTSTARTINGLOCATIONSCOMMAND_H_
#define NEWBIEREQUESTSTARTINGLOCATIONSCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class NewbieRequestStartingLocationsCommand : public QueueCommand {
public:

	NewbieRequestStartingLocationsCommand(const String& name, ZoneProcessServer* server)
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

#endif //NEWBIEREQUESTSTARTINGLOCATIONSCOMMAND_H_
