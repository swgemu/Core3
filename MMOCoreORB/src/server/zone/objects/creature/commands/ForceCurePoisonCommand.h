/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef FORCECUREPOISONCOMMAND_H_
#define FORCECUREPOISONCOMMAND_H_

#include "ForceHealQueueCommand.h"

class ForceCurePoisonCommand : public ForceHealQueueCommand {
public:

	ForceCurePoisonCommand(const String& name, ZoneProcessServer* server)
	: ForceHealQueueCommand(name, server) {

	}

};

#endif //FORCECUREPOISONCOMMAND_H_
