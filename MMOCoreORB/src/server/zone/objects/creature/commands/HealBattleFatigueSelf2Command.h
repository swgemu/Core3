/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef HEALBATTLEFATIGUESELF2COMMAND_H_
#define HEALBATTLEFATIGUESELF2COMMAND_H_

#include "ForceHealQueueCommand.h"

class HealBattleFatigueSelf2Command : public ForceHealQueueCommand {
public:

	HealBattleFatigueSelf2Command(const String& name, ZoneProcessServer* server)
		: ForceHealQueueCommand(name, server) {
	}

	float getCommandDuration(CreatureObject* object, const UnicodeString& arguments) const {
		return defaultTime * speed;
	}

};

#endif //HEALBATTLEFATIGUESELF2COMMAND_H_
