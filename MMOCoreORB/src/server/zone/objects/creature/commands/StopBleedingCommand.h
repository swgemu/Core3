/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef STOPBLEEDINGCOMMAND_H_
#define STOPBLEEDINGCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/packets/object/CombatAction.h"
#include "ForceHealQueueCommand.h"

class StopBleedingCommand : public ForceHealQueueCommand {
public:

	StopBleedingCommand(const String& name, ZoneProcessServer* server)
		: ForceHealQueueCommand(name, server) {

	}
};

#endif //STOPBLEEDINGCOMMAND_H_
