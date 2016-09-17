/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef TRANSFERFORCECOMMAND_H_
#define TRANSFERFORCECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class TransferForceCommand : public CombatQueueCommand {
public:

	TransferForceCommand(const String& name, ZoneProcessServer* server)
		: CombatQueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (isWearingArmor(creature)) {
			return NOJEDIARMOR;
		}

		ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(target);

		// Fail if target is not a player...
		if (object == NULL || !object->isPlayerCreature())
			return INVALIDTARGET;

		CreatureObject* targetCreature = cast<CreatureObject*>( object.get());

		if (targetCreature == NULL || targetCreature->isDead() || targetCreature->isIncapacitated())
			return INVALIDTARGET;

		Locker clocker(targetCreature, creature);

		ManagedReference<PlayerObject*> targetGhost = targetCreature->getPlayerObject();
		ManagedReference<PlayerObject*> playerGhost = creature->getPlayerObject();

		if (targetGhost == NULL || playerGhost == NULL)
			return GENERALERROR;

		if (!CollisionManager::checkLineOfSight(creature, targetCreature)) {
			creature->sendSystemMessage("@cbt_spam:los_fail");// You lost sight of your target.
			return GENERALERROR;
		}

		if (!checkDistance(creature, targetCreature, range))
			return TOOFAR;

		int maxTransfer = minDamage; //Value set in command lua
		if (playerGhost->getForcePower() < maxTransfer) {
			creature->sendSystemMessage("@jedi_spam:no_force_power"); //You do not have enough force to do that.
			return GENERALERROR;
		}

		if (targetCreature->isHealableBy(creature)) {
			int forceSpace = targetGhost->getForcePowerMax() - targetGhost->getForcePower();
			if (forceSpace <= 0) {
				creature->sendSystemMessage("@jedi_spam:power_already_active"); //This target is already affected by that power.
				return GENERALERROR;
			}

			int forceTransfer = forceSpace >= maxTransfer ? maxTransfer : forceSpace;
			targetGhost->setForcePower(targetGhost->getForcePower() + forceTransfer);
			playerGhost->setForcePower(playerGhost->getForcePower() - forceTransfer);

			uint32 animCRC = getAnimationString().hashCode();
			creature->doCombatAnimation(targetCreature, animCRC, 0x1, 0xFF);
			CombatManager::instance()->broadcastCombatSpam(creature, targetCreature, NULL, forceTransfer, "cbt_spam", combatSpam, 0);

			return SUCCESS;
		}

		return GENERALERROR;
	}

	float getCommandDuration(CreatureObject* object, const UnicodeString& arguments) const {
		return defaultTime * 3.0;
	}

};

#endif //TRANSFERFORCECOMMAND_H_
