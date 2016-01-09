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
		// since this is a special case buff, these CRC's aren't exclusive. Instead we will use this list to select whichever one is not active
		buffCRCs.add(BuffCRC::JEDI_AVOID_INCAPACITATION);
		buffCRCs.add(BuffCRC::JEDI_AVOID_INCAPACITATION_1);
		buffCRCs.add(BuffCRC::JEDI_AVOID_INCAPACITATION_2);
		buffCRCs.add(BuffCRC::JEDI_AVOID_INCAPACITATION_3);
		buffCRCs.add(BuffCRC::JEDI_AVOID_INCAPACITATION_4);
		buffCRCs.add(BuffCRC::JEDI_AVOID_INCAPACITATION_5);
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		// SPECIAL - For Avoid Incapacitation, it can be stacked up to 6 times for a new buff object, and needs a new crc.
		uint32 buffCRCUsed = -1;

		for (int i=0; i < buffCRCs.size(); i++) {
			if (!creature->hasBuff(buffCRCs.get(i))) {
				buffCRCUsed = buffCRCs.get(i);
				break;
			}
		}

		if (buffCRCUsed == -1)
			return NOSTACKJEDIBUFF;

		// Avoid Incap is a special case since it stacks (whereas all other jedi buffs do not stack), so forego the
		// existing structure and build the buff manually

		int res = doCommonJediSelfChecks(creature);

		if (res != SUCCESS)
			return res;

		ManagedReference<PlayerObject*> playerObject = creature->getPlayerObject();

		uint32 buffcrc1 = BuffCRC::JEDI_AVOID_INCAPACITATION;

		if (creature->hasBuff(buffcrc1)) {
			creature->removeBuff(buffcrc1);
                }

		playerObject->setForcePower(playerObject->getForcePower() - forceCost);

		StringIdChatParameter startStringId("jedi_spam", "apply_avoidincapacitation");
		StringIdChatParameter endStringId("jedi_spam", "remove_avoidincapacitation");

		ManagedReference<Buff*> buff = new Buff(creature, buffCRCUsed, duration, BuffType::JEDI);

		Locker locker(buff);

		buff->setStartMessage(startStringId);
		buff->setEndMessage(endStringId);
		buff->setSkillModifier("avoid_incapacitation", 1);
		creature->addBuff(buff);

		if (!clientEffect.isEmpty())
			creature->playEffect(clientEffect, "");

		return SUCCESS;
	}

};

#endif //AVOIDINCAPACITATIONCOMMAND_H_
