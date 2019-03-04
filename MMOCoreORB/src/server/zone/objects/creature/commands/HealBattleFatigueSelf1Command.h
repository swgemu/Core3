/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef HEALBATTLEFATIGUESELF1COMMAND_H_
#define HEALBATTLEFATIGUESELF1COMMAND_H_

#include "ForceHealQueueCommand.h"

class HealBattleFatigueSelf1Command : public ForceHealQueueCommand {
public:

	HealBattleFatigueSelf1Command(const String& name, ZoneProcessServer* server)
		: ForceHealQueueCommand(name, server) {
	}

	float getCommandDuration(CreatureObject* object, const UnicodeString& arguments) const {
		return defaultTime * speed;
	}

};

#endif //HEALBATTLEFATIGUESELF1COMMAND_H_
