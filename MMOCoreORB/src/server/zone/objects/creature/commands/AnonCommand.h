/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef ANONCOMMAND_H_
#define ANONCOMMAND_H_

#include "server/zone/objects/player/PlayerObject.h"

class AnonCommand : public QueueCommand {
public:

	AnonCommand(const String& name, ZoneProcessServer* server)
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

		if (ghost->isAnonymous())
			creature->sendSystemMessage("@ui_who:anonymous_false");
		else
			creature->sendSystemMessage("@ui_who:anonymous_true");

		if (ghost != NULL)
			ghost->toggleCharacterBit(PlayerObject::ANONYMOUS);


		return SUCCESS;
	}

};

#endif //ANONCOMMAND_H_
