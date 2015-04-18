/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CSDISCONNECTPLAYERCOMMAND_H_
#define CSDISCONNECTPLAYERCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class CsDisconnectPlayerCommand : public QueueCommand {
public:

	CsDisconnectPlayerCommand(const String& name, ZoneProcessServer* server)
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

#endif //CSDISCONNECTPLAYERCOMMAND_H_
