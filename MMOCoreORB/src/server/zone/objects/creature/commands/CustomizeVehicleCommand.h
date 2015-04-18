/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CUSTOMIZEVEHICLECOMMAND_H_
#define CUSTOMIZEVEHICLECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class CustomizeVehicleCommand : public QueueCommand {
public:

	CustomizeVehicleCommand(const String& name, ZoneProcessServer* server)
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

#endif //CUSTOMIZEVEHICLECOMMAND_H_
