/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CENTEROFBEINGCOMMAND_H_
#define CENTEROFBEINGCOMMAND_H_

class CenterOfBeingCommand : public QueueCommand {
public:

	CenterOfBeingCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		PlayerObject* ghost = creature->getPlayerObject();

		if (creature->hasBuff(STRING_HASHCODE("centerofbeing"))) {
			creature->sendSystemMessage("@combat_effects:already_centered");
			return GENERALERROR;
		}

		WeaponObject* weapon = creature->getWeapon();

		int duration = 0;
		int efficacy = 0;

		if (weapon->isUnarmedWeapon()) {
			duration = creature->getSkillMod("center_of_being_duration_unarmed");
			efficacy = creature->getSkillMod("unarmed_center_of_being_efficacy");
		} else if (weapon->isOneHandMeleeWeapon()) {
			duration = creature->getSkillMod("center_of_being_duration_onehandmelee");
			efficacy = creature->getSkillMod("onehandmelee_center_of_being_efficacy");
		} else if (weapon->isTwoHandMeleeWeapon()) {
			duration = creature->getSkillMod("center_of_being_duration_twohandmelee");
			efficacy = creature->getSkillMod("twohandmelee_center_of_being_efficacy");
		} else if (weapon->isPolearmWeaponObject()) {
			duration = creature->getSkillMod("center_of_being_duration_polearm");
			efficacy = creature->getSkillMod("polearm_center_of_being_efficacy");
		} else
			return GENERALERROR;

		if (duration == 0 || efficacy == 0)
			return GENERALERROR;

		Buff* centered = new Buff(creature, STRING_HASHCODE("centerofbeing"), duration, BuffType::SKILL);

		Locker locker(centered);

		centered->setSkillModifier("private_center_of_being", efficacy);

		StringIdChatParameter startMsg("combat_effects", "center_start");
		StringIdChatParameter endMsg("combat_effects", "center_stop");
		centered->setStartMessage(startMsg);
		centered->setEndMessage(endMsg);

		centered->setStartFlyText("combat_effects", "center_start_fly", 0, 255, 0);
		centered->setEndFlyText("combat_effects", "center_stop_fly", 255, 0, 0);

		creature->addBuff(centered);

		return SUCCESS;
	}

};

#endif //CENTEROFBEINGCOMMAND_H_
