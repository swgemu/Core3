/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef HEALACTIONWOUNDOTHER2COMMAND_H_
#define HEALACTIONWOUNDOTHER2COMMAND_H_

#include "ForceHealQueueCommand.h"

class HealActionWoundOther2Command : public ForceHealQueueCommand {
public:
	HealActionWoundOther2Command(const String& name, ZoneProcessServer* server)
		: ForceHealQueueCommand(name, server) {
	}

	float getCommandDuration(CreatureObject* object, const UnicodeString& arguments) const {
		return defaultTime * speed;
	}

};

#endif /* HEALACTIONWOUNDOTHER2COMMAND_H_ */
