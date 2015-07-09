/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef HEALACTIONSELF1COMMAND_H_
#define HEALACTIONSELF1COMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "ForceHealQueueCommand.h"

class HealActionSelf1Command : public ForceHealQueueCommand {
public:
	HealActionSelf1Command(const String& name, ZoneProcessServer* server) : ForceHealQueueCommand(name, server) {}
};

#endif //HEALACTIONSELF1COMMAND_H_
