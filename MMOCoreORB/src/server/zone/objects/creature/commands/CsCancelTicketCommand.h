/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CSCANCELTICKETCOMMAND_H_
#define CSCANCELTICKETCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class CsCancelTicketCommand : public QueueCommand {
public:

	CsCancelTicketCommand(const String& name, ZoneProcessServer* server)
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

#endif //CSCANCELTICKETCOMMAND_H_
