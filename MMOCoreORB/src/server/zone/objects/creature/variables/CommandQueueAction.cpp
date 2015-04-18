/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include "CommandQueueAction.h"

#include "server/zone/objects/creature/commands/QueueCommand.h"

#include "server/zone/objects/creature/CreatureObject.h"

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/managers/objectcontroller/ObjectController.h"

CommandQueueAction::CommandQueueAction(CreatureObject* cr, uint64 tar, uint32 command, uint32 acntr, const UnicodeString& amod) {
	actionCounter = acntr;

	target = tar;

	arguments = amod;

	creature = cr;
	queueCommand = command;
	compareToCounter = actionCounter;
}

void CommandQueueAction::clear(float timer, uint32 tab1, uint32 tab2) {
	creature->clearQueueAction(actionCounter, timer, tab1, tab2);
}

void CommandQueueAction::run() {

}
