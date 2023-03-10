/*
 * ServerLootCommand.h
 *
 *  Created on: 11/09/2019
 *      Author: Smoki
 */

#ifndef SERVERLOOTCOMMAND_H_
#define SERVERLOOTCOMMAND_H_

#include "engine/engine.h"
#include "templates/LootItemTemplate.h"
#include "server/chat/ChatManager.h"
#include "server/zone/objects/player/sui/messagebox/SuiMessageBox.h"

#include "templates/LuaTemplate.h"
#include "templates/crafting/AttributesMap.h"
#include "templates/manager/TemplateManager.h"
#include "templates/SharedTangibleObjectTemplate.h"

#include "server/zone/objects/transaction/TransactionLog.h"
#include "server/zone/managers/loot/LootManager.h"

#include "templates/LootItemTemplate.h"
#include "templates/LootGroupTemplate.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/managers/loot/LootGroupMap.h"

#include "templates/manager/DataArchiveStore.h"

class ServerLootCommand {

	const static int GENERALERROR = 0;
	const static int SUCCESS = 1;

public:

	static int executeCommand(CreatureObject* creature, uint64 target, const UnicodeString& arguments) {
		Reference<PlayerObject*> ghost = creature->getPlayerObject();
		if (ghost == nullptr || ghost->getAdminLevel() < 15) {
			return GENERALERROR;
		}

		StringTokenizer tokenizer(arguments.toString().toLowerCase());
		StringBuffer systemMessage;

		String command = tokenizer.hasMoreTokens() ? tokenizer.getStringToken() : "";
		String args = tokenizer.hasMoreTokens() ? tokenizer.getRemainingString() : "";

		systemMessage
		<< "Server Loot Command: Info:" << endl
		<< "Command: " << command << endl
		<< "Arguments: " << args << endl
		<< endl;

		if (command == "item") {
			systemMessage << item(creature, args);
		}

		else if (command == "group") {
			systemMessage << group(creature, args);
		}

		else if (command == "search") {
			systemMessage << search(creature, args);
		}

		else {
			systemMessage << getSyntax();
		}

		sendSystemMessage(creature, systemMessage.toString());

		return SUCCESS;
	}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	static String item(CreatureObject* creature, const String& args) {
		StringBuffer systemMessage;
		StringTokenizer tokenizer(args.toLowerCase());
		String lootTemplate = tokenizer.hasMoreTokens() ? tokenizer.getStringToken() : "";

		auto level = tokenizer.hasMoreTokens() ? tokenizer.getIntToken() : 0;
		auto count = tokenizer.hasMoreTokens() ? tokenizer.getIntToken() : 0;

		level = level > 300 ? 300 : level < 0 ? 0 : level;

		const auto lootManager = creature->getZoneServer()->getLootManager();
		if (lootManager == nullptr) {
			return "lootManager nullptr";
		}

		const auto lootMap = lootManager->getLootMap();
		if (lootMap == nullptr) {
			return "lootMap nullptr";
		}

		const LootItemTemplate* itemTemplate = lootMap->getLootItemTemplate(lootTemplate);
		if (itemTemplate == nullptr) {
			return "itemTemplate nullptr " + lootTemplate;
		}

		const auto inventory = creature->getSlottedObject("inventory");
		if (inventory == nullptr) {
			return "itemTemplate nullptr";
		}

		auto container = creature->getZoneServer()->createObject(STRING_HASHCODE( "object/tangible/container/drum/large_plain_crate_s01.iff"), 2);
		if (container == nullptr) {
			return "container nullptr";
		}

		container->setCustomObjectName(lootTemplate + " cl:" + String::valueOf(level), false);

		if (inventory->transferObject(container, -1, false, true)) {
			container->sendTo(creature, true, false);

			try {
				for (int i = 0; count > i; ++i) {
					ManagedReference<TangibleObject*> lootObject = lootManager->createLootObject(itemTemplate, level, false);
					if (lootObject == nullptr) {
						return "lootObject nullptr " + lootTemplate;
					}

					if (container->transferObject(lootObject, -1, false, true)) {
						lootObject->sendTo(creature, true, false);

						systemMessage << "template: " << lootTemplate << " level: " << level << " successfully created." << endl;
					} else {
						lootObject->destroyObjectFromDatabase(true);
					}
				}
			} catch (Exception &e) {
				e.what();
				e.printStackTrace();
			}

		} else {
			container->destroyObjectFromDatabase(true);
		}

		return systemMessage.toString();
	}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	static String group(CreatureObject* creature, const String& args) {
		StringBuffer systemMessage;
		StringTokenizer tokenizer(args.toLowerCase());
		String lootTemplate = tokenizer.hasMoreTokens() ? tokenizer.getStringToken() : 0;

		auto level = tokenizer.hasMoreTokens() ? tokenizer.getIntToken() : 0;
		auto count = tokenizer.hasMoreTokens() ? tokenizer.getIntToken() : 0;

		level = level > 300 ? 300 : level < 0 ? 0 : level;

		const auto lootManager = creature->getZoneServer()->getLootManager();
		if (lootManager == nullptr) {
			return "lootManager nullptr";
		}

		const auto lootMap = lootManager->getLootMap();
		if (lootMap == nullptr) {
			return "lootMap nullptr";
		}

		const auto lootGroupMap = lootManager->getLootMap();
		if (lootGroupMap == nullptr) {
			return "lootGroupMap nullptr";
		}

		const auto group = lootManager->getLootMap()->getLootGroupTemplate(lootTemplate);
		if (group == nullptr) {
			return "group nullptr";
		}

		const auto inventory = creature->getSlottedObject("inventory");
		if (inventory == nullptr) {
			return "inventory nullptr";
		}

		auto container = creature->getZoneServer()->createObject( STRING_HASHCODE("object/tangible/container/drum/large_plain_crate_s01.iff"), 2);
		if (container == nullptr) {
			return "container nullptr";
		}

		container->setCustomObjectName(lootTemplate + " cl:" + String::valueOf(level), false);

		if (inventory->transferObject(container, -1, false, true)) {
			container->sendTo(creature, true);

			for (int i = 0; i < count; ++i) {
				String current, last = "first";

				for (int ii = 0; ii < 1000; ++ii) {
					int increment = ii * 10000;

					current = group->getLootGroupEntryForRoll(increment);

					if (current != last) {
						last = current;

						const LootItemTemplate* itemTemplate = lootMap->getLootItemTemplate(current);
						if (itemTemplate == nullptr) {
							return "itemTemplate nullptr " + current;
						}

						ManagedReference<TangibleObject*> lootObject = lootManager->createLootObject(itemTemplate, level, false);
						if (lootObject == nullptr) {
							return "lootObject nullptr " + itemTemplate->getDirectObjectTemplate();
						}

						if (container->transferObject(lootObject, -1, false, true)) {
							container->broadcastObject(lootObject, true);

							systemMessage << "template: " << current << " level: " << level << " successfully created." << endl;
						} else {
							lootObject->destroyObjectFromDatabase(true);
						}
					}
				}
			}
		} else {
			container->destroyObjectFromDatabase(true);
		}

		return systemMessage.toString();
	}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		static String search(CreatureObject* creature, const String& args) {
			StringBuffer systemMessage;
			StringTokenizer tokenizer(args.toLowerCase());
			String lootTemplate = tokenizer.hasMoreTokens() ? tokenizer.getStringToken() : "";

			auto level = tokenizer.hasMoreTokens() ? tokenizer.getIntToken() : 1;

			level = level > 300 ? 300 : level < 1 ? 1 : level;

			LootManager* lootManager = creature->getZoneServer()->getLootManager();
			if (lootManager == nullptr) {
				return "lootManager nullptr";
			}

			const LootGroupMap* lootMap = lootManager->getLootMap();
			if (lootMap == nullptr) {
				return "lootMap nullptr";
			}

			File file("scripts/loot/items.lua");
			FileReader reader(&file);
			Vector<String> fileIndex;

			if (file.exists()) {
				String entry;
				while (reader.readLine(entry)) {
					if (!entry.beginsWith("includeFile")) {
						continue;
					}

					String path = entry.subString(entry.indexOf("\"") +1, entry.lastIndexOf("\""));
					fileIndex.add(path);
				}

				reader.close();
				file.close();
			}

			if (fileIndex.size() == 0) {
				return "No items found";
			}

			Reference<SceneObject*> container = creature->getZoneServer()->createObject(STRING_HASHCODE("object/tangible/container/drum/large_plain_crate_s01.iff"), 2);
			if (container == nullptr) {
				return "container nullptr";
			}

			Reference<SceneObject *> inventory = creature->getSlottedObject("inventory");
			if (inventory == nullptr) {
				return "inventory nullptr";
			}

			Reference<SceneObject*> subContainer = container;
			subContainer->setCustomObjectName(lootTemplate + " cl:" + String::valueOf(level), false);

			String currentPath;

			if (inventory->transferObject(container, -1, false, true)) {
				inventory->broadcastObject(container, true);
			} else {
				container->destroyObjectFromDatabase(true);
				systemMessage << " transfer failed " << endl;

				return systemMessage.toString();
			}

			if (container == nullptr) {
				systemMessage << " container nullptr " << endl;
				return systemMessage.toString();
			}

			for (int x = 0; x < fileIndex.size(); ++x) {
				String index = fileIndex.get(x);
				if (!index.contains("/") || !index.contains(".")) {
					continue;
				}

				String path = index.subString(0, index.lastIndexOf("/"));
				String entry = index.subString(index.lastIndexOf("/") + 1, index.lastIndexOf("."));

				bool match = lootTemplate == "all" || index.contains(lootTemplate);
				if (!match) {
					continue;
				}

				if (currentPath != path) {
					currentPath = path;

					subContainer = creature->getZoneServer()->createObject(STRING_HASHCODE("object/tangible/container/drum/large_plain_crate_s01.iff"), 2);

					if (subContainer) {
						subContainer->setCustomObjectName(currentPath, false);

						if (container->transferObject(subContainer, -1, false, true)) {
							container->broadcastObject(subContainer, true);
						} else {
							subContainer->destroyObjectFromDatabase(true);
							break;
						}
					}
				}

				Reference<const LootItemTemplate*> itemTemplate = lootMap->getLootItemTemplate(entry);
				if (itemTemplate == nullptr) {
					systemMessage << " itemTemplate nullptr " << entry << endl;
					continue;
				}

				ManagedReference<TangibleObject*> lootObject = lootManager->createLootObject(itemTemplate, level, false);
				if (lootObject == nullptr) {
					systemMessage << " lootObject nullptr " << endl;
					continue;
				}

				if (subContainer->transferObject(lootObject, -1, false, true)) {
					subContainer->broadcastObject(lootObject, true);

					systemMessage << "template: " << entry << " level: " << level << " successfully created." << endl;
				} else {
					lootObject->destroyObjectFromDatabase(true);
				}
			}

			return systemMessage.toString();
		}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	 static String getSyntax() {
		StringBuffer syntax;

		syntax
		<< "SubCommands:" << endl
		<< "	item: /server loot item lootItemTemplate level(0,300) quantity(0,100)" << endl
		<< "	example: /server loot item rifle_t21 300 100 1" << endl
		<< endl
		<< "	group: /server loot group lootItemTemplate level(0,300)" << endl
		<< "	example: /server loot group weapons_all 300 1" << endl
		<< endl
		<< "	search: /server loot search string level(0,300)" << endl
		<< "	example: /server loot search weapon 300 1" << endl
		<< endl;

		return syntax.toString();
	}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	static void sendSystemMessage(CreatureObject* creature, const String& systemMessage) {
		Reference<PlayerObject*> ghost = creature->getPlayerObject();

		if (ghost) {
			auto box = new SuiMessageBox(creature, 0);

			box->setPromptTitle("Server Loot Command");
			box->setPromptText(systemMessage);

			ghost->addSuiBox(box);
			creature->sendMessage(box->generateMessage());
		}
	}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

};

#endif /* SERVERLOOTCOMMAND_H_ */
