/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef GETPLAYERIDCOMMAND_H_
#define GETPLAYERIDCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/managers/player/PlayerManager.h"

class GetPlayerIdCommand : public QueueCommand {
public:

	GetPlayerIdCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		Reference<PlayerObject*> admin = creature->getSlottedObject("ghost").castTo<PlayerObject*>();

		if(admin == NULL || !admin->isPrivileged())
			return INVALIDTARGET;

		ManagedReference<CreatureObject* > targetCreature = NULL;

		StringTokenizer args(arguments.toString());

		if(args.hasMoreTokens()) {
			String character;
			args.getStringToken(character);

			ManagedReference<PlayerManager*> playerManager = server->getPlayerManager();
			targetCreature = playerManager->getPlayer(character);

		} else {

			targetCreature = server->getZoneServer()->getObject(target).castTo<CreatureObject*>();

		}

		if(targetCreature == NULL || !targetCreature->isPlayerCreature())
			return INVALIDTARGET;

		creature->sendSystemMessage("PlayerId for " + targetCreature->getFirstName()
				+ ": " + String::valueOf(targetCreature->getObjectID()));

		return SUCCESS;
	}

};

#endif //GETPLAYERIDCOMMAND_H_
