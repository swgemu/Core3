/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef REQUESTBADGESCOMMAND_H_
#define REQUESTBADGESCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class RequestBadgesCommand : public QueueCommand {
public:

	RequestBadgesCommand(const String& name, ZoneProcessServer* server)
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

		CreatureObject* playerCreature = cast<CreatureObject*>( object.get());

		Reference<PlayerObject*> playerObject = playerCreature->getSlottedObject("ghost").castTo<PlayerObject*>();

		if (playerObject != NULL)
			playerObject->sendBadgesResponseTo(creature);

		return SUCCESS;
	}

};

#endif //REQUESTBADGESCOMMAND_H_
