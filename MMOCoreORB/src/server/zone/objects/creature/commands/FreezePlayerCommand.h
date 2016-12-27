/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef FREEZEPLAYERCOMMAND_H_
#define FREEZEPLAYERCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class FreezePlayerCommand : public QueueCommand {
public:

	FreezePlayerCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		String syntaxerror = "Invalid arguments: /freezePlayer <firstname> <reason>";

		ManagedReference<SceneObject* > object = server->getZoneServer()->getObject(target);

		ManagedReference<CreatureObject* > targetPlayer = NULL;
		CreatureObject* player = cast<CreatureObject*>(creature);
		StringTokenizer args(arguments.toString());
		StringBuffer fullReason;

		if (object == NULL || !object->isPlayerCreature()) {

			String firstName;
			if (args.hasMoreTokens()) {
				args.getStringToken(firstName);
				targetPlayer = server->getZoneServer()->getPlayerManager()->getPlayer(firstName);
			}

		} else {
			targetPlayer = cast<CreatureObject*>( object.get());
		}

		if (targetPlayer == NULL) {
			player->sendSystemMessage(syntaxerror);
			return INVALIDPARAMETERS;
		}

		ManagedReference<PlayerObject*> targetGhost = targetPlayer->getPlayerObject();

		if (targetGhost == NULL) {
			player->sendSystemMessage(syntaxerror);
			return INVALIDPARAMETERS;
		}

		while (args.hasMoreTokens()) {
			String reason;
			args.getStringToken(reason);
			fullReason << reason << " ";
		}

		try {

			Locker playerlocker(targetPlayer);

			targetGhost->setMutedState(true);
			targetPlayer->setRootedState(3600);
			targetPlayer->setSpeedMultiplierBase(0.f, true);

			if(fullReason.toString().isEmpty()) {
				targetPlayer->sendSystemMessage("You have been frozen and muted by " + player->getFirstName() + ".");
				player->sendSystemMessage(targetPlayer->getFirstName() + " is now frozen and muted.");
			} else {
				String reason = fullReason.toString();
				targetGhost->setMutedReason(reason);

				StringBuffer muteMessage, targetMuteMessage;

				targetMuteMessage << "You have been muted by \'" << player->getFirstName() << "\' for '" << reason << "'";
				targetPlayer->sendSystemMessage(targetMuteMessage.toString());

				muteMessage << targetPlayer->getFirstName() << " is now muted for \'" << reason << "'";
				player->sendSystemMessage(muteMessage.toString());
			}

		} catch (Exception& e) {
			player->sendSystemMessage(syntaxerror);
		}

		return SUCCESS;
	}

};

#endif //FREEZEPLAYERCOMMAND_H_
