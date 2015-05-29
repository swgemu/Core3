/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#include "server/zone/objects/tangible/pharmaceutical/DotPack.h"

void DotPackImplementation::notifyLoadFromDatabase() {
	PharmaceuticalObjectImplementation::notifyLoadFromDatabase();

	if (commandToExecute.beginsWith("/")) {
		commandToExecute = commandToExecute.replaceFirst("/", "");
	}
}
