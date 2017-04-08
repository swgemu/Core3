/*
 				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef EQUILIBRIUMCOMMAND_H_
#define EQUILIBRIUMCOMMAND_H_

class EquilibriumCommand: public QueueCommand {
public:

	EquilibriumCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (creature->hasAttackDelay() || !creature->checkPostureChangeDelay())
			return GENERALERROR;

		if (creature->getSpecies() != CreatureObject::ZABRAK)
			return GENERALERROR;

		CreatureObject* player = cast<CreatureObject*>(creature);

		// Check to see if "innate_equilibrium" Cooldown isPast();
		if (!player->checkCooldownRecovery("innate_equilibrium")) {
			StringIdChatParameter stringId;

			Time* cdTime = player->getCooldownTime("innate_equilibrium");

			// Returns -time. Multiple by -1 to return positive.
			int timeLeft = floor((float)cdTime->miliDifference() / 1000) *-1;

			stringId.setStringId("@innate:equil_wait"); // You are still recovering from your last equilization. Command available in %DI seconds.
			stringId.setDI(timeLeft);
			player->sendSystemMessage(stringId);
			return GENERALERROR;
		}

		int health = player->getHAM(CreatureAttribute::HEALTH);
		int action = player->getHAM(CreatureAttribute::ACTION);
		int mind = player->getHAM(CreatureAttribute::MIND);

		// All pools Balanced to the same Value.
		int balValue = (health + action + mind) / 3;

		// Get the difference between current HEALTH and the balValue.
		int diffHealth = Math::max(health, balValue) - Math::min(health, balValue);
		int diffAction = Math::max(action, balValue) - Math::min(action, balValue);
		int diffMind = Math::max(mind, balValue) - Math::min(mind, balValue);

		// Check rather to Heal or inflict damage to the player.
		if (health < balValue) {
			player->healDamage(player,CreatureAttribute::HEALTH, diffHealth, true);

		} else {
			player->inflictDamage(player, CreatureAttribute::HEALTH, diffHealth, true);

		}

		if (action < balValue) {
			player->healDamage(player,CreatureAttribute::ACTION, diffAction, true);

		} else {
			player->inflictDamage(player, CreatureAttribute::ACTION, diffAction, true);

		}

		if (mind < balValue) {
			player->healDamage(player,CreatureAttribute::MIND, diffMind, true);

		} else {
			player->inflictDamage(player, CreatureAttribute::MIND, diffMind, true);

		}

		player->sendSystemMessage("@innate:equil_active"); // Through sheer willpower, you force yourself into a state of equilibrium.
		player->showFlyText("combat_effects", "innate_equilibrium", 0, 255, 0); // +Equilibrium+

		player->addCooldown("innate_equilibrium", 3600 * 1000);

		return SUCCESS;
	}

};

#endif //EQUILIBRIUMCOMMAND_H_
