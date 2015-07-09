/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef HEALACTIONWOUNDOTHER1COMMAND_H_
#define HEALACTIONWOUNDOTHER1COMMAND_H_

#include "ForceHealQueueCommand.h"

class HealActionWoundOther1Command : public ForceHealQueueCommand {
public:
	HealActionWoundOther1Command(const String& name, ZoneProcessServer* server)
		: ForceHealQueueCommand(name, server) {
	}
};

#endif /* HEALACTIONWOUNDOTHER1COMMAND_H_ */
