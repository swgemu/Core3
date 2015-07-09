/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef HEALALLSELF1COMMAND_H_
#define HEALALLSELF1COMMAND_H_

#include "ForceHealQueueCommand.h"

class HealAllSelf1Command : public ForceHealQueueCommand {
public:

	HealAllSelf1Command(const String& name, ZoneProcessServer* server)
			: ForceHealQueueCommand(name, server) {

	}
};

#endif //HEALALLSELF1COMMAND_H_
