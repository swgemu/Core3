/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CSAPPENDCOMMENTCOMMAND_H_
#define CSAPPENDCOMMENTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class CsAppendCommentCommand : public QueueCommand {
public:

	CsAppendCommentCommand(const String& name, ZoneProcessServer* server)
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

#endif //CSAPPENDCOMMENTCOMMAND_H_
