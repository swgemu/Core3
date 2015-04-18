/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SEARCHCORPSECOMMAND_H_
#define SEARCHCORPSECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class SearchCorpseCommand : public QueueCommand {
public:

	SearchCorpseCommand(const String& name, ZoneProcessServer* server)
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

#endif //SEARCHCORPSECOMMAND_H_
