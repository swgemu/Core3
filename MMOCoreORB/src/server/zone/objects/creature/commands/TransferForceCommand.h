/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef TRANSFERFORCECOMMAND_H_
#define TRANSFERFORCECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/managers/frs/FrsManager.h"

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
		if (object == nullptr || !object->isPlayerCreature())
			return INVALIDTARGET;

		CreatureObject* targetCreature = cast<CreatureObject*>( object.get());

		if (targetCreature == nullptr || targetCreature->isDead() || targetCreature->isIncapacitated())
			return INVALIDTARGET;

		Locker clocker(targetCreature, creature);

		ManagedReference<PlayerObject*> targetGhost = targetCreature->getPlayerObject();
		ManagedReference<PlayerObject*> playerGhost = creature->getPlayerObject();

		if (targetGhost == nullptr || playerGhost == nullptr)
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

		FrsManager* frsManager = server->getZoneServer()->getFrsManager();

		if (checkForArenaDuel(targetCreature)) {
			creature->sendSystemMessage("@jedi_spam:no_help_target"); // You are not permitted to help that target.
			return GENERALERROR;
		}

		if (!targetCreature->isHealableBy(creature)) {
			creature->sendSystemMessage("@healing:pvp_no_help"); // It would be unwise to help such a patient.
			return GENERALERROR;
		}

		int forceSpace = targetGhost->getForcePowerMax() - targetGhost->getForcePower();
		int forceTransfer = 0;

		if (forceSpace > 0) {
			forceTransfer = forceSpace >= maxTransfer ? maxTransfer : forceSpace;
			targetGhost->setForcePower(targetGhost->getForcePower() + forceTransfer);
			playerGhost->setForcePower(playerGhost->getForcePower() - forceTransfer);
		}

		uint32 animCRC = getAnimationString().hashCode();
		creature->doCombatAnimation(targetCreature, animCRC, 0x1, 0xFF);
		CombatManager::instance()->broadcastCombatSpam(creature, targetCreature, nullptr, forceTransfer, "cbt_spam", combatSpam, 0);

		return SUCCESS;
	}

	float getCommandDuration(CreatureObject* object, const UnicodeString& arguments) const {
		return defaultTime * 3.0;
	}

};

#endif //TRANSFERFORCECOMMAND_H_
