/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef HEALHEALTHWOUNDOTHER2COMMAND_H_
#define HEALHEALTHWOUNDOTHER2COMMAND_H_

#include "ForceHealQueueCommand.h"

class HealHealthWoundOther2Command : public ForceHealQueueCommand {
public:
	HealHealthWoundOther2Command(const String& name, ZoneProcessServer* server)
		: ForceHealQueueCommand(name, server) {
	}
};

#endif /* HEALHEALTHWOUNDOTHER2COMMAND_H_ */
