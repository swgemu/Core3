/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef LOOTAICORPSECOMMAND_H_
#define LOOTAICORPSECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class LootAiCorpseCommand : public QueueCommand {
public:

	LootAiCorpseCommand(const String& name, ZoneProcessServer* server)
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

#endif //LOOTAICORPSECOMMAND_H_
