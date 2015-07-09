/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef HEALHEALTHSELF2COMMAND_H_
#define HEALHEALTHSELF2COMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "ForceHealQueueCommand.h"

class HealHealthSelf2Command : public ForceHealQueueCommand {
public:
	HealHealthSelf2Command(const String& name, ZoneProcessServer* server) : ForceHealQueueCommand(name, server) {}
};

#endif //HEALHEALTHSELF2COMMAND_H_
