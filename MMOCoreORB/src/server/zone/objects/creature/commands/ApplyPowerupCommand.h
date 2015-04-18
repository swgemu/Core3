/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef APPLYPOWERUPCOMMAND_H_
#define APPLYPOWERUPCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/tangible/powerup/PowerupObject.h"
#include "server/zone/objects/tangible/weapon/WeaponObject.h"

class ApplyPowerupCommand : public QueueCommand {
public:

	ApplyPowerupCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		StringTokenizer args(arguments.toString());

		ManagedReference<PowerupObject*> pup = server->getZoneServer()->getObject(target).castTo<PowerupObject*>();

		if (pup == NULL)
			return GENERALERROR;

		if (!args.hasMoreTokens())
			return GENERALERROR;

		uint64 targetObjectID = args.getLongToken();

		ManagedReference<WeaponObject*> weapon = server->getZoneServer()->getObject(targetObjectID).castTo<WeaponObject*>();

		if (weapon == NULL)
			return GENERALERROR;

		if (!pup->checkContainerPermission(creature, ContainerPermissions::MOVECONTAINER))
			return GENERALERROR;

		if (!weapon->isASubChildOf(creature))
			return GENERALERROR;

		if (!pup->isASubChildOf(creature))
			return GENERALERROR;
			
		if (weapon->isJediWeapon())
			return GENERALERROR;			

		if((weapon->isRangedWeapon() && pup->isRanged()) ||
				(weapon->isMeleeWeapon() && pup->isMelee()) ||
				(weapon->isThrownWeapon() && pup->isThrown()) ||
				(weapon->isMineWeapon() && pup->isMine())) {

			if(!weapon->hasPowerup()) {

				if (weapon->applyPowerup(creature, pup)) {

					StringIdChatParameter message("powerup", "prose_pup_apply"); //You powerup your %TT with %TU.
					message.setTT(weapon->getDisplayedName());
					message.setTU(pup->getDisplayedName());

					creature->sendSystemMessage(message);
				} else {
					StringIdChatParameter message("powerup", "prose_apply_restricted"); //You cannot apply %TU to %TT.
					message.setTT(weapon->getDisplayedName());
					message.setTU(pup->getDisplayedName());

					creature->sendSystemMessage(message);
				}

			} else {

				StringIdChatParameter message("powerup", "prose_already_powered"); //Your %TT already has a powerup.
				message.setTT(weapon->getDisplayedName());

				creature->sendSystemMessage(message);

			}

			return SUCCESS;
		} else {
			StringIdChatParameter message("powerup", "prose_apply_restricted"); //You cannot apply %TU to %TT.
			message.setTT(weapon->getDisplayedName());
			message.setTU(pup->getDisplayedName());

			creature->sendSystemMessage(message);
		}

		return GENERALERROR;
	}

};

#endif //APPLYPOWERUPCOMMAND_H_
