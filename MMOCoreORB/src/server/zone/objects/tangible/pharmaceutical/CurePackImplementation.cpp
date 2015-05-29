/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#include "server/zone/objects/tangible/pharmaceutical/CurePack.h"

void CurePackImplementation::notifyLoadFromDatabase() {
	PharmaceuticalObjectImplementation::notifyLoadFromDatabase();

	if (commandToExecute.beginsWith("/")) {
		commandToExecute = commandToExecute.replaceFirst("/", "");
	}
}
