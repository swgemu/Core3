/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef UNINSTALLSHIPCOMPONENTCOMMAND_H_
#define UNINSTALLSHIPCOMPONENTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class UninstallShipComponentCommand : public QueueCommand {
public:

	UninstallShipComponentCommand(const String& name, ZoneProcessServer* server)
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

#endif //UNINSTALLSHIPCOMPONENTCOMMAND_H_
