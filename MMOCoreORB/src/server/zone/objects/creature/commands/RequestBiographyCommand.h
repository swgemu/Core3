/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef REQUESTBIOGRAPHYCOMMAND_H_
#define REQUESTBIOGRAPHYCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/packets/object/Biography.h"

class RequestBiographyCommand : public QueueCommand {
public:

	RequestBiographyCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(target);

		if (object == NULL)
			return GENERALERROR;

		if (!object->isPlayerCreature())
			return GENERALERROR;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		CreatureObject* playerCreature = cast<CreatureObject*>( object.get());

		PlayerObject* ghost = playerCreature->getPlayerObject();

		if (ghost == NULL)
			return GENERALERROR;

		Biography* bio = new Biography(creature, playerCreature);
		creature->sendMessage(bio);

		return SUCCESS;
	}

};

#endif //REQUESTBIOGRAPHYCOMMAND_H_
