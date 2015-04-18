/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef REQUESTMANFSCHEMATICSLOTSCOMMAND_H_
#define REQUESTMANFSCHEMATICSLOTSCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class RequestManfSchematicSlotsCommand : public QueueCommand {
public:

	RequestManfSchematicSlotsCommand(const String& name, ZoneProcessServer* server)
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

#endif //REQUESTMANFSCHEMATICSLOTSCOMMAND_H_
