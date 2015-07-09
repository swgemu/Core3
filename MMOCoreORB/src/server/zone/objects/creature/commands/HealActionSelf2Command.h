/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef HEALACTIONSELF2COMMAND_H_
#define HEALACTIONSELF2COMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "ForceHealQueueCommand.h"

class HealActionSelf2Command : public ForceHealQueueCommand {
public:
	HealActionSelf2Command(const String& name, ZoneProcessServer* server) : ForceHealQueueCommand(name, server) {}
};

#endif //HEALACTIONSELF2COMMAND_H_
