/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef HEALSTATESSELFCOMMAND_H_
#define HEALSTATESSELFCOMMAND_H_

#include "ForceHealQueueCommand.h"

class HealStatesSelfCommand : public ForceHealQueueCommand {
public:

	HealStatesSelfCommand(const String& name, ZoneProcessServer* server)
		: ForceHealQueueCommand(name, server) {

	}
};

#endif //HEALSTATESSELFCOMMAND_H_
