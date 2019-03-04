/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef HEALSTATESOTHERCOMMAND_H_
#define HEALSTATESOTHERCOMMAND_H_

#include "ForceHealQueueCommand.h"

class HealStatesOtherCommand : public ForceHealQueueCommand {
public:

	HealStatesOtherCommand(const String& name, ZoneProcessServer* server)
		: ForceHealQueueCommand(name, server) {
	}

	float getCommandDuration(CreatureObject* object, const UnicodeString& arguments) const {
		return defaultTime * speed;
	}

};

#endif //HEALSTATESOTHERCOMMAND_H_
