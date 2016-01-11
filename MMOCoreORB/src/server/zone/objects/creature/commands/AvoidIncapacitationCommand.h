/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef AVOIDINCAPACITATIONCOMMAND_H_
#define AVOIDINCAPACITATIONCOMMAND_H_

#include "JediQueueCommand.h"

class AvoidIncapacitationCommand : public JediQueueCommand {
public:

	AvoidIncapacitationCommand(const String& name, ZoneProcessServer* server)
: JediQueueCommand(name, server) {
		buffCRC = BuffCRC::JEDI_AVOID_INCAPACITATION;
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		// SPECIAL - For Avoid Incapacitation, it can be stacked (maybe up to 6 times, if looking at the client CRCs)
		// TODO: implement AI stacking
		// Avoid Incap is a special case since it stacks (whereas all other jedi buffs do not stack), so forego the
		// existing structure and build the buff manually

		int res = doCommonJediSelfChecks(creature);

		if (res != SUCCESS)
			return res;

		ManagedReference<Buff*> buff = new Buff(creature, buffCRC, duration, BuffType::JEDI);

		Locker locker(buff);

		buff->setSkillModifier("avoid_incapacitation", 1);
		creature->addBuff(buff);

		ManagedReference<PlayerObject*> playerObject = creature->getPlayerObject();
		playerObject->setForcePower(playerObject->getForcePower() - forceCost);

		if (!clientEffect.isEmpty())
			creature->playEffect(clientEffect, "");

		return SUCCESS;
	}

};

#endif //AVOIDINCAPACITATIONCOMMAND_H_
