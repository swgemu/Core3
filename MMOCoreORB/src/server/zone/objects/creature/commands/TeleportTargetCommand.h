/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef TELEPORTTARGETCOMMAND_H_
#define TELEPORTTARGETCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/ZoneServer.h"

class TeleportTargetCommand : public QueueCommand {
public:

	TeleportTargetCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ManagedReference<Zone*> targetZone = creature->getZone();

		if (targetZone == NULL)
			return GENERALERROR; //Creature must be in a valid zone to use the command...

		ManagedReference<SceneObject*> obj = server->getZoneServer()->getObject(target);

		if (obj == creature)
			obj = NULL; //In case the player has himself targeted with the command.

		String targetName = "";
		String planetName = targetZone->getZoneName();
		float x = creature->getPositionX();
		float y = creature->getPositionY();
		float z = creature->getPositionZ();
		uint64 parentID = creature->getParentID();

		ManagedReference<CreatureObject*> targetCreature = NULL;
		UnicodeTokenizer tokenizer(arguments);

		try {
			tokenizer.getStringToken(targetName);
		} catch (Exception& e) {
			targetCreature = cast<CreatureObject*>(obj.get());
		}

		try {

			if (tokenizer.hasMoreTokens()) {

				x = tokenizer.getFloatToken();
				y = tokenizer.getFloatToken();

				if(tokenizer.hasMoreTokens()) {
					tokenizer.getStringToken(planetName);
					planetName = planetName.toLowerCase();
				}

				targetZone = targetZone->getZoneServer()->getZone(planetName);

				if (targetZone == NULL)
					throw Exception();

				z = targetZone->getHeight(x, y);
			}

			if (tokenizer.hasMoreTokens())
				z = tokenizer.getFloatToken();

			if (tokenizer.hasMoreTokens())
				parentID = tokenizer.getLongToken();

		} catch (Exception& e) {
			creature->sendSystemMessage("SYNTAX: /teleportTarget [<name>] -- Bring target to you");
			creature->sendSystemMessage("SYNTAX: /teleportTarget [<name>] <x> <y> [<planet>] [<z> <parentID>]");
			return INVALIDPARAMETERS;
		}

		if (!targetName.isEmpty()) {
			ManagedReference<PlayerManager*> playerManager = server->getPlayerManager();
			targetCreature = playerManager->getPlayer(targetName);
		}

		if (targetCreature == NULL) {
			creature->sendSystemMessage("The specified player does not exist.");
			return GENERALERROR;
		}

		Locker _lock(targetCreature, creature);

		targetCreature->switchZone(planetName, x, z, y, parentID);

		return SUCCESS;
	}

};

#endif //TELEPORTTARGETCOMMAND_H_
