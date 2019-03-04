/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef HEALHEALTHWOUNDSELF1COMMAND_H_
#define HEALHEALTHWOUNDSELF1COMMAND_H_

#include "ForceHealQueueCommand.h"

class HealHealthWoundSelf1Command : public ForceHealQueueCommand {
public:

	HealHealthWoundSelf1Command(const String& name, ZoneProcessServer* server)
		: ForceHealQueueCommand(name, server) {
	}

	float getCommandDuration(CreatureObject* object, const UnicodeString& arguments) const {
		return defaultTime * speed;
	}

};

#endif //HEALHEALTHWOUNDSELF1COMMAND_H_
