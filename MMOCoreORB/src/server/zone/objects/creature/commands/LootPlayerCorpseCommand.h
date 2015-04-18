/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef LOOTPLAYERCORPSECOMMAND_H_
#define LOOTPLAYERCORPSECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class LootPlayerCorpseCommand : public QueueCommand {
public:

	LootPlayerCorpseCommand(const String& name, ZoneProcessServer* server)
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

#endif //LOOTPLAYERCORPSECOMMAND_H_
