/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef STOPBLEEDINGCOMMAND_H_
#define STOPBLEEDINGCOMMAND_H_

#include "ForceHealQueueCommand.h"

class StopBleedingCommand : public ForceHealQueueCommand {
public:

	StopBleedingCommand(const String& name, ZoneProcessServer* server)
		: ForceHealQueueCommand(name, server) {
	}

	float getCommandDuration(CreatureObject* object, const UnicodeString& arguments) const {
		return defaultTime * speed;
	}

};

#endif //STOPBLEEDINGCOMMAND_H_
