/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef HEALHEALTHWOUNDSELF2COMMAND_H_
#define HEALHEALTHWOUNDSELF2COMMAND_H_

#include "ForceHealQueueCommand.h"

class HealHealthWoundSelf2Command : public ForceHealQueueCommand {
public:

	HealHealthWoundSelf2Command(const String& name, ZoneProcessServer* server)
		: ForceHealQueueCommand(name, server) {
	}
};

#endif //HEALHEALTHWOUNDSELF2COMMAND_H_
