/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef PLANETWARPCOMMAND_H_
#define PLANETWARPCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class PlanetwarpCommand : public QueueCommand {
public:

	PlanetwarpCommand(const String& name, ZoneProcessServer* server)
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

#endif //PLANETWARPCOMMAND_H_
