/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef KICKCOMMAND_H_
#define KICKCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class KickCommand : public QueueCommand {
public:

	KickCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		try {

			ManagedReference<SceneObject* > object =
					server->getZoneServer()->getObject(target);

			ManagedReference<CreatureObject*> player = NULL;

			StringTokenizer args(arguments.toString());

			if (object == NULL || !object->isPlayerCreature()) {
				String firstName;

				if (args.hasMoreTokens()) {
					args.getStringToken(firstName);
					player = server->getZoneServer()->getChatManager()->getPlayer(
							firstName);
				}

			} else {
				player = cast<CreatureObject*>( object.get());
			}

			if (player == NULL) {
				creature->sendSystemMessage("Usage: /kick <firstName> <reason>");
				return GENERALERROR;
			}

			StringBuffer banReason;

			while (args.hasMoreTokens()) {
				String reason;
				args.getStringToken(reason);
				banReason << reason << " ";
			}

			if(banReason.toString().isEmpty()) {
				creature->sendSystemMessage("You must provide a reason for kicking");
				return GENERALERROR;
			}

			ManagedReference<PlayerManager*> playerManager = server->getZoneServer()->getPlayerManager();
			String reason = banReason.toString();
			playerManager->kickUser(player->getFirstName(), creature->getCustomObjectName().toString(), reason);

			creature->sendSystemMessage(player->getFirstName() + " kicked.");

		} catch (Exception& e) {
			creature->sendSystemMessage("invalid arguments for kick command.");
		}


		return SUCCESS;
	}

};

#endif //KICKCOMMAND_H_
