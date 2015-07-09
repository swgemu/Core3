/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef HEALMINDWOUNDOTHER1COMMAND_H_
#define HEALMINDWOUNDOTHER1COMMAND_H_

#include "ForceHealQueueCommand.h"

class HealMindWoundOther1Command : public ForceHealQueueCommand {
public:
	HealMindWoundOther1Command(const String& name, ZoneProcessServer* server)
		: ForceHealQueueCommand(name, server) {
	}

};

#endif /* HEALMINDWOUNDOTHER1COMMAND_H_ */
