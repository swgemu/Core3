/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef ROLEPLAYCOMMAND_H_
#define ROLEPLAYCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/player/PlayerObject.h"


class RolePlayCommand : public QueueCommand {
public:

	RolePlayCommand(const String& name, ZoneProcessServer* server)
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
			ghost->toggleCharacterBit(PlayerObject::ROLEPLAYER);

		return SUCCESS;
	}

};

#endif //ROLEPLAYCOMMAND_H_
