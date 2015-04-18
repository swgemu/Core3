/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CSGETARTICLECOMMAND_H_
#define CSGETARTICLECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class CsGetArticleCommand : public QueueCommand {
public:

	CsGetArticleCommand(const String& name, ZoneProcessServer* server)
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

#endif //CSGETARTICLECOMMAND_H_
