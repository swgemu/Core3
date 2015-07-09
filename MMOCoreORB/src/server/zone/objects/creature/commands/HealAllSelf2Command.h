/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef HEALALLSELF2COMMAND_H_
#define HEALALLSELF2COMMAND_H_

#include "ForceHealQueueCommand.h"

class HealAllSelf2Command : public ForceHealQueueCommand {
public:
	HealAllSelf2Command(const String& name, ZoneProcessServer* server)
			: ForceHealQueueCommand(name, server) {

	}
};

#endif //HEALALLSELF2COMMAND_H_
