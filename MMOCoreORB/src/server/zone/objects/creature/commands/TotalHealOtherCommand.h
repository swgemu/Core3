/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef TOTALHEALOTHERCOMMAND_H_
#define TOTALHEALOTHERCOMMAND_H_

#include "ForceHealQueueCommand.h"

class TotalHealOtherCommand : public ForceHealQueueCommand {
public:
	TotalHealOtherCommand(const String& name, ZoneProcessServer* server) : ForceHealQueueCommand(name, server) {}
};

#endif //TOTALHEALOTHERCOMMAND_H_
