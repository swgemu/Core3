/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef HEALHEALTHSELF1COMMAND_H_
#define HEALHEALTHSELF1COMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "ForceHealQueueCommand.h"

class HealHealthSelf1Command : public ForceHealQueueCommand {
public:
	HealHealthSelf1Command(const String& name, ZoneProcessServer* server) : ForceHealQueueCommand(name, server) {}

};

#endif //HEALHEALTHSELF1COMMAND_H_
