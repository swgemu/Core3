/*
 * StartingLocationTerminalImplementation.cpp
 *
 *  Created on: 12/08/2009
 *      Author: victor
 */

#include "StartingLocationTerminal.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/packets/object/StartingLocationList.h"

/*
StartingLocationTerminalImplementation::StartingLocationTerminalImplementation(LuaObject* templateData) :
	TerminalImplementation(templateData) {

	setLoggingName("StartingLocationTerminal");
}*/

void StartingLocationTerminalImplementation::initializeTransientMembers() {
	TerminalImplementation::initializeTransientMembers();

	setLoggingName("StartingLocationTerminal");
}

int StartingLocationTerminalImplementation::useObject(SceneObject* object) {
	if (!object->isCreatureObject())
		return 1;

	StartingLocationList* sll = new StartingLocationList((CreatureObject*)object);
	object->sendMessage(sll);

	return 0;
}
