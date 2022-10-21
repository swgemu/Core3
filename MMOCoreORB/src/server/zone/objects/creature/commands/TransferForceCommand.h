/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef TRANSFERFORCECOMMAND_H_
#define TRANSFERFORCECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/managers/frs/FrsManager.h"

class TransferForceCommand : public CombatQueueCommand {
public:

	TransferForceCommand(const String& name, ZoneProcessServer* server) : CombatQueueCommand(name, server) {
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

		CreatureObject* targetCreature = cast<CreatureObject*>(object.get());

		if (targetCreature == nullptr || targetCreature->isDead() || targetCreature->isIncapacitated())
			return INVALIDTARGET;

		if (!CollisionManager::checkLineOfSight(creature, targetCreature)) {
			creature->sendSystemMessage("@combat_effects:cansee_fail");//You cannot see your target.
			return GENERALERROR;
		}

		if (!checkDistance(creature, targetCreature, range))
			return TOOFAR;

		if (!playerEntryCheck(creature, targetCreature)) {
			return GENERALERROR;
		}

		Locker clocker(targetCreature, creature);

		ManagedReference<PlayerObject*> targetGhost = targetCreature->getPlayerObject();
		ManagedReference<PlayerObject*> playerGhost = creature->getPlayerObject();

		if (targetGhost == nullptr || playerGhost == nullptr)
			return GENERALERROR;

		if (targetGhost == playerGhost)
			return GENERALERROR;

		int transfer = System::random(75) + minDamage; //Value set in command lua

		FrsManager* frsManager = server->getZoneServer()->getFrsManager();

		if (checkForArenaDuel(targetCreature)) {
			creature->sendSystemMessage("@jedi_spam:no_help_target"); // You are not permitted to help that target.
			return GENERALERROR;
		}

		if (!targetCreature->isHealableBy(creature)) {
			creature->sendSystemMessage("@healing:pvp_no_help"); // It would be unwise to help such a patient.
			return GENERALERROR;
		}

		if (playerGhost->getForcePower() < forceCost) {
			creature->sendSystemMessage("@jedi_spam:no_force_power"); //You do not have enough force to do that.
			return GENERALERROR;
		}

		int forceSpace = targetGhost->getForcePowerMax() - targetGhost->getForcePower();
		int forceTransfer = 0;

		if (forceSpace > 0) { //Only allows amount to be transfered that the target can hold and fails if target has full Force.
			forceTransfer = forceSpace >= transfer ? transfer : forceSpace;
		} else {
			return GENERALERROR;
		}

		targetGhost->setForcePower(targetGhost->getForcePower() + forceTransfer);
		playerGhost->setForcePower(playerGhost->getForcePower() - forceCost);

		uint32 animCRC = getAnimationString().hashCode();
		creature->doCombatAnimation(targetCreature, animCRC, 0x1, 0xFF);
		CombatManager::instance()->broadcastCombatSpam(creature, targetCreature, nullptr, forceTransfer, "cbt_spam", combatSpam, 0);

		VisibilityManager::instance()->increaseVisibility(creature, visMod);

		if (ConfigManager::instance()->useCovertOvertSystem())
			checkForTef(creature, targetCreature);

		return SUCCESS;
	}

	float getCommandDuration(CreatureObject* object, const UnicodeString& arguments) const {
		return defaultTime;
	}

};

#endif //TRANSFERFORCECOMMAND_H_
