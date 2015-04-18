/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef INSTALLSHIPCOMPONENTCOMMAND_H_
#define INSTALLSHIPCOMPONENTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class InstallShipComponentCommand : public QueueCommand {
public:

	InstallShipComponentCommand(const String& name, ZoneProcessServer* server)
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

#endif //INSTALLSHIPCOMPONENTCOMMAND_H_
