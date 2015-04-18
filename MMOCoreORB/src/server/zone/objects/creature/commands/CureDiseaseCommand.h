/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CUREDISEASECOMMAND_H_
#define CUREDISEASECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "CurePackCommand.h"

class CureDiseaseCommand : public CurePackCommand {

public:

	CureDiseaseCommand(const String& name, ZoneProcessServer* server)
		: CurePackCommand(name, server) {

		state = CreatureState::DISEASED;
	}


};

#endif //CUREDISEASECOMMAND_H_
