/*
 * ServerLootCommand.h
 *
 *  Created on: 11/09/2019
 *      Author: Smoki
 */

#ifndef SERVERLOOTCOMMAND_H_
#define SERVERLOOTCOMMAND_H_

#include "templates/SharedTangibleObjectTemplate.h"
#include "server/zone/managers/loot/LootValues.h"
#include "server/zone/managers/loot/LootManager.h"
#include "server/zone/managers/loot/LootGroupMap.h"
#include "server/zone/objects/transaction/TransactionLog.h"
#include "server/zone/objects/player/sui/messagebox/SuiMessageBox.h"

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
		<< "--------------------------------" << endl
		<< "  Command:   " << command << endl
		<< "  Arguments: " << args << endl
		<< "--------------------------------" << endl;

		TransactionLog trx(TrxCode::ADMINCOMMAND, creature);
		trx.addState("commandType", "ServerLootCommand::" + arguments.toString());

		if (command == "item") {
			systemMessage << item(trx, creature, args);
		} else if (command == "group") {
			systemMessage << group(trx, creature, args);
		} else if (command == "search") {
			systemMessage << search(trx, creature, args);
		} else {
			systemMessage << getSyntax();
		}

		sendSystemMessage(creature, systemMessage.toString());

		return SUCCESS;
	}

	static String createLoot(TransactionLog& trx, CreatureObject* creature, SceneObject* container, const String& lootName, int level = 0, float modifier = 0.f) {
		StringBuffer msg;

		auto lootManager = container->getZoneServer()->getLootManager();

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

		ManagedReference<TangibleObject*> prototype = lootManager->createLootObject(trx, itemTemplate, level, false);

		if (prototype == nullptr) {
			return "!prototype";
		}

		Locker lock(prototype, creature);
		String craftersName = creature->getFirstName();
		uint64 craftersOID = creature->getObjectID();

		prototype->setCraftersName(craftersName);
		prototype->setCraftersID(craftersOID);

		if (modifier >= 1.f) {
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

		if (container->transferObject(prototype, -1, true, true)) {
			prototype->sendTo(creature, true);
		} else {
			prototype->destroyObjectFromDatabase(true);
		}

		msg << "createLoot: name: " << lootName << " path: " << itemTemplate->getDirectObjectTemplate() << endl;

		return msg.toString();
	}

	static String item(TransactionLog& trx, CreatureObject* creature, const String& args) {
		StringBuffer msg;
		StringTokenizer tokenizer(args.toLowerCase());

		String lootTemplate = tokenizer.hasMoreTokens() ? tokenizer.getStringToken() : "";
		int level = tokenizer.hasMoreTokens() ? tokenizer.getIntToken() : 0;
		float modifier = tokenizer.hasMoreTokens() ? tokenizer.getIntToken() : 0.f;
		int count = tokenizer.hasMoreTokens() ? tokenizer.getIntToken() : 1;

		ManagedReference<SceneObject*> inventory = creature->getSlottedObject("inventory");

		if (inventory == nullptr) {
			return "!itemTemplate";
		}

		ManagedReference<SceneObject*> container = creature->getZoneServer()->createObject(String::hashCode("object/tangible/container/drum/large_plain_crate_s01.iff"), 2);

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

	static String group(TransactionLog& trx, CreatureObject* creature, const String& args) {
		StringBuffer msg;
		StringTokenizer tokenizer(args.toLowerCase());

		String lootTemplate = tokenizer.hasMoreTokens() ? tokenizer.getStringToken() : 0;
		int level = tokenizer.hasMoreTokens() ? tokenizer.getIntToken() : 0;
		float modifier = tokenizer.hasMoreTokens() ? tokenizer.getIntToken() : 0.f;

		const auto lootManager = creature->getZoneServer()->getLootManager();

		if (lootManager == nullptr) {
			return "!lootManager";
		}

		auto lootMap = lootManager->getLootMap();

		if (lootMap == nullptr) {
			return "!lootMap";
		}

		auto lootGroupMap = lootManager->getLootMap();

		if (lootGroupMap == nullptr) {
			return "!lootGroupMap";
		}

		auto lootGroup = lootManager->getLootMap()->getLootGroupTemplate(lootTemplate);

		if (lootGroup == nullptr) {
			return "!group";
		}

		ManagedReference<SceneObject*> inventory = creature->getSlottedObject("inventory");

		if (inventory == nullptr) {
			return "!inventory";
		}

		ManagedReference<SceneObject*> container = creature->getZoneServer()->createObject(String::hashCode("object/tangible/container/drum/large_plain_crate_s01.iff"), 2);

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
						group(trx, creature, current + " " + String::valueOf(level) + " " + String::valueOf(modifier));
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

	static String search(TransactionLog& trx, CreatureObject* creature, const String& args) {
		StringBuffer msg;
		StringTokenizer tokenizer(args.toLowerCase());

		String searchString = tokenizer.hasMoreTokens() ? tokenizer.getStringToken() : "";
		int level = tokenizer.hasMoreTokens() ? tokenizer.getIntToken() : 0;
		float modifier = tokenizer.hasMoreTokens() ? tokenizer.getIntToken() : 0.f;

		auto lootManager = creature->getZoneServer()->getLootManager();

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

		ManagedReference<SceneObject*> container = creature->getZoneServer()->createObject(String::hashCode("object/tangible/container/drum/large_plain_crate_s01.iff"), 2);

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
			String entry = index.subString(index.lastIndexOf("/") + 1, index.lastIndexOf("."));

			auto itemTemplate = lootMap->getLootItemTemplate(entry);

			if (itemTemplate == nullptr) {
				continue;
			}

			const auto& templatePath = itemTemplate->getDirectObjectTemplate();
			if (!index.contains(searchString) && !templatePath.contains(searchString)) {
				continue;
			}

			if (currentPath != path) {
				currentPath = path;

				subContainer = creature->getZoneServer()->createObject(String::hashCode("object/tangible/container/drum/large_plain_crate_s01.iff"), 2);
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

			msg << createLoot(trx, creature, subContainer, entry, level, modifier);
		}

		return msg.toString();
	}

	 static String getSyntax() {
		StringBuffer syntax;

		syntax
		<< "Command:	Type 		Arguments" << endl
		<< "--------------------------------" << endl
		<< "item" << endl
		<< "			String		lootTemplate" << endl
		<< "			int			level" << endl
		<< "			float		modifier" << endl
		<< "			int			count" << endl
		<< endl
		<< "example:	/server loot item rifle_t21 300 100 10" << endl
		<< "--------------------------------" << endl
		<< "group" << endl
		<< "			String		lootTemplate" << endl
		<< "			int			level" << endl
		<< "			float		modifier" << endl
		<< endl
		<< "example:	/server loot group weapons_all 300 10" << endl
		<< "--------------------------------" << endl
		<< "search" << endl
		<< "			String		lootTemplate" << endl
		<< "			int			level" << endl
		<< "			float		modifier" << endl
		<< endl
		<< "example:	/server loot search items 300 10" << endl
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
