/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef APPLYPOISONCOMMAND_H_
#define APPLYPOISONCOMMAND_H_

#include "DotPackCommand.h"

class ApplyPoisonCommand : public DotPackCommand {
public:

	ApplyPoisonCommand(const String& name, ZoneProcessServer* server)
		: DotPackCommand(name, server) {
		skillName = "applypoison";
	}

};

#endif //APPLYPOISONCOMMAND_H_
