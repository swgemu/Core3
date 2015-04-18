/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef TELEPORTTOCOMMAND_H_
#define TELEPORTTOCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/ZoneServer.h"

class TeleportToCommand : public QueueCommand {
public:

	TeleportToCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		String targetName;

		try {
			UnicodeTokenizer args(arguments);
			args.getStringToken(targetName);

		} catch (Exception& e) {
			creature->sendSystemMessage("SYNTAX: /teleportTo <targetName>");
			return INVALIDPARAMETERS;
		}

		ManagedReference<PlayerManager*> playerManager = server->getPlayerManager();
		ManagedReference<CreatureObject*> targetCreature = playerManager->getPlayer(targetName);

		if (targetCreature == NULL) {
			creature->sendSystemMessage("The specified player does not exist.");
			return INVALIDTARGET;
		}

		if (targetCreature->getZone() == NULL) {
			creature->sendSystemMessage("The specified player is not in a zone that is currently loaded.");
			return INVALIDTARGET;
		}

		if (creature == targetCreature) {
			creature->sendSystemMessage("You cannot teleport to yourself.");
			return INVALIDTARGET;
		}

		String zoneName = targetCreature->getZone()->getZoneName();
		float x = targetCreature->getPositionX();
		float y = targetCreature->getPositionY();
		float z = targetCreature->getPositionZ();
		uint64 parentid = targetCreature->getParentID();

		creature->switchZone(zoneName, x, z, y, parentid);

		return SUCCESS;
	}

};

#endif //TELEPORTTOCOMMAND_H_
