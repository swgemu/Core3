/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef LISTCOMPLETEDQUESTSCOMMAND_H_
#define LISTCOMPLETEDQUESTSCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class ListCompletedQuestsCommand : public QueueCommand {
public:

	ListCompletedQuestsCommand(const String& name, ZoneProcessServer* server)
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

#endif //LISTCOMPLETEDQUESTSCOMMAND_H_
