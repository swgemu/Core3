/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef HEALACTIONWOUNDSELF1COMMAND_H_
#define HEALACTIONWOUNDSELF1COMMAND_H_

#include "ForceHealQueueCommand.h"

class HealActionWoundSelf1Command : public ForceHealQueueCommand {
public:

	HealActionWoundSelf1Command(const String& name, ZoneProcessServer* server)
		: ForceHealQueueCommand(name, server) {

	}
};

#endif //HEALACTIONWOUNDSELF1COMMAND_H_
