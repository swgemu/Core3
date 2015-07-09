/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef HEALMINDWOUNDSELF1COMMAND_H
#define HEALMINDWOUNDSELF1COMMAND_H

#include "ForceHealQueueCommand.h"

class HealMindWoundSelf1Command : public ForceHealQueueCommand {
public:

	HealMindWoundSelf1Command(const String& name, ZoneProcessServer* server)
		: ForceHealQueueCommand(name, server) {

	}
};

#endif //HEALMINDWOUNDSELF1COMMAND_H
