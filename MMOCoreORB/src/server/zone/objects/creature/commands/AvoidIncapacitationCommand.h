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
		 skillMods.put("avoid_incapacitation", 1);
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		// SPECIAL - For Avoid Incapacitation, which is a special case buff, if it's determined that it should only be stacked up to 6 times for a new buff object, then it'll needs a new crc from the other 5 in string-files.
		// PLUS: There is no concrete evidence for what's stated in 'SPECIAL' sentence above, beyond the existence of 6 CRCs themselves.

		if (creature->hasBuff(BuffCRC::JEDI_AVOID_INCAPACITATION)) {

			int res = doCommonJediSelfChecks(creature);

			if (res != SUCCESS)
				return res;

			creature->renewBuff(buffCRC, duration, true);

			doForceCost(creature);

			if (!clientEffect.isEmpty())
				creature->playEffect(clientEffect, "");

			return SUCCESS;
		} else {
			return doJediSelfBuffCommand(creature);
		}
	}

};

#endif //AVOIDINCAPACITATIONCOMMAND_H_
