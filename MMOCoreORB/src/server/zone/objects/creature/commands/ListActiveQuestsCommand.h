/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef LISTACTIVEQUESTSCOMMAND_H_
#define LISTACTIVEQUESTSCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class ListActiveQuestsCommand : public QueueCommand {
public:

	ListActiveQuestsCommand(const String& name, ZoneProcessServer* server)
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

#endif //LISTACTIVEQUESTSCOMMAND_H_
