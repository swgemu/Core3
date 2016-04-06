/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef UNFREEZEPLAYERCOMMAND_H_
#define UNFREEZEPLAYERCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "templates/params/creature/CreatureState.h"

class UnfreezePlayerCommand : public QueueCommand {
public:

	UnfreezePlayerCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		String syntaxerror = "Invalid arguments: /unfreezePlayer <firstname>";

		ManagedReference<SceneObject* > object = server->getZoneServer()->getObject(target);

		ManagedReference<CreatureObject* > targetPlayer = NULL;
		CreatureObject* player = cast<CreatureObject*>(creature);
		StringTokenizer args(arguments.toString());

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

		try {

			Locker playerlocker(targetPlayer);

			targetGhost->setMutedState(false);
			String mutedResonse = "";
			targetGhost->setMutedReason(mutedResonse);

			targetPlayer->removeStateBuff(CreatureState::FROZEN);
			targetPlayer->sendSystemMessage("You have been unfrozen and unmuted by \'" + player->getFirstName() + "\'");

			targetPlayer->setSpeedMultiplierBase(1.f, true);

			player->sendSystemMessage(targetPlayer->getFirstName() + " has been unfrozen and unmuted.");

		} catch (Exception& e) {
			player->sendSystemMessage(syntaxerror);
		}

		return SUCCESS;

	}

};

#endif //UNFREEZEPLAYERCOMMAND_H_
