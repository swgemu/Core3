/*
 * ServerLootCommand.h
 *
 *  Created on: 14/08/2019
 *      Author: smoki
 */

#ifndef SERVERLOOTCOMMAND_H_
#define SERVERLOOTCOMMAND_H_

#include "engine/engine.h"
#include "templates/LootItemTemplate.h"
#include "server/zone/objects/player/sui/messagebox/SuiMessageBox.h"

class ServerLootCommand {

public:

	static int executeCommand(CreatureObject* creature, uint64 target, const UnicodeString& arguments) {

		PlayerObject* ghost = creature->getPlayerObject();

		if (ghost == nullptr || ghost->getAdminLevel() < 15)
			return 1;

		StringTokenizer tokenizer(arguments.toString());
		StringBuffer systemMessage;

		if (tokenizer.hasMoreTokens()) {
			try {
				String commandType;

				bool correctSyntax = true;
				tokenizer.getStringToken(commandType);

				LootManager* lootManager = creature->getZoneServer()->getLootManager();

//				+-------------------------------------------------------------------------------------------------------------------------------------------------------+

					if (commandType.beginsWith("resetlog")) {


					File* file = new File("log/loot/lootLog.tsv");
					FileWriter* fileWriter  = new FileWriter(file, false);
					StringBuffer headerBuffer;

					headerBuffer << "string"
								 << "	" << "string"
								 << "	" << "float "
								 << "	" << "float "
								 << "	" << "float "
								 << "	" << "float   "
								 << endl;

					fileWriter->write(headerBuffer.toString().toCharArray());

					fileWriter->close();
					file->close();

					systemMessage << "lootLog.tsv has been successfully reset.";

//				+-------------------------------------------------------------------------------------------------------------------------------------------------------+

				} else if (commandType.beginsWith("displaylog")) {

					StringBuffer readBuffer;

					systemMessage << "legendary Items Looted   = " << String::valueOf(lootManager->getLegendaryLooted()) << endl
								  << "exceptional Items Looted = " << String::valueOf(lootManager->getExceptionalLooted()) << endl
								  << "yellow Items Looted      = " << String::valueOf(lootManager->getYellowLooted()) << endl << endl;

					File file("log/loot/lootLog.tsv");
					FileReader fileReader(&file);

					if (file.exists()) {

						String line;
						while (fileReader.readLine(line))
							readBuffer << line.toCharArray();

						if (readBuffer.length() > 16384) {
							readBuffer.deleteRange(0, readBuffer.length() - 16384);
							systemMessage << "warning: log/loot/lootLog.tsv length exceeds buffer limit and can not be displayed fully." << endl << endl;
						}

						systemMessage << readBuffer.toString().toCharArray();
					}

//				+-------------------------------------------------------------------------------------------------------------------------------------------------------+

				} else if (commandType.beginsWith("version")) {

					int value = 0;

					if (tokenizer.hasMoreTokens())
						value = tokenizer.getIntToken();

					if (value == 0) {
						systemMessage << "loot refactor deactivated.";
					} else if (value == 1) {
						systemMessage << "loot refactor activated.";
					} else {
						systemMessage << "specify a valid lootVersion value, 1/0 object calculation refactor/original.";
						correctSyntax = false;
					}

					if (correctSyntax)
						lootManager->setLootVersion(value);

//				+-------------------------------------------------------------------------------------------------------------------------------------------------------+

				} else if (commandType.beginsWith("modifier") || commandType.beginsWith("chance")) {

					float leg = -1, exc = -1, yel = -1;

					if (tokenizer.hasMoreTokens())
						leg = tokenizer.getFloatToken();

					if (tokenizer.hasMoreTokens())
						exc = tokenizer.getFloatToken();

					if (tokenizer.hasMoreTokens())
						yel = tokenizer.getFloatToken();

					if (leg < 0 || exc < 0 || yel < 0) {
						systemMessage << "specify valid values for legendary, exceptional, yellow.";
						correctSyntax = false;
					}

					if (correctSyntax && commandType.beginsWith("modifier")) {
						if (leg > 10)
							leg = 10;

						if (exc > 10)
							exc = 10;

						if (yel > 10)
							yel = 10;

						systemMessage << "global loot modifiers set" << endl
									  << "legendary = " << String::valueOf(leg) << endl
									  << "exceptional = " << String::valueOf(exc) << endl
									  << "yellow = " << String::valueOf(yel);

						lootManager->setLootModifier(leg, exc, yel);

					} else if (correctSyntax && commandType.beginsWith("chance")) {
						systemMessage << "global loot chance set" << endl
									  << "legendary = " << String::valueOf(leg) << endl
									  << "exceptional = " << String::valueOf(exc) << endl
									  << "yellow = " << String::valueOf(yel);

						lootManager->setLootChance(leg, exc, yel);
					}

//				+-------------------------------------------------------------------------------------------------------------------------------------------------------+

				} else if (commandType.beginsWith("item")) {
					String lootTemplate, compareLog;
					int level = -1;

					if (tokenizer.hasMoreTokens())
						tokenizer.getStringToken(lootTemplate);

					if (tokenizer.hasMoreTokens()) {
						level = tokenizer.getIntToken();

						if (level < 1 || level > 300) {
							correctSyntax = false;
							systemMessage << "level not valid.";
						}
					}

					int count = -1;

					if (tokenizer.hasMoreTokens()) {
						count = tokenizer.getIntToken();

						if (count < 1 || count > 100) {
							correctSyntax = false;
							systemMessage << "quantity not valid.";
						}

					} else {
						systemMessage << "specify a valid item template,level and quantity.";
						correctSyntax = false;
					}

					if (correctSyntax) {
						if (tokenizer.hasMoreTokens())
							compareLog = tokenizer.getRemainingString();

						bool logLoot = compareLog.contains("log");
						bool compareLoot = compareLog.contains("compare");

						Reference<const LootItemTemplate*> itemTemplate = lootManager->getLootMap()->getLootItemTemplate(lootTemplate);

						if (itemTemplate != nullptr) {
							ManagedReference<SceneObject*> container = creature->getSlottedObject("inventory");

							if (count > 1 || compareLoot) {
								container = creature->getZoneServer()->createObject(STRING_HASHCODE("object/tangible/container/drum/large_plain_crate_s01.iff"), 2);
								container->setCustomObjectName(lootTemplate + " level: " + String::valueOf(level), false);

								if (count > 100)
									count = 100;
							}

							if (container != nullptr) {
								int lootVersion = lootManager->getLootVersion();

								for (int i = 0; count > i; ++i) {
									ManagedReference<TangibleObject*> obj = nullptr;
									ManagedReference<TangibleObject*> ref = nullptr;

									if (compareLoot || lootVersion == 0)
										obj = lootManager->createLootObject(itemTemplate, level, false, logLoot);

									if (obj != nullptr) {
										obj->setCustomObjectName(obj->getDisplayedName() + " (old)", false);

										systemMessage << "template: " << obj->getDisplayedName() << " successfully generated." << endl;

										if (container->transferObject(obj, -1, false, true)) {
											container->broadcastObject(obj, true);
										} else {
											obj->destroyObjectFromDatabase(true);
										}
									}

									if (compareLoot || lootVersion == 1)
										ref = lootManager->createNewLootObject(itemTemplate, level, false, logLoot);

									if (ref != nullptr) {
										ref->setCustomObjectName(ref->getDisplayedName() + " (new)", false);

										systemMessage << "template: " << ref->getDisplayedName() << " successfully generated." << endl;

										if (container->transferObject(ref, -1, false, true)) {
											container->broadcastObject(ref, true);
										} else {
											ref->destroyObjectFromDatabase(true);
										}
									}
								}

								if (count > 1 || compareLoot) {
									if (creature->getSlottedObject("inventory")->transferObject(container, -1, false, true)) {
										creature->getSlottedObject("inventory")->broadcastObject(container, true);
									}
								}
							}
						} else {
							systemMessage << lootTemplate << " is not recognized as a valid item template.";
						}
					}

//				+-------------------------------------------------------------------------------------------------------------------------------------------------------+

				} else if (commandType.beginsWith("group")) {
					String lootGroup, compareLog;
					int level = -1;

					if (tokenizer.hasMoreTokens())
						tokenizer.getStringToken(lootGroup);

					if (tokenizer.hasMoreTokens()) {
						level = tokenizer.getIntToken();

						if (level < 1 || level > 300) {
							correctSyntax = false;
							systemMessage << "level not valid.";
						}
					} else {
						systemMessage << "specify a valid group template and level.";
						correctSyntax = false;
					}

					if (correctSyntax) {
						if (tokenizer.hasMoreTokens())
							compareLog = tokenizer.getRemainingString();

						bool logLoot = compareLog.contains("log");
						bool compareLoot = compareLog.contains("compare");

						Reference<const LootGroupMap*> lootGroupMap = lootManager->getLootMap();
						Reference<const LootGroupTemplate*> group = lootGroupMap->getLootGroupTemplate(lootGroup);

						if (group != nullptr) {
							String current;
							String last;

							last = "first";
							current = "first";

							ManagedReference<SceneObject*> drumSceno = creature->getZoneServer()->createObject(STRING_HASHCODE("object/tangible/container/drum/large_plain_crate_s01.iff"), 2);

							if (drumSceno != nullptr) {
								drumSceno->setCustomObjectName(lootGroup + " level: " + String::valueOf(level), false);
								int lootVersion = lootManager->getLootVersion();

								systemMessage << "	" << "LootGroup:"
											  << "	" << lootGroup
											  << "	"  << "level:"
											  << "	" << level
											  << endl;

								for (int i = 1; i < 1001; ++i) {
									int increment = i * 10000;

									if (increment == 10000000)
										increment = 0;

									current = group->getLootGroupEntryForRoll(increment);

									if (last == "first")
										last = current;

									if (current == last)
										continue;

									Reference<const LootItemTemplate*> itemTemplate = lootGroupMap->getLootItemTemplate(current);

									last = current;

									if (itemTemplate == nullptr)
										continue;

									ManagedReference<TangibleObject*> obj = nullptr;
									ManagedReference<TangibleObject*> ref = nullptr;

									if (compareLoot || lootVersion == 0)
										obj = lootManager->createLootObject(itemTemplate, level, false, logLoot);

									if (obj != nullptr) {
										obj->setCustomObjectName(obj->getDisplayedName() + " (old)", false);

										systemMessage << "template: " << obj->getDisplayedName() << " successfully generated." << endl;

										if (drumSceno->transferObject(obj, -1, false, true)) {
											drumSceno->broadcastObject(obj, true);
										} else {
											obj->destroyObjectFromDatabase(true);
										}
									}

									if (compareLoot || lootVersion == 1)
										ref = lootManager->createNewLootObject(itemTemplate, level, false, logLoot);

									if (ref != nullptr) {
										ref->setCustomObjectName(ref->getDisplayedName() + " (new)", false);

										systemMessage << "template: " << ref->getDisplayedName() << " successfully generated." << endl;

										if (drumSceno->transferObject(ref, -1, false, true)) {
											drumSceno->broadcastObject(ref, true);
										} else {
											ref->destroyObjectFromDatabase(true);
										}
									}
								}

								if (creature->getSlottedObject("inventory")->transferObject(drumSceno, -1, false, true)) {
										creature->getSlottedObject("inventory")->broadcastObject(drumSceno, true);
								} else {
										drumSceno->destroyObjectFromDatabase(true);
								}
							}
						} else {
							systemMessage << group << " is not recognized as a valid group template.";
						}
					}

//				+-------------------------------------------------------------------------------------------------------------------------------------------------------+

				} else if (commandType.beginsWith("all")) {
					int level = -1;
					String category, compareLog;

					if (tokenizer.hasMoreTokens())
						tokenizer.getStringToken(category);

					if (tokenizer.hasMoreTokens()) {
						level = tokenizer.getIntToken();

						if (level < 1 || level > 300) {
							correctSyntax = false;
							systemMessage << "level not valid.";
						}
					} else {
						systemMessage << "specify a valid directory and level.";
						correctSyntax = false;
					}

					if (correctSyntax) {
						if (tokenizer.hasMoreTokens())
							compareLog = tokenizer.getRemainingString();

						bool logLoot = compareLog.contains("log");
						bool compareLoot = compareLog.contains("compare");

						File file("scripts/loot/items.lua");
						FileReader reader(&file);

						if (file.exists()) {
							String line;

							Reference<const LootGroupMap*> lootGroupMap = lootManager->getLootMap();
							ZoneServer* zoneServer = creature->getZoneServer();
							ManagedReference<SceneObject*> drumSceno = zoneServer->createObject(STRING_HASHCODE("object/tangible/container/drum/large_plain_crate_s01.iff"), 2);

							if (drumSceno != nullptr) {
								StringBuffer readBuffer;
								String current = "first";
								String last = "first";

								creature->sendSystemMessage("server loot command info: generating loot items.");

								int lootVersion = lootManager->getLootVersion();

								while (reader.readLine(line)) {
									if (line.beginsWith("includeFile") == false)
										continue;

									current = line.subString(line.indexOf("(") + 2, line.lastIndexOf("/"));

									if (current.contains(category) == false)
										continue;

									if (last == "first") {
										last = current;
										drumSceno->setCustomObjectName(current + " level: " + String::valueOf(level), false);
									}

									if (last != current) {
										last = current;

									if (creature->getSlottedObject("inventory")->transferObject(drumSceno, -1, false, true)) {
										creature->getSlottedObject("inventory")->broadcastObject(drumSceno, true);
									} else {
										drumSceno->destroyObjectFromDatabase(true);
									}

									drumSceno = zoneServer->createObject(STRING_HASHCODE("object/tangible/container/drum/large_plain_crate_s01.iff"), 2);

									if (drumSceno != nullptr) {
										drumSceno->setCustomObjectName(current + " level: " + String::valueOf(level), false);
									} else {
										break;
										}
									}

									readBuffer << line.subString(line.lastIndexOf("/") + 1, line.lastIndexOf(".")).toCharArray();

									Reference<const LootItemTemplate*> itemTemplate = lootGroupMap->getLootItemTemplate(readBuffer.toString());

									if (itemTemplate == nullptr)
									continue;

									ManagedReference<TangibleObject*> obj = nullptr;
									ManagedReference<TangibleObject*> ref = nullptr;

									if (compareLoot || lootVersion == 0)
										obj = lootManager->createLootObject(itemTemplate, level, false, logLoot);

									if (obj != nullptr) {
										obj->setCustomObjectName(obj->getDisplayedName() + " (old)", false);

										systemMessage << "template: " << obj->getDisplayedName() << " successfully generated." << endl;
										readBuffer.deleteAll();

										if (drumSceno->transferObject(obj, -1, false, true)) {
											drumSceno->broadcastObject(obj, true);
										} else {
											obj->destroyObjectFromDatabase(true);
										}
									}

									if (compareLoot || lootVersion == 1)
										ref = lootManager->createNewLootObject(itemTemplate, level, false, logLoot);

									if (ref != nullptr) {
										ref->setCustomObjectName(ref->getDisplayedName() + " (new)", false);

										systemMessage << "template: " << ref->getDisplayedName() << " successfully generated." << endl;

										if (drumSceno->transferObject(ref, -1, false, true)) {
											drumSceno->broadcastObject(ref, true);
										} else {
											ref->destroyObjectFromDatabase(true);
										}
									}
								}

								if (drumSceno->getContainedObjectsRecursive() == 0) {
									drumSceno->destroyObjectFromDatabase(false);
									systemMessage << "no directory matches for search: " << category << endl;
								} else if (creature->getSlottedObject("inventory")->transferObject(drumSceno, -1, false, true)) {
									creature->getSlottedObject("inventory")->broadcastObject(drumSceno, true);
								} else {
									drumSceno->destroyObjectFromDatabase(true);
								}

								reader.close();
								file.close();
							}
						}
					}

//				+-------------------------------------------------------------------------------------------------------------------------------------------------------+

				} else if (commandType.beginsWith("checktemplates")) {
					File file("scripts/loot/items.lua");
					FileReader reader(&file);

					Vector<String> templateVector;
					Reference<const LootGroupMap*> lootGroupMap = lootManager->getLootMap();

					if (file.exists()) {
						String line;

						while (reader.readLine(line)) {
							if (line.beginsWith("includeFile") == true) {
								templateVector.add(line.subString(line.lastIndexOf("/") + 1, line.lastIndexOf(".")));
							}
						}

						reader.close();
						file.close();

						systemMessage << "template "
									  << "	" << "error    "
									  << "	" << "subtitle "
									  << "	" << "string   "
									  << "	" << "float    "
									  << "	" << "string   "
									  << "	" << "float    "
									  << endl ;
					}

					for (int i = 0; templateVector.size() > i; ++i) {
						const LootItemTemplate* itemTemplate = lootGroupMap->getLootItemTemplate(templateVector.get(i));

						if (itemTemplate == nullptr)
							continue;

						ZoneServer* zoneServer = creature->getZone()->getZoneServer();
						ManagedReference<TangibleObject*> prototype = zoneServer->createObject(itemTemplate->getDirectObjectTemplate().hashCode(), 0)->asTangibleObject();

						if (prototype == nullptr)
							continue;

						ValuesMap valuesMap = itemTemplate->getValuesMapCopy();
						CraftingValues* craftingValues = new CraftingValues(valuesMap);

						StringBuffer templateBuffer;
						bool templateError = false;

						for (int j = 0; j < craftingValues->getExperimentalPropertySubtitleSize(); ++j) {
							const String& subtitle = craftingValues->getExperimentalPropertySubtitle(j);

							float min = craftingValues->getMinValue(subtitle);
							float max = craftingValues->getMaxValue(subtitle);
							float prc = craftingValues->getPrecision(subtitle);

							if (!prototype->isComponent() && subtitle == "hitpoints") {
								templateBuffer << "	" << "hitpoints while not a component:"
											   << "	" << subtitle
											   << "	" << "min:"
											   << "	" << min
											   << "	" << "max:"
											   << "	" << max
											   << endl;
								templateError = true;
							}

							if (itemTemplate->getMaximumLevel() != itemTemplate->getMinimumLevel() && min == max) {
								if (subtitle == "color"
								 || subtitle == "skillmodmin"
								 || subtitle == "armor_rating"
								 || subtitle == "armor_integrity"
								 || subtitle == "midrange"
								 || subtitle == "maxrange")
									continue;

								templateBuffer << "	" << "static value dynamic template:"
											   << "	" << subtitle
											   << "	" << "min:"
											   << "	" << min
											   << "	" << "max:"
											   << "	" << max
											   << endl;
								templateError = true;
							}

							if (itemTemplate->getMaximumLevel() == itemTemplate->getMinimumLevel() && min != max) {
								if (subtitle == "useCount")
									continue;

								templateBuffer << "	" << "dynamic value static template:"
											   << "	" << subtitle
											   << "	" << "min:"
											   << "	" << min
											   << "	" << "max:"
											   << "	" << max
											   << endl;
								templateError = true;
							}

							if ((subtitle == "armor_effectiveness"
							  || subtitle == "acideffectiveness"
							  || subtitle == "blasteffectiveness"
							  || subtitle == "coldeffectiveness"
							  || subtitle == "energyeffectiveness"
							  || subtitle == "heateffectiveness"
							  || subtitle == "kineticeffectiveness") && prc != 10) {
								templateBuffer << "	" << "precision:"
											   << "	" << subtitle
											   << "	" << "currently:"
											   << "	" << prc
											   << "	" << "should be:"
											   << "	" << 10
											   << endl;
								templateError = true;
							}

							if ((subtitle == "woundchance"
							  || subtitle == "attackspeed") && prc != 1) {
								templateBuffer << "	" << "precision:"
											   << "	" << subtitle
											   << "	" << "currently:"
											   << "	" << prc
											   << "	" << "should be:"
											   << "	" << 1
											   << endl;
								templateError = true;
							}

							if ((subtitle == "armor_action_encumbrance"	|| subtitle == "armor_health_encumbrance"	|| subtitle == "armor_integrity"
							  || subtitle == "armor_mind_encumbrance"	|| subtitle == "armor_rating"				|| subtitle == "armor_special_effectiveness"
							  || subtitle == "armor_special_integrity"	|| subtitle == "armor_special_type"

							  || subtitle == "flavor"					|| subtitle == "filling"					|| subtitle == "quantity_bonus"
							  || subtitle == "quality"					|| subtitle == "nutrition"					|| subtitle == "stomach"

							  || subtitle == "attackactioncost"			|| subtitle == "attackhealthcost"			|| subtitle == "attackmindcost"
							  || subtitle == "maxdamage"				|| subtitle == "mindamage"					|| subtitle == "midrange"
							  || subtitle == "maxrange"					|| subtitle == "hit_points"					|| subtitle == "hitpoints"
							  || subtitle == "roundsused"				|| subtitle == "midrangemod"				|| subtitle == "zerorangemod"
							  || subtitle == "maxrangemod"				|| subtitle == "minrangemod"

							  || subtitle == "potency"					|| subtitle == "power"						|| subtitle == "quantity"
							  || subtitle == "range"					|| subtitle == "sockets"					|| subtitle == "charges"
							  || subtitle == "useCount"					|| subtitle == "usemodifier"				|| subtitle == "color"
							  || subtitle == "area") && prc != 0) {
								templateBuffer << "	" << "precision:"
											   << "	" << subtitle
											   << "	" << "currently:"
											   << "	" << prc
											   << "	" << "should be:"
											   << "	" << 0
											   << endl;
								templateError = true;
							}
						}

						if (templateError)
							systemMessage << templateVector.get(i) << templateBuffer;

						delete craftingValues;
						prototype->destroyObjectFromDatabase(true);

					}

					if (systemMessage.length() > 0) {
						File* templateErrorFile = new File("log/loot/lootTemplateDebug.tsv");
						FileWriter* fileWriter = new FileWriter(templateErrorFile, false);

						fileWriter->write(systemMessage.toString().toCharArray());

						fileWriter->close();
						templateErrorFile->close();
					} else {
						if (templateVector.size() > 0) {
							systemMessage << "server loot command info: no template errors detected. ";
						} else {
							systemMessage << "server loot command error: file read error, vector empty. ";
						}
					}

//				+-------------------------------------------------------------------------------------------------------------------------------------------------------+

				} else {
					systemMessage << " server loot command error: incomplete arguments.";
					sendSyntax(creature);
					return 1;
				}

				if (systemMessage.length() == 0)
					return 1;

				ManagedReference<SuiMessageBox*> box = new SuiMessageBox(creature, 0);

				box->setPromptTitle("Server Loot Implementation");
				box->setPromptText(systemMessage.toString());

				ghost->addSuiBox(box);

				creature->sendSystemMessage(" server loot command info:" + commandType + " sub-command complete.");
				creature->sendMessage(box->generateMessage());

				if (!correctSyntax) {
					sendSyntax(creature);
					return 1;
				}

			} catch (Exception& e) {

				systemMessage << " server loot command critical error: exception caught " << e.getMessage();
				creature->sendSystemMessage(systemMessage.toString());
				e.printStackTrace();
			}
		}
		return 0;
	}

	 static void sendSyntax(CreatureObject* player) {
		if (player != nullptr) {
			StringBuffer syntax;
			syntax  << "Syntax: /server loot version (<int>): 1/0 refactored/original." << endl
					<< "Syntax: /server loot modifier (<float> <float> <float>): legendary, exceptional, yellow." << endl
					<< "Syntax: /server loot chance (<int> <int> <int>): legendary, exceptional, yellow." << endl
					<< "Syntax: /server loot all (<string> <int>): category, level. (optional: <string> <string>: compare, log)" << endl
					<< "Syntax: /server loot item (<string> <int> <int>): lootItemTemplate, level, quantity (optional: <string> <string>: compare, log)" << endl
					<< "Syntax: /server loot group (<string> <int>): lootGroupTemplate, level (optional: <string> <string>: compare, log)" << endl
					<< "Syntax: /server loot checktemplates";

			player->sendSystemMessage(syntax.toString());

		}
	}
};

#endif /* SERVERLOOTCOMMAND_H_ */
