/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef HEALBATTLEFATIGUEOTHER2COMMAND_H_
#define HEALBATTLEFATIGUEOTHER2COMMAND_H_

#include "ForceHealQueueCommand.h"

class HealBattleFatigueOther2Command : public ForceHealQueueCommand {
public:

	HealBattleFatigueOther2Command(const String& name, ZoneProcessServer* server)
		: ForceHealQueueCommand(name, server) {

	}
};

#endif //HEALBATTLEFATIGUEOTHER2COMMAND_H_
