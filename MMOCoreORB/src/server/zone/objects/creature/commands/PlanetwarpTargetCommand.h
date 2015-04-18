/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef PLANETWARPTARGETCOMMAND_H_
#define PLANETWARPTARGETCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class PlanetwarpTargetCommand : public QueueCommand {
public:

	PlanetwarpTargetCommand(const String& name, ZoneProcessServer* server)
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

#endif //PLANETWARPTARGETCOMMAND_H_
