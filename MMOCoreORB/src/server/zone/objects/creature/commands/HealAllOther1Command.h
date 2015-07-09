/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef HEALALLOTHER1COMMAND_H_
#define HEALALLOTHER1COMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/packets/object/CombatAction.h"
#include "ForceHealQueueCommand.h"

class HealAllOther1Command : public ForceHealQueueCommand {
public:
	HealAllOther1Command(const String& name, ZoneProcessServer* server)
		: ForceHealQueueCommand(name, server) {
	}
};

#endif /* HEALALLOTHER1COMMAND_H_ */
