/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef HEALBATTLEFATIGUEOTHER1COMMAND_H_
#define HEALBATTLEFATIGUEOTHER1COMMAND_H_

#include "ForceHealQueueCommand.h"

class HealBattleFatigueOther1Command : public ForceHealQueueCommand {
public:

	HealBattleFatigueOther1Command(const String& name, ZoneProcessServer* server)
		: ForceHealQueueCommand(name, server) {
	}

	float getCommandDuration(CreatureObject* object, const UnicodeString& arguments) const {
		return defaultTime * speed;
	}

};

#endif //HEALBATTLEFATIGUEOTHER1COMMAND_H_
