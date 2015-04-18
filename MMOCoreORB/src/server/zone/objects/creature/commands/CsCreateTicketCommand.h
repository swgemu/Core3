/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CSCREATETICKETCOMMAND_H_
#define CSCREATETICKETCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class CsCreateTicketCommand : public QueueCommand {
public:

	CsCreateTicketCommand(const String& name, ZoneProcessServer* server)
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

#endif //CSCREATETICKETCOMMAND_H_
