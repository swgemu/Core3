/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef DRAINFORCECOMMAND_H_
#define DRAINFORCECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "CombatQueueCommand.h"

class DrainForceCommand : public CombatQueueCommand {
public:

	DrainForceCommand(const String& name, ZoneProcessServer* server)
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

		if (targetCreature == nullptr || targetCreature->isDead() || (targetCreature->isIncapacitated() && !targetCreature->isFeigningDeath()) || !targetCreature->isAttackableBy(creature))
			return INVALIDTARGET;

		if (!checkDistance(creature, targetCreature, range))
			return TOOFAR;

		if (!CollisionManager::checkLineOfSight(creature, targetCreature)) {
			creature->sendSystemMessage("@combat_effects:cansee_fail");//You cannot see your target.
			return GENERALERROR;
		}

		if (!playerEntryCheck(creature, targetCreature)) {
			return GENERALERROR;
		}

		Locker clocker(targetCreature, creature);

		ManagedReference<PlayerObject*> targetGhost = targetCreature->getPlayerObject();
		ManagedReference<PlayerObject*> playerGhost = creature->getPlayerObject();

		if (targetGhost == nullptr || playerGhost == nullptr)
			return GENERALERROR;

		CombatManager* manager = CombatManager::instance();

		if (manager->startCombat(creature, targetCreature, false)) { //lockDefender = false because already locked above.
			int forceSpace = playerGhost->getForcePowerMax() - playerGhost->getForcePower();

			if (forceSpace <= 0) //Cannot Force Drain if attacker can't hold any more Force.
				return GENERALERROR;

			if (playerGhost->getForcePower() < forceCost) {
				creature->sendSystemMessage("@jedi_spam:no_force_power"); //You do not have sufficient Force power to perform that action.
				return GENERALERROR;
			}

			int drain = System::random(maxDamage);

			int targetForce = targetGhost->getForcePower();
			if (targetForce <= 0) {
				creature->sendSystemMessage("@jedi_spam:target_no_force"); //That target does not have any Force Power.
				return GENERALERROR;
			}

			int forceDrain = targetForce >= drain ? drain : targetForce; //Drain whatever Force the target has, up to max.

			if (forceDrain > forceSpace) {
				forceDrain = forceSpace; //Drain only what attacker can hold in their own Force pool.
			}

			playerGhost->setForcePower(playerGhost->getForcePower() + (forceDrain - forceCost));
			targetGhost->setForcePower(targetGhost->getForcePower() - forceDrain);

			uint32 animCRC = getAnimationString().hashCode();
			creature->doCombatAnimation(targetCreature, animCRC, 0x1, 0xFF);
			manager->broadcastCombatSpam(creature, targetCreature, nullptr, forceDrain, "cbt_spam", combatSpam, 1);

			if (targetCreature->getSkillMod("force_absorb") > 0) {
				float drainAbsorb = forceDrain * 0.4f;
				targetCreature->notifyObservers(ObserverEventType::FORCEABSORB, targetCreature, drainAbsorb);
				manager->sendMitigationCombatSpam(targetCreature, nullptr, drainAbsorb, 0x04); // FORCEABSORB
			}

			VisibilityManager::instance()->increaseVisibility(creature, visMod);

			return SUCCESS;

		}

		return GENERALERROR;

	}

	float getCommandDuration(CreatureObject* object, const UnicodeString& arguments) const {
		float baseDuration = defaultTime * 3.0;
		float combatHaste = object->getSkillMod("combat_haste");

		if (combatHaste > 0) {
			return baseDuration * (1.f - (combatHaste / 100.f));
		} else {
			return baseDuration;
		}
	}

};

#endif //DRAINFORCECOMMAND_H_
