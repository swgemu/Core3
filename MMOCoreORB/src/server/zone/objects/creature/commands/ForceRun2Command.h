/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef FORCERUN2COMMAND_H_
#define FORCERUN2COMMAND_H_

#include "server/zone/objects/creature/buffs/PrivateSkillMultiplierBuff.h"
#include "JediQueueCommand.h"

class ForceRun2Command : public JediQueueCommand {
public:

	ForceRun2Command(const String& name, ZoneProcessServer* server)
	: JediQueueCommand(name, server) {
		// BuffCRC's, first one is used.
		buffCRCs.add(BuffCRC::JEDI_FORCE_RUN_2);
		buffCRCs.add(BuffCRC::JEDI_FORCE_RUN_1);
		buffCRCs.add(BuffCRC::JEDI_FORCE_RUN_3);

		skillMods.put("force_run", 2);
		skillMods.put("slope_move", 66);
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		int res = doJediSelfBuffCommand(creature);

		if (res != SUCCESS) {
			return res;
		}

		// need to apply the damage reduction in a separate buff so that the multiplication and division applies right
		Buff* buff = creature->getBuff(BuffCRC::JEDI_FORCE_RUN_2);
		if (buff == NULL)
			return GENERALERROR;

		ManagedReference<PrivateSkillMultiplierBuff*> multBuff = new PrivateSkillMultiplierBuff(creature, name.hashCode(), duration, BuffType::JEDI);

		Locker locker(multBuff);

		multBuff->setSkillModifier("private_damage_multiplier", 19);
		multBuff->setSkillModifier("private_damage_divisor", 20);

		creature->addBuff(multBuff);

		locker.release();

		Locker blocker(buff);

		buff->addSecondaryBuffCRC(multBuff->getBuffCRC());

		if (creature->hasBuff(String("burstrun").hashCode()) || creature->hasBuff(String("retreat").hashCode())) {
			creature->removeBuff(String("burstrun").hashCode());
			creature->removeBuff(String("retreat").hashCode());
		}

		return SUCCESS;
	}

};

#endif //FORCERUN2COMMAND_H_
