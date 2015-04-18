/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef GIVEMAINTENANCETOVENDORCOMMAND_H_
#define GIVEMAINTENANCETOVENDORCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class GiveMaintenanceToVendorCommand : public QueueCommand {
public:

	GiveMaintenanceToVendorCommand(const String& name, ZoneProcessServer* server)
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

#endif //GIVEMAINTENANCETOVENDORCOMMAND_H_
