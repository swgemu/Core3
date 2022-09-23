/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef BERSERK2COMMAND_H_
#define BERSERK2COMMAND_H_

class Berserk2Command : public QueueCommand {
public:

	Berserk2Command(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ManagedReference<WeaponObject*> weapon = creature->getWeapon();

		if (weapon == nullptr || (!weapon->isMeleeWeapon() && !weapon->isUnarmedWeapon())) {
			creature->sendSystemMessage("@cbt_spam:berserk_fail_single");
			creature->sendStateCombatSpam("cbt_spam", "berserk_fail", 0);

			return INVALIDWEAPON;
		}

		// Roll chance to fail
		int mod = creature->getSkillMod("berserk");
		int roll = System::random(100) + mod;

		if (roll < 25) {
			creature->sendSystemMessage("@cbt_spam:berserk_fail_single");
			creature->sendStateCombatSpam("cbt_spam", "berserk_fail", 0);

			return GENERALERROR;
		}

		int healthCost = creature->calculateCostAdjustment(CreatureAttribute::STRENGTH, 100);
		int actionCost = creature->calculateCostAdjustment(CreatureAttribute::QUICKNESS, 100);
		int mindCost = creature->calculateCostAdjustment(CreatureAttribute::FOCUS, 50);

		if (creature->getHAM(CreatureAttribute::HEALTH) <= healthCost || creature->getHAM(CreatureAttribute::ACTION) <= actionCost || creature->getHAM(CreatureAttribute::MIND) <= mindCost) {
			creature->sendSystemMessage("@cbt_spam:berserk_fail_single");
			creature->sendStateCombatSpam("cbt_spam", "berserk_fail", 0);

			return GENERALERROR;
		}

		creature->inflictDamage(creature, CreatureAttribute::HEALTH, healthCost, false, true, false);
		creature->inflictDamage(creature, CreatureAttribute::ACTION, actionCost, false, true, false);
		creature->inflictDamage(creature, CreatureAttribute::MIND, mindCost, false, true, false);

		int time = 40;
		creature->setBerserkedState(time);

		creature->sendSystemMessage("@cbt_spam:berserk_success_single");
		creature->sendStateCombatSpam("cbt_spam", "berserk_success", 0);

		return SUCCESS;
	}
};

#endif //BERSERK2COMMAND_H_
