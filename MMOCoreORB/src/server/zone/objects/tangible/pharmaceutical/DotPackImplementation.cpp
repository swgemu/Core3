/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#include "server/zone/objects/tangible/pharmaceutical/DotPack.h"
#include "server/zone/objects/tangible/pharmaceutical/PharmaceuticalObject.h"
#include "system/lang/String.h"

void DotPackImplementation::notifyLoadFromDatabase() {
	PharmaceuticalObjectImplementation::notifyLoadFromDatabase();

	if (commandToExecute.beginsWith("/")) {
		commandToExecute = commandToExecute.replaceFirst("/", "");
	}
}
