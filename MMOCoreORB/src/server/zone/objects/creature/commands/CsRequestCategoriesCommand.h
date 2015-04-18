/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CSREQUESTCATEGORIESCOMMAND_H_
#define CSREQUESTCATEGORIESCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class CsRequestCategoriesCommand : public QueueCommand {
public:

	CsRequestCategoriesCommand(const String& name, ZoneProcessServer* server)
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

#endif //CSREQUESTCATEGORIESCOMMAND_H_
