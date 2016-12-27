/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef TOGGLEDISPLAYINGFACTIONRANKCOMMAND_H_
#define TOGGLEDISPLAYINGFACTIONRANKCOMMAND_H_

#include "server/zone/objects/player/PlayerObject.h"

class ToggleDisplayingFactionRankCommand : public QueueCommand {
public:

	ToggleDisplayingFactionRankCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		Reference<PlayerObject*> ghost = creature->getSlottedObject("ghost").castTo<PlayerObject*>();

		if (ghost != NULL)
			ghost->toggleCharacterBit(PlayerObject::FACTIONRANK);

		return SUCCESS;
	}

};

#endif //TOGGLEDISPLAYINGFACTIONRANKCOMMAND_H_
