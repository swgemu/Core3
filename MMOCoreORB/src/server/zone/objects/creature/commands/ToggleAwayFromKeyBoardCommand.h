/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef TOGGLEAWAYFROMKEYBOARDCOMMAND_H_
#define TOGGLEAWAYFROMKEYBOARDCOMMAND_H_

#include "server/zone/objects/player/PlayerObject.h"

class ToggleAwayFromKeyBoardCommand : public QueueCommand {
public:

	ToggleAwayFromKeyBoardCommand(const String& name, ZoneProcessServer* server)
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
			ghost->toggleCharacterBit(PlayerObject::AFK);

		return SUCCESS;
	}

};

#endif //TOGGLEAWAYFROMKEYBOARDCOMMAND_H_
