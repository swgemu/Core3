/*
Copyright (C) 2007 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.
*/

#ifndef RESOURCECOMMAND_H_
#define RESOURCECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class ResourceCommand : public QueueCommand {
public:

	ResourceCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		StringTokenizer args(arguments.toString());

		try {
			String command;

			if(args.hasMoreTokens())
				args.getStringToken(command);

			if(command == "list") {
				listResources(creature, &args);

			} else if(command == "health") {
				healthCheck(creature, &args);

			} else if(command == "dump") {
				dumpResources(creature, &args);

			} else if(command == "despawn") {
				despawnResource(creature, &args);

			} else if(command == "info") {
				listResourceInfo(creature, &args);

			} else {
				throw Exception();
			}

		} catch (Exception& e){
			creature->sendSystemMessage("invalid arguments for resources command:  /resource [option] [params]");
			creature->sendSystemMessage("		list [planet] : Lists resources on specified planet");
			creature->sendSystemMessage("		info [resource name] : Lists Info about a specific resource");
		}

		return SUCCESS;
	}

	void listResources(CreatureObject* creature, StringTokenizer* args) const {
		if(creature->getZoneServer() == NULL)
			return;

		String planet = "";
		if(args->hasMoreTokens())
			args->getStringToken(planet);

		if(planet.isEmpty())
			throw Exception();

		ResourceManager* resMan = creature->getZoneServer()->getResourceManager();
		resMan->listResourcesForPlanetOnScreen(creature, planet);
	}

	void healthCheck(CreatureObject* creature, StringTokenizer* args) const {
		if(creature->getZoneServer() == NULL)
			return;

		ResourceManager* resMan = creature->getZoneServer()->getResourceManager();

		creature->sendSystemMessage(resMan->healthCheck());
	}

	void dumpResources(CreatureObject* creature, StringTokenizer* args) const {
		if(creature->getZoneServer() == NULL)
			return;

		ResourceManager* resMan = creature->getZoneServer()->getResourceManager();

		creature->sendSystemMessage(resMan->dumpResources());
	}

	void despawnResource(CreatureObject* creature, StringTokenizer* args) const {
		if(creature->getZoneServer() == NULL)
			return;

		String resourceName = "";
		if(args->hasMoreTokens())
			args->getStringToken(resourceName);


		ResourceManager* resMan = creature->getZoneServer()->getResourceManager();

		creature->sendSystemMessage(resMan->despawnResource(resourceName));
	}

	void listResourceInfo(CreatureObject* creature, StringTokenizer* args) const {
		if(creature->getZoneServer() == NULL)
			return;

		String resourceName = "";
		if(args->hasMoreTokens())
			args->getStringToken(resourceName);

		ResourceManager* resMan = creature->getZoneServer()->getResourceManager();

		ManagedReference<ResourceSpawn*> spawn = resMan->getResourceSpawn(resourceName);
		if(spawn == NULL) {
			creature->sendSystemMessage("Resource not found");
			return;
		}

		creature->sendSystemMessage("******** " + spawn->getName() + " *********");

		uint64 despawned = spawn->getDespawned();
		uint64 currTime = System::getTime();

		int diff = 0;
		if(despawned > currTime) {
			diff = despawned - currTime;
		} else {
			diff = currTime - despawned;
		}

		int days = (diff / 60 / 60 / 24);
		int hours = ((diff / 60 / 60) % 24);
		int minutes = ((diff / 60) % 60);

		if(despawned > currTime) {
			creature->sendSystemMessage("Expires in: " + String::valueOf(days) + " days, " + String::valueOf(hours) + " hours, " + String::valueOf(minutes) + " minutes");
			creature->sendSystemMessage("Pool: " + String::valueOf(spawn->getSpawnPool()));

			for(int i = 0; i < spawn->getSpawnMapSize(); ++i) {
				creature->sendSystemMessage("Spawned on: " + spawn->getSpawnMapZone(i));
			}

		} else {
			creature->sendSystemMessage("Expired: " + String::valueOf(days) + " days, " + String::valueOf(hours) + " hours, " + String::valueOf(minutes) + " minutes ago");
		}


		for(int i = 0; i < 12; ++i) {
			String attribute = "";
			int value = spawn->getAttributeAndValue(attribute, i);
			if(attribute != "") {
				creature->sendSystemMessage(attribute + ": " + String::valueOf(value));
			}
		}
	}

};

#endif //RESOURCECOMMAND_H_
