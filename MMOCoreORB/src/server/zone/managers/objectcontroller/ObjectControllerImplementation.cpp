/*
 * ObjectControllerImplementation.cpp
 *
 *  Created on: 11/08/2009
 *      Author: victor
 */

#include "ObjectController.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/managers/objectcontroller/command/CommandQueueManager.h"

ObjectControllerImplementation::ObjectControllerImplementation(ZoneProcessServerImplementation* server) : ManagedObjectImplementation() {
	setLoggingName("ObjectController");

	ObjectControllerImplementation::server = server;

	commandQueueManager = new CommandQueueManager(server);
}
