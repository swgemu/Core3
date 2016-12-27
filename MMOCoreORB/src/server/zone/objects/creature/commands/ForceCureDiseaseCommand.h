/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef FORCECUREDISEASECOMMAND_H_
#define FORCECUREDISEASECOMMAND_H_

#include "ForceHealQueueCommand.h"

class ForceCureDiseaseCommand : public ForceHealQueueCommand {
public:

	ForceCureDiseaseCommand(const String& name, ZoneProcessServer* server)
		: ForceHealQueueCommand(name, server) {

	}
};

#endif //FORCECUREPOISONCOMMAND_H_
