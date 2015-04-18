/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SHOWCOUNCILRANKCOMMAND_H_
#define SHOWCOUNCILRANKCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class ShowCouncilRankCommand : public QueueCommand {
public:

	ShowCouncilRankCommand(const String& name, ZoneProcessServer* server)
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

#endif //SHOWCOUNCILRANKCOMMAND_H_
