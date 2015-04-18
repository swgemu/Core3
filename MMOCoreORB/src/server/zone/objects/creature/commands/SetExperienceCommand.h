/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SETEXPERIENCECOMMAND_H_
#define SETEXPERIENCECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/managers/player/PlayerManager.h"

class SetExperienceCommand : public QueueCommand {
public:

	SetExperienceCommand(const String& name, ZoneProcessServer* server)
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
					player = server->getZoneServer()->getPlayerManager()->getPlayer(
									firstName);
				}

			} else {
				player = cast<CreatureObject*>(object.get());
			}

			if (player == NULL) {
				creature->sendSystemMessage("invalid arguments for setExperience command. usage: setExperience <firstName> <experienceType> <amount>");
				return GENERALERROR;
			}

			String xpType;
			args.getStringToken(xpType);
			int amount = args.getIntToken();

			int num = (player->getSlottedObject("ghost").castTo<PlayerObject*>())->getExperience(xpType);
			amount -= num;
			player->getZoneServer()->getPlayerManager()->awardExperience(player, xpType, amount);

			creature->sendSystemMessage("Experience Successfully changed");

		} catch (Exception& e) {
			creature->sendSystemMessage("invalid arguments for setExperience command. usage: setExperience <firstName> <experienceType> <amount>");
		}


		return SUCCESS;
	}

};

#endif //SETEXPERIENCECOMMAND_H_
