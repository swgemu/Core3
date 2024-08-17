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
#include "server/zone/objects/tangible/weapon/WeaponObject.h"

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

	static TangibleObject* createLootObject(TransactionLog& trx, CreatureObject* creature, const String& lootName, int level = 0, float modifier = 0.f) {
		auto zone = creature->getZone();

		if (zone == nullptr) {
			return nullptr;
		}

		auto zoneServer = creature->getZoneServer();

		if (zoneServer == nullptr)
			return nullptr;

		auto lootManager = zoneServer->getLootManager();

		if (lootManager == nullptr) {
			return nullptr;
		}

		auto lootMap = lootManager->getLootMap();

		if (lootMap == nullptr) {
			return nullptr;
		}

		auto itemTemplate = lootMap->getLootItemTemplate(lootName);

		if (itemTemplate == nullptr) {
			return nullptr;
		}

		ManagedReference<TangibleObject*> prototype = nullptr;

		if (itemTemplate->isRandomResourceContainer()) {
			prototype = lootManager->createLootResource(lootName, zone->getZoneName());
		} else {
			prototype = lootManager->createLootObject(trx, itemTemplate, level, false);
		}

		if (prototype == nullptr) {
			return nullptr;
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
		}

		return prototype;
	}

	static String testItem(TransactionLog& trx, CreatureObject* creature, const String& args, bool createItems = true) {
		StringBuffer msg;
		StringTokenizer tokenizer(args.toLowerCase());

		String lootTemplate = tokenizer.hasMoreTokens() ? tokenizer.getStringToken() : "";
		int level = tokenizer.hasMoreTokens() ? tokenizer.getIntToken() : 0;
		int count = tokenizer.hasMoreTokens() ? tokenizer.getIntToken() : 1;
		float modifier = tokenizer.hasMoreTokens() ? tokenizer.getIntToken() : 0.f;

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
		int level = tokenizer.hasMoreTokens() ? tokenizer.getIntToken() : 1;
		int count = tokenizer.hasMoreTokens() ? tokenizer.getIntToken() : 1;
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

		ManagedReference<SceneObject*> container = nullptr;

		for (int i = 0; i < count; ++i) {
			container = zoneServer->createObject(String::hashCode("object/tangible/container/drum/large_plain_crate_s01.iff"), 2);

			if (container == nullptr) {
				continue;
			}

			Locker cLock(container, creature);

			container->setCustomObjectName(lootTemplate + " cl:" + String::valueOf(level), false);

			if (inventory->transferObject(container, -1, false, true)) {
				container->sendTo(creature, true);

				String current, last = "first";

				for (int j = 0; j < 1000; ++j) {
					int increment = j * 10000;

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

			container = nullptr;
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

		uint32 legendaryCount = lootManager->getLegendaryLooted();
		uint32 exceptionalCount = lootManager->getExceptionalLooted();
		uint32 yellowCount = lootManager->getYellowLooted();

		uint32 totalCollectionAttempts = 0;
		uint32 totalFailedCollection = 0;

		uint32 totalLootGroups = 0;
		uint32 totalLootItems = 0;

		// Weapon Data
		uint32 weaponCount = 0;

		// DoTs on Weapons
		uint32 weaponWithDotCount = 0;

		uint32 fireDotTotal = 0;
		uint32 firePotency = 0;
		uint32 fireStrenth = 0;
		uint32 fireDuration = 0;
		uint32 fireUseCount = 0;

		uint32 poisonDotTotal = 0;
		uint32 poisonPotency = 0;
		uint32 poisonStrength = 0;
		uint32 poisonDuration = 0;
		uint32 poisonUseCount = 0;

		uint32 diseaseDotTotal = 0;
		uint32 diseasePotency = 0;
		uint32 diseaseStrength = 0;
		uint32 diseaseDuration = 0;
		uint32 diseaseUseCount = 0;

		uint32 bleedDotTotal = 0;
		uint32 bleedPotency = 0;
		uint32 bleedStrength = 0;
		uint32 bleedDuration = 0;
		uint32 bleedUseCount = 0;

		uint32 healthDot = 0;
		uint32 actionDot = 0;
		uint32 mindDot = 0;
		uint32 secondaryDot = 0;

		// Wearable Mods on Weapons
		uint32 weaponWithSkillModCount = 0;
		uint32 weaponOneMod = 0;
		uint32 weaponTwoMods = 0;
		uint32 weaponThreeMods = 0;
		uint32 skillModTotal = 0;
		uint32 skillModsValueTotal = 0;

		// Attachment Data
		uint32 totalAttachments = 0;
		uint32 attachmentModTotal = 0;
		uint32 attachmentTotalMods = 0;

		uint32 attachmentOneMod = 0;
		uint32 attachmentTwoMods = 0;
		uint32 attachmentThreeMods = 0;

		VectorMap<String, uint32> objectCount;
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

				ManagedReference<TangibleObject*> prototype = nullptr;

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

					prototype = createLootObject(trx, creature, lootEntry, agentTemplate->getLevel());

					if (prototype == nullptr) {
						itemMsg << "NULL LOOT ITEM";
					} else {
						Locker lock(prototype);

						itemMsg << prototype->getDisplayedName();

						// Collect Weapon Data
						if (prototype->isWeaponObject()) {
							weaponCount++;

							auto weaponLoot = cast<WeaponObject*>(prototype.get());

							if (weaponLoot != nullptr) {
								int numberOfDots = weaponLoot->getNumberOfDots();

								if (numberOfDots > 0) {
									weaponWithDotCount++;

									for (int ii = 0; ii < numberOfDots; ii++) {
										switch (weaponLoot->getDotType(ii)) {
										case 1:
											// "Poison";
											poisonDotTotal++;
											poisonPotency += weaponLoot->getDotPotency(ii);
											poisonStrength += weaponLoot->getDotStrength(ii);
											poisonDuration += weaponLoot->getDotDuration(ii);
											poisonUseCount += weaponLoot->getDotUses(ii);
											break;
										case 2:
											// "Disease";
											diseaseDotTotal++;
											diseasePotency += weaponLoot->getDotPotency(ii);
											diseaseStrength += weaponLoot->getDotStrength(ii);
											diseaseDuration += weaponLoot->getDotDuration(ii);
											diseaseUseCount += weaponLoot->getDotUses(ii);
											break;
										case 3:
											// "Fire";
											fireDotTotal++;
											firePotency += weaponLoot->getDotPotency(ii);
											fireStrenth += weaponLoot->getDotStrength(ii);
											fireDuration += weaponLoot->getDotDuration(ii);
											fireUseCount += weaponLoot->getDotUses(ii);
											break;
										case 4:
											// "Bleeding";
											bleedDotTotal++;
											bleedPotency += weaponLoot->getDotPotency(ii);
											bleedStrength += weaponLoot->getDotStrength(ii);
											bleedDuration += weaponLoot->getDotDuration(ii);
											bleedUseCount += weaponLoot->getDotUses(ii);
											break;
										default:
											break;
										}

										switch (weaponLoot->getDotAttribute(ii)) {
										case 0: // CreatureAttribute::HEALTH
											healthDot++;
											break;
										case 3: // CreatureAttribute::ACTION
											actionDot++;
											break;
										case 6: // CreatureAttribute::MIND
											mindDot++;
											break;
										default:
											secondaryDot++;
											break;
										}
									}
								}

								const VectorMap<String, int>* wearableSkillMods = weaponLoot->getWearableSkillMods();
								int totalSkillMods = wearableSkillMods->size();

								if (totalSkillMods > 0) {
									weaponWithSkillModCount++;

									if (totalSkillMods == 1) {
										weaponOneMod++;
									} else if (totalSkillMods == 2) {
										weaponTwoMods++;
									} else if (totalSkillMods == 3) {
										weaponThreeMods++;
									}

									for (int ii = 0; ii < totalSkillMods; ii++) {
										skillModTotal++;
										skillModsValueTotal += wearableSkillMods->elementAt(ii).getValue();
									}
								}
							}
						// Collect attachment data
						} else if (prototype->isAttachment()) {
							totalAttachments++;

							auto attachment = prototype.castTo<Attachment*>();

							if (attachment != nullptr) {
								const auto attachmentMods = attachment->getSkillMods();

								if (attachmentMods != nullptr) {
									int totalSkillMods = attachmentMods->size();

									for(int i = 0; i < totalSkillMods; ++i) {
										int value = attachmentMods->elementAt(i).getValue();
										attachmentModTotal += value;
										attachmentTotalMods++;
									}

									if (totalSkillMods == 1) {
										attachmentOneMod++;
									} else if (totalSkillMods == 2) {
										attachmentTwoMods++;
									} else if (totalSkillMods == 3) {
										attachmentThreeMods++;
									}
								}
							}
						}

						prototype->destroyObjectFromWorld(true);
						prototype->destroyObjectFromDatabase(true);
					}

					prototype = nullptr;

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
		<< "Total Legendaries Dropped: " << legendaryCount << "    " << (((1.0f * legendaryCount) / totalLootItems) * 100.f) << " percent " << endl
		<< "Total Exceptionals Dropped: " << exceptionalCount << "    " << (((1.0f * exceptionalCount) / totalLootItems) * 100.f) << " percent" << endl
		<< "Total Yellow Named Dropped: " << yellowCount << "    " << (((1.0f * yellowCount) / totalLootItems) * 100.f) << " percent" << endl << endl
		<< "Total Weapons Dropped: " << weaponCount << endl << endl;

		if (weaponCount > 0) {
			msg << "Total DoT Weapons: " << weaponWithDotCount << "    " << (((1.0f * weaponWithDotCount) / weaponCount) * 100.f) << " percent of Weapons looted" << endl << endl;

			if (weaponWithDotCount > 0) {
				msg << "Total Fire Dots: " << fireDotTotal << "    " << (((1.0f * fireDotTotal) / weaponWithDotCount) * 100.f) << " percent of DOT Weapons looted" << endl;

				if (fireDotTotal > 0) {
					msg
					<< "Average Fire Potency: " << (firePotency / fireDotTotal) << endl
					<< "Average Fire Strength: " << (fireStrenth / fireDotTotal) << endl
					<< "Average Fire Duration: " << (fireDuration / fireDotTotal) << endl
					<< "Average Fire Use Count: " << (fireUseCount / fireDotTotal) << endl;
				}

				msg << endl << "Total Poison Dots: " << poisonDotTotal << "    " << (((1.0f * poisonDotTotal) / weaponWithDotCount) * 100.f) << " percent of DOT Weapons looted" << endl;

				if (poisonDotTotal > 0) {
					msg
					<< "Average Poison Potency: " << (poisonPotency / poisonDotTotal) << endl
					<< "Average Poison Strength: " << (poisonStrength / poisonDotTotal) << endl
					<< "Average Poison Duration: " << (poisonDuration / poisonDotTotal) << endl
					<< "Average Poison Use Count: " << (poisonUseCount / poisonDotTotal) << endl;
				}

				msg << endl << "Total Disease Dots: " << diseaseDotTotal << "    " << (((1.0f * diseaseDotTotal) / weaponWithDotCount) * 100.f) << " percent of DOT Weapons looted" << endl;

				if (diseaseDotTotal > 0) {
					msg
					<< "Average Disease Potency: " << (diseasePotency / diseaseDotTotal) << endl
					<< "Average Disease Strength: " << (diseaseStrength / diseaseDotTotal) << endl
					<< "Average Disease Duration: " << (diseaseDuration / diseaseDotTotal) << endl
					<< "Average Disease Use Count: " << (diseaseUseCount / diseaseDotTotal) << endl;
				}

				msg << endl << "Total Bleed Dots: " << bleedDotTotal << "    " << (((1.0f * bleedDotTotal) / weaponWithDotCount) * 100.f) << " percent of DOT Weapons looted" << endl;

				if (bleedDotTotal > 0) {
					msg
					<< "Average Bleed Potency: " << (bleedPotency / bleedDotTotal) << endl
					<< "Average Bleed Strength: " << (bleedStrength / bleedDotTotal) << endl
					<< "Average Bleed Duration: " << (bleedDuration / bleedDotTotal) << endl
					<< "Average Bleed Use Count: " << (bleedUseCount / bleedDotTotal) << endl;
				}

				int attributesTotal = healthDot + actionDot + mindDot + secondaryDot;

				msg << endl
				<< "Health DOTs: " << healthDot << "    " << (((1.0f * healthDot) / attributesTotal) * 100.f) << " percent of DOT Attributes" << endl
				<< "Action DOTs: " << actionDot << "    " << (((1.0f * actionDot) / attributesTotal) * 100.f) << " percent of DOT Attributes" << endl
				<< "Mind DOTs: " << mindDot << "    " << (((1.0f * mindDot) / attributesTotal) * 100.f) << " percent of DOT Attributes" << endl
				<< "Secondary Attribute DOTs: " << secondaryDot << "    " << (((1.0f * secondaryDot) / attributesTotal) * 100.f) << " percent of DOT Attributes" << endl;
			}

			msg
			<< endl
			<< "Total Weapons with Skill Mods: " << weaponWithSkillModCount << "    " << (((1.0f * weaponWithSkillModCount) / weaponCount) * 100.f) << " percent of weapons looted" << endl;

			if (skillModTotal > 0) {
				msg << "Average Weapon Skill Mod Value: " << (skillModsValueTotal / skillModTotal) << endl;
			}

			msg
			<< "Weapon - One Skill Mod: " << weaponOneMod << "    " << (((1.0f * weaponOneMod) / weaponCount) * 100.f) << " percent of weapons looted" << endl
			<< "Weapon - Two Skill Mods: " << weaponTwoMods << "    " << (((1.0f * weaponTwoMods) / weaponCount) * 100.f) << " percent of weapons looted" << endl
			<< "Weapon - Three Skill Mods: " << weaponThreeMods << "    " << (((1.0f * weaponThreeMods) / weaponCount) * 100.f) << " percent of weapons looted" << endl << endl;
		}

		// Attachments
		msg << "Total Attachments Dropped: " << totalAttachments << endl;

		if (totalAttachments > 0) {
			msg
			<< "Average Attachment Skill Mod Value: " << (attachmentModTotal / attachmentTotalMods) << endl
			<< "Attachments - One Skill Mod: " << attachmentOneMod << "    " << (((1.0f * attachmentOneMod) / totalAttachments) * 100.f) << " percent of attachments looted" << endl
			<< "Attachments - Two Skill Mods: " << attachmentTwoMods << "    " << (((1.0f * attachmentTwoMods) / totalAttachments) * 100.f) << " percent of attachments looted" << endl
			<< "Attachments - Three Skill Mods: " << attachmentThreeMods << "    " << (((1.0f * attachmentThreeMods) / totalAttachments) * 100.f) << " percent of attachments looted" << endl << endl;
		}

		StringBuffer objectMsg;
		objectMsg << "Items Dropped List:" << endl << endl;

		std::stringstream title;
		title << "\t" << std::left << std::setw(20) << "Count" << "|" << "\t" << std::setw(20) << "Percentage" << "|" << "\t" << "Item Name" << endl << endl;
		objectMsg << title.str() << endl << endl;

		for (int i = objectCount.size() - 1; i >= 0; i--) {
			std::stringstream newStream;

			int numDropped = objectCount.elementAt(i).getValue();
			String name = objectCount.elementAt(i).getKey();

			newStream << "\t" << std::left << std::setw(20) << numDropped << "|" << "\t" << std::setw(20) << (((float)numDropped / totalLootItems) * 100.00f) << "|" << "\t" << name.toCharArray();
			objectMsg << newStream.str() << endl;

			objectCount.remove(i);
		}

		sendSystemMessage(creature, objectMsg.toString());

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
		<< "			int			count" << endl
		<< "			float		modifier" << endl
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
		<< "			int			count" << endl
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
