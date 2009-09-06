/*
 * ObjectControllerImplementation.cpp
 *
 *  Created on: 11/08/2009
 *      Author: victor
 */

#include "ObjectController.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/managers/objectcontroller/command/CommandConfigManager.h"
#include "server/zone/managers/objectcontroller/command/CommandList.h"

#include "server/zone/objects/creature/LuaCreatureObject.h"
#include "server/zone/objects/player/PlayerCreature.h"
#include "server/db/ServerDatabase.h"


ObjectControllerImplementation::ObjectControllerImplementation(ZoneProcessServerImplementation* server) : ManagedObjectImplementation(), Lua() {
	setLoggingName("ObjectController");

	ObjectControllerImplementation::server = server;

	configManager = new CommandConfigManager(server);
	queueCommands = new CommandList();

	setLogging(true);
	setGlobalLogging(true);

	info("loading queue commands...", true);
	configManager->loadSlashCommandsFile(queueCommands);

	StringBuffer infoMsg;
	infoMsg << "loaded " << queueCommands->size() << " commands";
	info(infoMsg.toString(), true);

	// LUA
	init();
	Luna<LuaCreatureObject>::Register(L);
	//runFile("scripts/testscript.lua");
}

bool ObjectControllerImplementation::transferObject(SceneObject* objectToTransfer, SceneObject* destinationObject, int containmentType, bool notifyClient) {
	ManagedReference<SceneObject*> parent = objectToTransfer->getParent();

	if (parent == NULL) {
		error("objectToTransfer parent is NULL in ObjectManager::transferObject");
		return false;
	}

	if (destinationObject->getZone() != NULL && objectToTransfer->getZone() == NULL)
		destinationObject->broadcastObject(objectToTransfer, false);

	uint32 oldContainmentType = objectToTransfer->getContainmentType();

	if (!parent->removeObject(objectToTransfer)) {
		error("could not remove objectToTransfer from parent in ObjectManager::transferObject");
		return false;
	}

	if (!destinationObject->addObject(objectToTransfer, containmentType, notifyClient)) {
		error("could not add objectToTransfer to destinationObject in ObjectManager::transferObject");
		parent->addObject(objectToTransfer, oldContainmentType);
		return false;
	}

	return true;
}

void ObjectControllerImplementation::enqueueCommand(CreatureObject* object, unsigned int actionCRC, unsigned int actionCount, uint64 targetID, UnicodeString& arguments) {
	// Pre: object is wlocked
	// Post: object is wlocked

	QueueCommand* sc = getQueueCommand(actionCRC);

	if (sc != NULL) {
		StringBuffer infoMsg;
		infoMsg << "activating queue command 0x" << hex << actionCRC << " " << sc->getSlashCommandName();
		object->info(infoMsg.toString());

		bool completed = sc->doQueueCommand(object, targetID, arguments);

		if (!completed)
			sc->onFail(actionCount, object);
		else {
			sc->onComplete(actionCount, object);

			if (sc->addToCombatQueue() && object->isPlayerCreature())
				((PlayerCreature*)object)->clearQueueAction(actionCount);
		}

		return;
	} else {
		StringBuffer msg;
		msg << "unregistered queue command 0x" << hex << actionCRC << " arguments: " << arguments.toString();
		object->error(msg.toString());
	}

	if (object->isPlayerCreature()) {
		PlayerCreature* player = (PlayerCreature*) object;

		player->clearQueueAction(actionCount, 0, 2, 0);
	}


	/*

	lua_getglobal(L, "runScript");
	lua_pushlightuserdata(L, object);

	if (lua_pcall(L, 1, 0, 0) != 0) {
		System::out << "Error running function " << "runScript" << " " << lua_tostring(L, -1);
	}*/

	/*LuaFunction runScript(getLuaState(), "runScript", 0);
			runScript << object; // push first argument
			callFunction(&runScript);*/
	//}

	/*System::out << "200000 executions = " << testingSpeed2.miliDifference() << "\n";

	Time testingSpeed;

	for (int i = 0; i < 200000; ++i) {
		//object->setBankCredits(i - 1);

		object->setBankCredits(i + 3);

	}

	System::out << "200000 executions = " << testingSpeed.miliDifference() << "\n";*/


}

void ObjectControllerImplementation::addQueueCommand(QueueCommand* command) {
	queueCommands->put(command);
}

QueueCommand* ObjectControllerImplementation::getQueueCommand(const String& name) {
	return queueCommands->getSlashCommand(name);
}

QueueCommand* ObjectControllerImplementation::getQueueCommand(uint32 crc) {
	return queueCommands->getSlashCommand(crc);
}
