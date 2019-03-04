/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef TOTALHEALOTHERCOMMAND_H_
#define TOTALHEALOTHERCOMMAND_H_

#include "ForceHealQueueCommand.h"

class TotalHealOtherCommand : public ForceHealQueueCommand {
public:
	TotalHealOtherCommand(const String& name, ZoneProcessServer* server)
		: ForceHealQueueCommand(name, server) {
	}

	float getCommandDuration(CreatureObject* object, const UnicodeString& arguments) const {
		return defaultTime * speed;
	}

};

#endif //TOTALHEALOTHERCOMMAND_H_
