/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef UNCITYBANCOMMAND_H_
#define UNCITYBANCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class UnCityBanCommand : public QueueCommand {
public:

	UnCityBanCommand(const String& name, ZoneProcessServer* server)
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

#endif //UNCITYBANCOMMAND_H_
