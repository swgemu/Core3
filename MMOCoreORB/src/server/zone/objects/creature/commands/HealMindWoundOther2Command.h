/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef HEALMINDWOUNDOTHER2COMMAND_H_
#define HEALMINDWOUNDOTHER2COMMAND_H_

#include "ForceHealQueueCommand.h"

class HealMindWoundOther2Command : public ForceHealQueueCommand {
public:
	HealMindWoundOther2Command(const String& name, ZoneProcessServer* server)
		: ForceHealQueueCommand(name, server) {
	}
};

#endif /* HEALMINDWOUNDOTHER2COMMAND_H_ */
