/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef ASSOCIATEDROIDCONTROLDEVICEWITHSHIPCOMMAND_H_
#define ASSOCIATEDROIDCONTROLDEVICEWITHSHIPCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class AssociateDroidControlDeviceWithShipCommand : public QueueCommand {
public:

	AssociateDroidControlDeviceWithShipCommand(const String& name, ZoneProcessServer* server)
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

#endif //ASSOCIATEDROIDCONTROLDEVICEWITHSHIPCOMMAND_H_
