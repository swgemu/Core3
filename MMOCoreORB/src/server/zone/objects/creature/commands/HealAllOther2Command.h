/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef HEALALLOTHER2COMMAND_H_
#define HEALALLOTHER2COMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/packets/object/CombatAction.h"
#include "ForceHealQueueCommand.h"

class HealAllOther2Command : public ForceHealQueueCommand {
public:
	HealAllOther2Command(const String& name, ZoneProcessServer* server)
		: ForceHealQueueCommand(name, server) {
	}
};

#endif /* HEALALLOTHER2COMMAND_H_ */
