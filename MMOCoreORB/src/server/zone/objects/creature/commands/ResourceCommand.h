/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef RESOURCECOMMAND_H_
#define RESOURCECOMMAND_H_

#include "server/zone/managers/stringid/StringIdManager.h"

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

		ResourceManager* resMan = creature->getZoneServer()->getResourceManager();

		Locker locker(resMan);

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
			creature->sendSystemMessage("		health : Lists resource pool health stats");
			creature->sendSystemMessage("		dump : Performs manual dump of all resources to resource_manager_spawns.lua");
			creature->sendSystemMessage("		despawn <resource name> : Despawns a specific resource");
			creature->sendSystemMessage("		info <resource name> : Lists Info about a specific resource");
			creature->sendSystemMessage("		find <class> <attribute> <gt|lt> <value> [<and|or> <attribute> <gt|lt> <value> [...]]");
			creature->sendSystemMessage("		create <name> [quantity] : Spawns resource in inventory");
		}

		return SUCCESS;
	}

	void listResources(CreatureObject* creature, StringTokenizer* args) const {
		if(creature->getZoneServer() == nullptr)
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
		if(creature->getZoneServer() == nullptr)
			return;

		ResourceManager* resMan = creature->getZoneServer()->getResourceManager();

		creature->sendSystemMessage(resMan->healthCheck());
	}

	void dumpResources(CreatureObject* creature, StringTokenizer* args) const {
		if(creature->getZoneServer() == nullptr)
			return;

		ResourceManager* resMan = creature->getZoneServer()->getResourceManager();

		creature->sendSystemMessage(resMan->dumpResources());
	}

	void despawnResource(CreatureObject* creature, StringTokenizer* args) const {
		if(creature->getZoneServer() == nullptr)
			return;

		String resourceName = "";
		if(args->hasMoreTokens())
			args->getStringToken(resourceName);


		ResourceManager* resMan = creature->getZoneServer()->getResourceManager();

		creature->sendSystemMessage(resMan->despawnResource(resourceName));
	}

	void listResourceInfo(CreatureObject* creature, StringTokenizer* args) const {
		if(creature->getZoneServer() == nullptr)
			return;

		String resourceName = "";
		if(args->hasMoreTokens())
			args->getStringToken(resourceName);

		ResourceManager* resMan = creature->getZoneServer()->getResourceManager();

		ManagedReference<ResourceSpawn*> spawn = resMan->getResourceSpawn(resourceName);
		if(spawn == nullptr) {
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
		if(creature->getZoneServer() == nullptr || !args->hasMoreTokens())
			throw Exception();

		ResourceManager* resMan = creature->getZoneServer()->getResourceManager();
		if (resMan == nullptr)
			throw Exception();

		String resourceType = "";
		args->getStringToken(resourceType);

		ResourceSpawner* resSpawner = resMan->getResourceSpawner();
		if (resSpawner == nullptr)
			throw Exception();

		ResourceMap* map = resSpawner->getResourceMap();
		if (map == nullptr)
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
		if(creature->getZoneServer() == nullptr || !args->hasMoreTokens())
			throw Exception();

		ResourceManager* resMan = creature->getZoneServer()->getResourceManager();
		if (resMan == nullptr)
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
