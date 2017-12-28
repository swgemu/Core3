/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#include "server/zone/objects/tangible/pharmaceutical/CurePack.h"
#include "server/zone/objects/tangible/pharmaceutical/PharmaceuticalObject.h"
#include "system/lang/String.h"

void CurePackImplementation::notifyLoadFromDatabase() {
	PharmaceuticalObjectImplementation::notifyLoadFromDatabase();

	if (commandToExecute.beginsWith("/")) {
		commandToExecute = commandToExecute.replaceFirst("/", "");
	}
}
