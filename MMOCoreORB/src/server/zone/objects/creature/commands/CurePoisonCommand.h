/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CUREPOISONCOMMAND_H_
#define CUREPOISONCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "CurePackCommand.h"

class CurePoisonCommand : public CurePackCommand {
public:

	CurePoisonCommand(const String& name, ZoneProcessServer* server)
		: CurePackCommand(name, server) {
		state = CreatureState::POISONED;
	}

};

#endif //CUREPOISONCOMMAND_H_
