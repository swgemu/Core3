/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef TOTALHEALSELFCOMMAND_H_
#define TOTALHEALSELFCOMMAND_H_

#include "ForceHealQueueCommand.h"

class TotalHealSelfCommand : public ForceHealQueueCommand {
public:
	TotalHealSelfCommand(const String& name, ZoneProcessServer* server) : ForceHealQueueCommand(name, server) {}
};

#endif /* TOTALHEALSELFCOMMAND_H_ */
