/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef EXTINGUISHFIRECOMMAND_H_
#define EXTINGUISHFIRECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "CurePackCommand.h"

class ExtinguishFireCommand : public CurePackCommand {
public:

	ExtinguishFireCommand(const String& name, ZoneProcessServer* server)
		: CurePackCommand(name, server) {
		state = CreatureState::ONFIRE;
	}

};

#endif //EXTINGUISHFIRECOMMAND_H_
