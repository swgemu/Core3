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
		// since this is a special case buff, these CRC's aren't exclusive. Instead we will use this list to select whichever one is not active
		// buffCRCs.add(BuffCRC::JEDI_AVOID_INCAPACITATION);
		// buffCRCs.add(BuffCRC::JEDI_AVOID_INCAPACITATION_1);
		// buffCRCs.add(BuffCRC::JEDI_AVOID_INCAPACITATION_2);
		// buffCRCs.add(BuffCRC::JEDI_AVOID_INCAPACITATION_3);
		// buffCRCs.add(BuffCRC::JEDI_AVOID_INCAPACITATION_4);
		// buffCRCs.add(BuffCRC::JEDI_AVOID_INCAPACITATION_5);

		 skillMods.put("avoid_incapacitation", 1);
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		// SPECIAL - For Avoid Incapacitation, it can be stacked up to 6 times for a new buff object, and needs a new crc.
		// PLUS: There is no evidence for what's stated in 'SPECIAL' sentence above, beyond the existence of 6 CRCs themselves.

		uint32 buffcrc0 = BuffCRC::JEDI_AVOID_INCAPACITATION;

		if (creature->hasBuff(BuffCRC::JEDI_AVOID_INCAPACITATION)) {

			int res = doCommonJediSelfChecks(creature);

			if (res != SUCCESS)
				return res;

			StringIdChatParameter startStringId("jedi_spam", "apply_avoidincapacitation");
			StringIdChatParameter endStringId("jedi_spam", "remove_avoidincapacitation");

			Locker creatureLocker(creature);
			ManagedReference<Buff*> buff = creature->getBuff(BuffCRC::JEDI_AVOID_INCAPACITATION);
			Locker locker(buff);

			buff->renew(30);
			ManagedReference<PlayerObject*> playerObject = creature->getPlayerObject();
			playerObject->setForcePower(playerObject->getForcePower() - forceCost);

			if (!creature->hasBuff(buffcrc0)) {
				buff->setStartMessage(startStringId);
			}
			buff->setEndMessage(endStringId);
			buff->setSkillModifier("avoid_incapacitation", 1);
			creature->addBuff(buff);

			if (!clientEffect.isEmpty())
				creature->playEffect(clientEffect, "");

			buff->sendTo(creature);

			return SUCCESS;
		} else {
			return doJediSelfBuffCommand(creature);
		}
	}

};

#endif //AVOIDINCAPACITATIONCOMMAND_H_
