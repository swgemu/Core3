/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CSCONNECTPLAYERCOMMAND_H_
#define CSCONNECTPLAYERCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class CsConnectPlayerCommand : public QueueCommand {
public:

	CsConnectPlayerCommand(const String& name, ZoneProcessServer* server)
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

#endif //CSCONNECTPLAYERCOMMAND_H_
