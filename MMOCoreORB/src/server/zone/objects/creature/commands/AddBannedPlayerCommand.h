/*
 				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef ADDBANNEDPLAYERCOMMAND_H_
#define ADDBANNEDPLAYERCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/player/PlayerObject.h"

class AddBannedPlayerCommand: public QueueCommand {
public:

	AddBannedPlayerCommand(const String& name, ZoneProcessServer* server) :
		QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target,
			const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ManagedReference<PlayerObject*> adminGhost = creature->getPlayerObject();

		if (adminGhost == NULL || !adminGhost->isPrivileged())
			return INSUFFICIENTPERMISSION;

		ManagedReference<CreatureObject*> targetCreature = NULL;
		ManagedReference<PlayerObject*> ghost = NULL;
		ManagedReference<PlayerManager*> playerManager = server->getPlayerManager();

		StringTokenizer args(arguments.toString());

		if (args.hasMoreTokens()) {
			String character;
			args.getStringToken(character);

			targetCreature = playerManager->getPlayer(character);

		} else {

			targetCreature = server->getZoneServer()->getObject(target).castTo<CreatureObject*>();

		}

		if (targetCreature == NULL || !targetCreature->isPlayerCreature())
			return INVALIDTARGET;

		ghost = targetCreature->getPlayerObject();

		if (ghost == NULL) {
			creature->sendSystemMessage("Player Ghost not found");
			return SUCCESS;
		}

		int duration;

		if (args.hasMoreTokens()) {
			duration = args.getIntToken();
		} else {
			creature->sendSystemMessage("Usage: /AddBannedPlayer <player name> <reason>");
			return GENERALERROR;
		}

		StringBuffer banReason;

		while (args.hasMoreTokens()) {
			String reason;
			args.getStringToken(reason);
			banReason << reason << " ";
		}

		if(banReason.toString().isEmpty()) {
			creature->sendSystemMessage("Usage: /AddBannedPlayer <player name> <reason>");			return GENERALERROR;
		}

		ManagedReference<Account*> account = playerManager->getAccount(ghost->getAccountID());

		String reason = banReason.toString();
		playerManager->banCharacter(adminGhost, account, targetCreature->getFirstName(), server->getZoneServer()->getGalaxyID(), duration, reason);
		creature->sendSystemMessage(targetCreature->getFirstName() + " is banned");

		return SUCCESS;
	}

};

#endif //ADDBANNEDPLAYERCOMMAND_H_
