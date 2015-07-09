/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef HEALACTIONWOUNDSELF2COMMAND_H_
#define HEALACTIONWOUNDSELF2COMMAND_H_

#include "ForceHealQueueCommand.h"

class HealActionWoundSelf2Command : public ForceHealQueueCommand {
public:

	HealActionWoundSelf2Command(const String& name, ZoneProcessServer* server)
		: ForceHealQueueCommand(name, server) {

	}
};

#endif //HEALACTIONWOUNDSELF2COMMAND_H_
