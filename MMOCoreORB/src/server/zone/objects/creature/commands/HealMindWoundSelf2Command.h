/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef HEALMINDWOUNDSELF2COMMAND_H
#define HEALMINDWOUNDSELF2COMMAND_H

#include "ForceHealQueueCommand.h"

class HealMindWoundSelf2Command : public ForceHealQueueCommand {
public:

	HealMindWoundSelf2Command(const String& name, ZoneProcessServer* server)
		: ForceHealQueueCommand(name, server) {
	}

	float getCommandDuration(CreatureObject* object, const UnicodeString& arguments) const {
		return defaultTime * speed;
	}

};

#endif //HEALMINDWOUNDSELF2COMMAND_H
