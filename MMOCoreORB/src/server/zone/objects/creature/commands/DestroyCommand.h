/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef DESTROYCOMMAND_H_
#define DESTROYCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/player/sui/messagebox/SuiMessageBox.h"
#include "server/zone/objects/creature/commands/sui/DestroyCommandSuiCallback.h"

class DestroyCommand : public QueueCommand {
public:

	DestroyCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		//Note: This command doesn't do anything...

		return SUCCESS;
	}

};

#endif //DESTROYCOMMAND_H_
