/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef NEWBIEHELPERCOMMAND_H_
#define NEWBIEHELPERCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/player/PlayerObject.h"

class NewbiehelperCommand : public QueueCommand {
public:

	NewbiehelperCommand(const String& name, ZoneProcessServer* server)
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
			ghost->toggleCharacterBit(PlayerObject::NEWBIEHELPER);

		return SUCCESS;
	}

};

#endif //NEWBIEHELPERCOMMAND_H_
