/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef HEALMINDSELF1COMMAND_H_
#define HEALMINDSELF1COMMAND_H_

#include "ForceHealQueueCommand.h"

class HealMindSelf1Command : public ForceHealQueueCommand {
public:

	HealMindSelf1Command(const String& name, ZoneProcessServer* server)
		: ForceHealQueueCommand(name, server) {
	}

	float getCommandDuration(CreatureObject* object, const UnicodeString& arguments) const {
		return defaultTime * speed;
	}

};

#endif //HEALMINDSELF1COMMAND_H_
