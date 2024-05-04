/*
 * ServerLootCommand.h
 *
 *  Created on: 11/09/2019
 *      Author: Smoki
 */

#ifndef SERVERLOOTCOMMAND_H_
#define SERVERLOOTCOMMAND_H_

#include <sstream>
#include <iomanip>

#include "templates/SharedTangibleObjectTemplate.h"
#include "server/zone/managers/loot/LootValues.h"
#include "server/zone/managers/loot/LootManager.h"
#include "server/zone/managers/loot/LootGroupMap.h"
#include "server/zone/objects/transaction/TransactionLog.h"
#include "server/zone/objects/player/sui/messagebox/SuiMessageBox.h"
#include "server/zone/managers/creature/CreatureTemplateManager.h"

class ServerLootCommand {
	const static int GENERALERROR = 0;
	const static int SUCCESS = 1;

public:
	static int executeCommand(CreatureObject* creature, uint64 target, const UnicodeString& arguments) {
		PlayerObject* ghost = creature->getPlayerObject().get();

		if (ghost == nullptr || ghost->getAdminLevel() < 15) {
			return GENERALERROR;
		}

		StringTokenizer tokenizer(arguments.toString().toLowerCase());
		StringBuffer systemMessage;

		String command = tokenizer.hasMoreTokens() ? tokenizer.getStringToken() : "";
		String args = tokenizer.hasMoreTokens() ? tokenizer.getRemainingString() : "";

		systemMessage
		<< "ServerLootCommand:" << endl
		<< endl;

		if (!command.isEmpty()) {
			systemMessage
			<< "--------------------------------" << endl
			<< "  Command:   " << command << endl
			<< "  Arguments: " << args << endl
			<< "--------------------------------" << endl;
		}

		TransactionLog trx(TrxCode::ADMINCOMMAND, creature);
		trx.addState("commandType", "ServerLootCommand::" + arguments.toString());

		if (command == "item") {
			systemMessage << testItem(trx, creature, args);
		} else if (command == "group") {
			systemMessage << testGroup(trx, creature, args);
		} else if (command == "search") {
			systemMessage << searchLoot(trx, creature, args);
		} else if (command == "agent") {
			systemMessage << agentLoot(trx, creature, args);
		} else {
			systemMessage << getSyntax();
		}

		sendSystemMessage(creature, systemMessage.toString());

		return SUCCESS;
	}

	static String createLoot(TransactionLog& trx, CreatureObject* creature, SceneObject* container, const String& lootName, int level = 0, float modifier = 0.f) {
		StringBuffer msg;

		auto zone = creature->getZone();

		if (zone == nullptr) {
			return "!zone";
		}

		auto zoneServer = creature->getZoneServer();

		if (zoneServer == nullptr)
			return "!zoneServer";

		auto lootManager = zoneServer->getLootManager();

		if (lootManager == nullptr) {
			return "!lootManager";
		}

		auto lootMap = lootManager->getLootMap();

		if (lootMap == nullptr) {
			return "!lootMap";
		}

		auto itemTemplate = lootMap->getLootItemTemplate(lootName);

		if (itemTemplate == nullptr) {
			return "!lootItem";
		}

		ManagedReference<TangibleObject*> prototype = nullptr;

		if (itemTemplate->isRandomResourceContainer()) {
			prototype = lootManager->createLootResource(lootName, zone->getZoneName());
		} else {
			prototype = lootManager->createLootObject(trx, itemTemplate, level, false);
		}

		if (prototype == nullptr) {
			return "!prototype";
		}

		Locker lock(prototype, creature);
		String craftersName = creature->getFirstName();
		uint64 craftersOID = creature->getObjectID();

		prototype->setCraftersName(craftersName);
		prototype->setCraftersID(craftersOID);

		if (modifier >= LootValues::EXPERIMENTAL) {
			auto lootValues = LootValues(itemTemplate, 0, 0);
			lootValues.setLevel(level);
			lootValues.setModifier(modifier);
			lootValues.recalculateValues(true);

			prototype->updateCraftingValues(&lootValues, true);

			if (lootValues.getDynamicValues() > 0 && !(prototype->getOptionsBitmask() & OptionBitmask::YELLOW)) {
				prototype->addMagicBit(false);
			}
#ifdef LOOTVALUES_DEBUG
			lootValues.debugAttributes(prototype, itemTemplate);
#endif // LOOTVALUES_DEBUG
		}

		if (container != nullptr && container->transferObject(prototype, -1, true, true)) {
			prototype->sendTo(creature, true);

			msg << "createLoot: name: " << lootName << " path: " << itemTemplate->getDirectObjectTemplate() << endl;
		} else {
			msg << prototype->getDisplayedName();

			prototype->destroyObjectFromWorld(true);
			prototype->destroyObjectFromDatabase(true);
		}

		return msg.toString();
	}

	static String testItem(TransactionLog& trx, CreatureObject* creature, const String& args, bool createItems = true) {
		StringBuffer msg;
		StringTokenizer tokenizer(args.toLowerCase());

		String lootTemplate = tokenizer.hasMoreTokens() ? tokenizer.getStringToken() : "";
		int level = tokenizer.hasMoreTokens() ? tokenizer.getIntToken() : 0;
		float modifier = tokenizer.hasMoreTokens() ? tokenizer.getIntToken() : 0.f;
		int count = tokenizer.hasMoreTokens() ? tokenizer.getIntToken() : 1;

		auto zoneServer = creature->getZoneServer();

		if (zoneServer == nullptr)
			return "!zoneServer";

		ManagedReference<SceneObject*> inventory = creature->getSlottedObject("inventory");

		if (inventory == nullptr) {
			return "!itemTemplate";
		}

		ManagedReference<SceneObject*> container = zoneServer->createObject(String::hashCode("object/tangible/container/drum/large_plain_crate_s01.iff"), 2);

		if (container == nullptr) {
			return "!container";
		}

		Locker cLock(container, creature);

		container->setCustomObjectName(lootTemplate + " cl:" + String::valueOf(level), false);

		if (inventory->transferObject(container, -1, false, true)) {
			container->sendTo(creature, true, false);

			for (int i = 0; count > i; ++i) {
				msg << createLoot(trx, creature, container, lootTemplate, level, modifier);
			}
		} else {
			container->destroyObjectFromDatabase(true);
		}

		return msg.toString();
	}

	static String testGroup(TransactionLog& trx, CreatureObject* creature, const String& args) {
		StringBuffer msg;
		StringTokenizer tokenizer(args.toLowerCase());

		String lootTemplate = tokenizer.hasMoreTokens() ? tokenizer.getStringToken() : 0;
		int level = tokenizer.hasMoreTokens() ? tokenizer.getIntToken() : 0;
		float modifier = tokenizer.hasMoreTokens() ? tokenizer.getIntToken() : 0.f;

		auto zoneServer = creature->getZoneServer();

		if (zoneServer == nullptr)
			return "!zoneServer";

		const auto lootManager = zoneServer->getLootManager();

		if (lootManager == nullptr) {
			return "!lootManager";
		}

		auto lootGroupMap = lootManager->getLootMap();

		if (lootGroupMap == nullptr) {
			return "!lootGroupMap";
		}

		auto lootGroup = lootGroupMap->getLootGroupTemplate(lootTemplate);

		if (lootGroup == nullptr) {
			return "!group";
		}

		ManagedReference<SceneObject*> inventory = creature->getSlottedObject("inventory");

		if (inventory == nullptr) {
			return "!inventory";
		}

		ManagedReference<SceneObject*> container = zoneServer->createObject(String::hashCode("object/tangible/container/drum/large_plain_crate_s01.iff"), 2);

		if (container == nullptr) {
			return "!container";
		}

		Locker cLock(container, creature);

		container->setCustomObjectName(lootTemplate + " cl:" + String::valueOf(level), false);

		if (inventory->transferObject(container, -1, false, true)) {
			container->sendTo(creature, true);

			String current, last = "first";

			for (int ii = 0; ii < 1000; ++ii) {
				int increment = ii * 10000;

				current = lootGroup->getLootGroupEntryForRoll(increment);

				if (current != last) {
					last = current;

					if (lootGroupMap->lootGroupExists(current)) {
						testGroup(trx, creature, current + " " + String::valueOf(level) + " " + String::valueOf(modifier));
					} else {
						msg << createLoot(trx, creature, container, current, level, modifier);
					}
				}
			}
		} else {
			container->destroyObjectFromDatabase(true);
		}

		return msg.toString();
	}

	static String searchLoot(TransactionLog& trx, CreatureObject* creature, const String& args) {
		StringBuffer msg;
		StringTokenizer tokenizer(args.toLowerCase());

		String searchString = tokenizer.hasMoreTokens() ? tokenizer.getStringToken() : "";
		int level = tokenizer.hasMoreTokens() ? tokenizer.getIntToken() : 0;
		float modifier = tokenizer.hasMoreTokens() ? tokenizer.getIntToken() : 0.f;

		auto zoneServer = creature->getZoneServer();

		if (zoneServer == nullptr)
			return "!zoneServer";

		auto lootManager = zoneServer->getLootManager();

		if (lootManager == nullptr) {
			return "!lootManager";
		}

		auto lootMap = lootManager->getLootMap();

		if (lootMap == nullptr) {
			return "!lootMap";
		}

		File file("scripts/loot/items.lua");
		FileReader reader(&file);
		Vector<String> fileIndex;

		if (file.exists()) {
			String entry;
			while (reader.readLine(entry)) {
				if (!entry.beginsWith("includeFile") || !entry.contains("\"")) {
					continue;
				}

				String path = entry.subString(entry.indexOf("\"") +1, entry.lastIndexOf("\""));
				fileIndex.add(path);
			}

			reader.close();
			file.close();
		}

		if (fileIndex.size() == 0) {
			return "!fileIndex.size()";
		}

		ManagedReference<SceneObject*> container = zoneServer->createObject(String::hashCode("object/tangible/container/drum/large_plain_crate_s01.iff"), 2);

		if (container == nullptr) {
			return "!container";
		}

		Locker cLock(container, creature);

		ManagedReference<SceneObject *> inventory = creature->getSlottedObject("inventory");

		if (inventory == nullptr) {
			return "!inventory";
		}

		ManagedReference<SceneObject*> subContainer = container;
		subContainer->setCustomObjectName(searchString + " cl:" + String::valueOf(level), false);

		String currentPath;

		if (inventory->transferObject(container, -1, false, true)) {
			container->sendTo(creature, true);
		} else {
			container->destroyObjectFromDatabase(true);
			return "!transferObject inventory container";
		}

		if (container == nullptr) {
			return msg.toString();
		}

		for (int i = 0; i < fileIndex.size(); ++i) {
			String index = fileIndex.get(i);
			if (!index.contains("/") || !index.contains(".")) {
				continue;
			}

			String path = index.subString(0, index.lastIndexOf("/"));
			String entryName = index.subString(index.lastIndexOf("/") + 1, index.lastIndexOf("."));

			auto itemTemplate = lootMap->getLootItemTemplate(entryName);

			if (itemTemplate == nullptr) {
				continue;
			}

			const auto& templatePath = itemTemplate->getDirectObjectTemplate();

			if (!index.contains(searchString) && !templatePath.contains(searchString)) {
				continue;
			}

			if (currentPath != path) {
				currentPath = path;

				subContainer = zoneServer->createObject(String::hashCode("object/tangible/container/drum/large_plain_crate_s01.iff"), 2);

				if (subContainer == nullptr) {
					break;
				}

				subContainer->setCustomObjectName(currentPath, false);

				if (container->transferObject(subContainer, -1, false, true)) {
					subContainer->sendTo(creature, true);
				} else {
					subContainer->destroyObjectFromDatabase(true);
					break;
				}
			}

			msg << createLoot(trx, creature, subContainer, entryName, level, modifier);
		}

		return msg.toString();
	}

	static String agentLoot(TransactionLog& trx, CreatureObject* creature, const String& args) {
		StringBuffer msg;
		StringTokenizer tokenizer(args.toLowerCase());

		String agentTemplateString = tokenizer.hasMoreTokens() ? tokenizer.getStringToken() : 0;
		int count = tokenizer.hasMoreTokens() ? tokenizer.getIntToken() : 1;

		CreatureTemplate* agentTemplate = CreatureTemplateManager::instance()->getTemplate(agentTemplateString.hashCode());

		if (agentTemplate == nullptr)
			return "!agentTemplate";

		auto zoneServer = creature->getZoneServer();

		if (zoneServer == nullptr)
			return "!zoneServer";

		const auto lootManager = zoneServer->getLootManager();

		if (lootManager == nullptr) {
			return "!lootManager";
		}

		auto lootMap = lootManager->getLootMap();

		if (lootMap == nullptr)
			return "!lootMap";

		auto lootCollection = agentTemplate->getLootGroups();

		if (lootCollection == nullptr)
			return "!lootCollection";

		if (lootCollection->count() == 0)
			return "!emptyLootCollection";

		int agentLevel = agentTemplate->getLevel();

		int legendaryCount = lootManager->getLegendaryLooted();
		int exceptionalCount = lootManager->getExceptionalLooted();
		int yellowCount = lootManager->getYellowLooted();

		int totalCollectionAttempts = 0;
		int totalFailedCollection = 0;

		int totalLootGroups = 0;
		int totalLootItems = 0;

		VectorMap<String, int> objectCount;
		StringBuffer itemMsg;

		for (int i = 0; i < count; ++i) {
			for (int j = 0; j < lootCollection->count(); ++j) {
				const LootGroupCollectionEntry* collectionEntry = lootCollection->get(j);
				int lootChance = collectionEntry->getLootChance();

				if (lootChance <= 0)
					continue;

				int roll = System::random(10000000);

				// If we roll above the collection chance, skip that collection
				if (roll > lootChance) {
					totalFailedCollection++;
					continue;
				}

				totalCollectionAttempts++;

				// Start at 0.
				int tempChance = 0;

				const LootGroups* lootGroups = collectionEntry->getLootGroups();

				if (totalLootGroups == 0)
					totalLootGroups = lootGroups->count();

				//Now we do the second roll to determine loot group.
				roll = System::random(10000000);

				//Select the loot group to use.
				for (int k = 0; k < lootGroups->count(); ++k) {
					const LootGroupEntry* groupEntry = lootGroups->get(k);

					tempChance += groupEntry->getLootChance();

					//Is this groupEntry lower than the roll? If yes, then we want to try the next groupEntry.
					if (tempChance < roll) {
						continue;
					}

					String lootEntry = groupEntry->getLootGroupName();
					String lootGroup = "";

					int depthMax = 32;
					int depth = 0;

					while (lootMap->lootGroupExists(lootEntry) && depthMax > depth++) {
						auto group = lootMap->getLootGroupTemplate(lootEntry);

						if (group != nullptr) {
							lootGroup = lootEntry;
							lootEntry = group->getLootGroupEntryForRoll(System::random(10000000));
						}
					}

					itemMsg << createLoot(trx, creature, nullptr, lootEntry, agentTemplate->getLevel());

					String itemName = itemMsg.toString();

					if (objectCount.contains(itemName)) {
						int dropCount = objectCount.get(itemName) + 1;

						objectCount.drop(itemName);
						objectCount.put(itemName, dropCount);
					} else {
						objectCount.put(itemName, 1);
					}

					itemMsg.deleteAll();

					totalLootItems++;

					break;
				}
			}
		}

		legendaryCount = lootManager->getLegendaryLooted() - legendaryCount;
		exceptionalCount = lootManager->getExceptionalLooted() - exceptionalCount;
		yellowCount = lootManager->getYellowLooted() - yellowCount;

		msg
		<< "AI Agent Template: " << agentTemplateString << endl
		<< "AI Agent Level: " << agentLevel << endl
		<< endl
		<< "Total Iterations: " << commas << count << endl
		<< endl
		<< "Agent Total Loot Collections: " << lootCollection->count() << endl
		<< "Agent Total Loot Groups: " << totalLootGroups << endl
		<< endl
		<< "Total Failed Collection Rolls: "<< totalFailedCollection << endl
		<< "Total Loot Collection Attempts: " << totalCollectionAttempts << endl
		<< "Total Dropped Loot Items: " << totalLootItems << endl
		<< endl
		<< "Total Legendaries Dropped: " << legendaryCount << "\t" << ((1.0f * legendaryCount) / totalLootItems) << "%" << endl
		<< "Total Expectionals Dropped: " << exceptionalCount << "\t" << ((1.0f * exceptionalCount) / totalLootItems) << "%" << endl
		<< "Total Yellow Named Dropped: " << yellowCount << "\t" << ((1.0f * yellowCount) / totalLootItems) << "%" << endl
		<< endl << endl
		<< "Items Dropped List:\n\n";

		std::stringstream title;
		title << "\t" << std::left << std::setw(20) << "Count" << "|" << std::setw(20) << "Percentage" << "|" << "\t" << "Item Name";
		msg << title.str() << "\n\n";

		for (int i = objectCount.size() - 1; i >= 0; i--) {
			std::stringstream newStream;

			int numDropped = objectCount.elementAt(i).getValue();
			String name = objectCount.elementAt(i).getKey();

			newStream << "\t" << std::left << std::setw(20) << numDropped << "|" << "\t" << std::setw(20) << (((float)numDropped / totalLootItems) * 100.00f) << "|" << "\t" << name.toCharArray();
			msg << newStream.str() << endl;

			objectCount.remove(i);
		}

		return msg.toString();
	}

	 static String getSyntax() {
		StringBuffer syntax;

		syntax
		<< endl
		<< "Note: Inputting a modifier of 0 will use the values determined by the LootManager." << endl
		<< endl
		<< "Command		Type 		Arguments" << endl
		<< "--------------------------------" << endl
		<< "item    -    Syntax:    /server loot item lootTemplate level modifier count" << endl
		<< endl
		<< "Spawn specific loot items." << endl
		<< endl
		<< "			String		lootTemplate" << endl
		<< "			int			level" << endl
		<< "			float		modifier" << endl
		<< "			int			count" << endl
		<< endl
		<< "example:	/server loot item rifle_t21 300 100 10" << endl
		<< endl
		<< "--------------------------------" << endl
		<< "group    -    Syntax:    /server loot group groupTemplate level modifier" << endl
		<< endl
		<< "Spawn specific loot group." << endl
		<< endl
		<< "			String		groupTemplate" << endl
		<< "			int			level" << endl
		<< "			float		modifier" << endl
		<< endl
		<< "example:	/server loot group weapons_all 300 10" << endl
		<< endl
		<< "--------------------------------" << endl
		<< "search    -    Syntax:    /server loot search itemName level modifier" << endl
		<< endl
		<< "Search for loot templates." << endl
		<< endl
		<< "			String		itemName" << endl
		<< "			int			level" << endl
		<< "			float		modifier" << endl
		<< endl
		<< "example:	/server loot search items 300 10" << endl
		<< endl
		<< "--------------------------------" << endl
		<< "agent    -    Syntax:    /server loot agentTemplate count" << endl
		<< endl
		<< "This will spawn the given agent's loot groups for the given amount of times, using that agents groups and level." << endl
		<< endl
		<< "			String		agentTemplate" << endl
		<< "			int			count" << endl
		<< endl
		<< "example:	/server loot agent nightsister_elder" << endl
		<< endl
		<< "--------------------------------" << endl
		<< endl;

		return syntax.toString();
	}

	static void sendSystemMessage(CreatureObject* creature, const String& systemMessage) {
		PlayerObject* ghost = creature->getPlayerObject().get();

		if (ghost) {
			auto box = new SuiMessageBox(creature, 0);

			box->setPromptTitle("Server Loot Command");
			box->setPromptText(systemMessage);

			ghost->addSuiBox(box);
			creature->sendMessage(box->generateMessage());
		}
	}
};

#endif /* SERVERLOOTCOMMAND_H_ */
