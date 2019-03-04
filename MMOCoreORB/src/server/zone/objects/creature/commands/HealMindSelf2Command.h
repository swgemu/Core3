/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef HEALMINDSELF2COMMAND_H_
#define HEALMINDSELF2COMMAND_H_

#include "ForceHealQueueCommand.h"

class HealMindSelf2Command : public ForceHealQueueCommand {
public:

	HealMindSelf2Command(const String& name, ZoneProcessServer* server)
		: ForceHealQueueCommand(name, server) {
	}

	float getCommandDuration(CreatureObject* object, const UnicodeString& arguments) const {
		return defaultTime * speed;
	}

};

#endif //HEALMINDSELF2COMMAND_H_
