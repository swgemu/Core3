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

			} else if(command == "find") {
				findResources(creature, &args);

			} else if(command == "create") {
				giveResource(creature, &args);

			} else {
				throw Exception();
			}

		} catch (Exception& e){
			creature->sendSystemMessage("invalid arguments for resources command:  /resource <option> [params]");
			creature->sendSystemMessage("		list <planet> : Lists resources on specified planet");
			creature->sendSystemMessage("		info <resource name> : Lists Info about a specific resource");
			creature->sendSystemMessage("		find <class> <attribute> <gt|lt> <value> [<and|or> <attribute> <gt|lt> <value> [...]]");
			creature->sendSystemMessage("		create <name> [quantity] : Spawns resource in inventory");
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

	void findResources(CreatureObject* creature, StringTokenizer* args) const {
		if(creature->getZoneServer() == NULL || !args->hasMoreTokens())
			throw Exception();

		ResourceManager* resMan = creature->getZoneServer()->getResourceManager();
		if (resMan == NULL)
			throw Exception();

		String resourceType = "";
		args->getStringToken(resourceType);

		ResourceSpawner* resSpawner = resMan->getResourceSpawner();
		if (resSpawner == NULL)
			throw Exception();

		ResourceMap* map = resSpawner->getResourceMap();
		if (map == NULL)
			throw Exception();

		Reference<ResourceMap*> resultsMap = new ResourceMap();
		map->getTypeSubset(*resultsMap, resourceType);

		if (resultsMap->isEmpty()) {
			creature->sendSystemMessage("No results from resource type.");
			return;
		}

		bool andFlag = true;
		while (args->hasMoreTokens()) {
			String attribute = "";
			args->getStringToken(attribute);

			if (!args->hasMoreTokens())
				throw Exception();

			String qualifier = "";
			args->getStringToken(qualifier);

			if (!args->hasMoreTokens() || (qualifier != "gt" && qualifier != "lt"))
				throw Exception();

			int value = args->getIntToken();

			Reference<ResourceMap*> tempMap = new ResourceMap();

			if (andFlag) //and means only get results from that which we have already eliminated
				resultsMap->getAttributeSubset(*tempMap, attribute);
			else //or means look at everything and concat the vectors
				map->getAttributeSubset(*tempMap, attribute);

			for (int i = tempMap->size() - 1; i >= 0 && tempMap->size() > 0; i--) {
				ResourceSpawn* spawn = tempMap->get(i);
				int stat = 0;

				if (attribute == "res_cold_resist")
					stat = spawn->getValueOf(CraftingManager::CR);
				else if (attribute == "res_conductivity")
					stat = spawn->getValueOf(CraftingManager::CD);
				else if (attribute == "res_decay_resist")
					stat = spawn->getValueOf(CraftingManager::DR);
				else if (attribute == "res_heat_resist")
					stat = spawn->getValueOf(CraftingManager::HR);
				else if (attribute == "res_flavor")
					stat = spawn->getValueOf(CraftingManager::FL);
				else if (attribute == "res_malleability")
					stat = spawn->getValueOf(CraftingManager::MA);
				else if (attribute == "res_potential_energy")
					stat = spawn->getValueOf(CraftingManager::PE);
				else if (attribute == "res_quality")
					stat = spawn->getValueOf(CraftingManager::OQ);
				else if (attribute == "res_shock_resistance")
					stat = spawn->getValueOf(CraftingManager::SR);
				else if (attribute == "res_toughness")
					stat = spawn->getValueOf(CraftingManager::UT);
				else {
					creature->sendSystemMessage("Invalid attribute name " + attribute + " in /resource find");
					return;
				}

				if (qualifier == "gt") {
					if (stat < value)
						tempMap->drop(spawn->getName().toLowerCase());
				} else {
					if (stat > value)
						tempMap->drop(spawn->getName().toLowerCase());
				}
			}

			if (andFlag)
				resultsMap = tempMap;
			else
				resultsMap->addAll(*tempMap);

			// no grab the trailing conjunction so we know what to do with the next argument
			if (args->hasMoreTokens()) {
				String conjunction = "";
				args->getStringToken(conjunction);

				if (conjunction == "and")
					andFlag = true;
				else
					andFlag = false;
			}
		}

		if (resultsMap->isEmpty()) {
			creature->sendSystemMessage("No results from resource search.");
			return;
		}

		ManagedReference<SuiMessageBox*> box = new SuiMessageBox(creature, 0);
		box->setPromptTitle(String::valueOf(resultsMap->size()) + " Results from Resource Find");

		StringBuffer promptText;
		for (int i = 0; i < resultsMap->size(); i++) {
			ResourceSpawn* spawn = resultsMap->get(i);

			promptText << String::valueOf(i) << ": " << spawn->getName() << ", " << spawn->getFinalClass() << endl;
			for (int j = 0; j < 12; j++) {
				String attribute = "";
				int value = spawn->getAttributeAndValue(attribute, j);
				if (attribute != "") {
					StringId attrName("obj_attr_n", attribute);
					promptText << "    " << StringIdManager::instance()->getStringId(attrName).toString() << ": " << String::valueOf(value) << endl;
				}
			}

		}

		box->setPromptText(promptText.toString());

		creature->sendMessage(box->generateMessage());
	}

	void giveResource(CreatureObject* creature, StringTokenizer* args) const {
		if(creature->getZoneServer() == NULL || !args->hasMoreTokens())
			throw Exception();

		ResourceManager* resMan = creature->getZoneServer()->getResourceManager();
		if (resMan == NULL)
			throw Exception();

		if (!args->hasMoreTokens())
			throw Exception();

		String resName = "";
		args->getStringToken(resName);

		int quantity = ResourceManager::RESOURCE_DEED_QUANTITY;
		if (args->hasMoreTokens())
			quantity = args->getIntToken();

		resMan->givePlayerResource(creature, resName.toLowerCase(), quantity);
	}

};

#endif //RESOURCECOMMAND_H_
