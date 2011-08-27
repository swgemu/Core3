/*
 * GroupLootCommand.h
 *
 *  Created on: Aug 26, 2011
 *      Author: dannuic
 */

#ifndef GROUPLOOTCOMMAND_H_
#define GROUPLOOTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class GroupLootCommand : public QueueCommand {
public:

	GroupLootCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		return SUCCESS;
	}

};

#endif /* GROUPLOOTCOMMAND_H_ */
