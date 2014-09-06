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

#include "SuiManager.h"

#include "server/zone/managers/radial/RadialManager.h"

#include "server/zone/ZoneProcessServer.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/sui/SuiWindowType.h"
#include "server/zone/objects/player/sui/banktransferbox/SuiBankTransferBox.h"
#include "server/zone/objects/player/sui/characterbuilderbox/SuiCharacterBuilderBox.h"
#include "server/zone/objects/player/sui/transferbox/SuiTransferBox.h"
#include "server/zone/objects/creature/commands/UnconsentCommand.h"
#include "server/zone/managers/objectcontroller/ObjectController.h"
#include "server/zone/managers/resource/ResourceManager.h"
#include "server/zone/managers/skill/SkillManager.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/objects/group/GroupObject.h"
#include "server/zone/packets/chat/ChatSystemMessage.h"
#include "server/zone/objects/player/sui/SuiBox.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/player/sui/inputbox/SuiInputBox.h"
#include "server/zone/objects/player/sui/messagebox/SuiMessageBox.h"
#include "server/zone/Zone.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/managers/minigames/FishingManager.h"
#include "server/zone/managers/minigames/GamblingManager.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/objects/tangible/tool/SurveyTool.h"
#include "server/zone/objects/tangible/ticket/TicketObject.h"
#include "server/zone/objects/installation/InstallationObject.h"
#include "server/zone/objects/installation/factory/FactoryObject.h"
#include "server/zone/objects/manufactureschematic/ManufactureSchematic.h"
#include "server/zone/objects/player/sui/keypadbox/SuiKeypadBox.h"
#include "server/zone/objects/player/sui/callbacks/LuaSuiCallback.h"
#include "server/zone/objects/tangible/terminal/characterbuilder/CharacterBuilderTerminal.h"
#include "server/zone/objects/tangible/deed/resource/ResourceDeed.h"
#include "server/zone/managers/planet/MapLocationType.h"
#include "server/zone/managers/city/CityManager.h"
#include "server/zone/objects/creature/commands/FindCommand.h"
#include "server/zone/objects/creature/commands/sui/DestroyCommandSuiCallback.h"
#include "server/zone/objects/player/sessions/sui/FindSessionSuiCallback.h"
#include "server/zone/objects/creature/commands/sui/ListGuildsResponseSuiCallback.h"
#include "server/zone/objects/player/sessions/sui/SlicingSessionSuiCallback.h"
#include "server/zone/objects/player/sessions/vendor/sui/CreateVendorSuiCallback.h"
#include "server/zone/objects/player/sessions/vendor/sui/NameVendorSuiCallback.h"
#include "server/zone/objects/creature/sui/RepairVehicleSuiCallback.h"
#include "server/zone/objects/creature/commands/sui/InstallMissionTerminalSuiCallback.h"
#include "server/zone/objects/creature/commands/sui/RecruitSkillTrainerSuiCallback.h"
#include "server/zone/objects/creature/CreatureAttribute.h"
#include "server/zone/objects/creature/CreatureState.h"
#include "server/zone/objects/tangible/tool/sui/SurveyToolSetRangeSuiCallback.h"
#include "server/zone/managers/guild/GuildManager.h"
#include "server/zone/objects/tangible/terminal/guild/GuildTerminal.h"
#include "server/zone/objects/guild/GuildObject.h"
#include "server/zone/objects/tangible/sign/SignObject.h"
#include "server/zone/objects/scene/ObserverEventType.h"
#include "server/zone/objects/tangible/deed/eventperk/EventPerkDeed.h"

SuiManager::SuiManager() : Logger("SuiManager") {
	server = NULL;
	setGlobalLogging(true);
	setLogging(false);
}

void SuiManager::handleSuiEventNotification(uint32 boxID, CreatureObject* player, uint32 cancel, Vector<UnicodeString>* args) {
	uint16 windowType = (uint16) boxID;

	Locker _lock(player);

	ManagedReference<PlayerObject*> ghost = player->getPlayerObject();

	if (ghost == NULL)
		return;

	ManagedReference<SuiBox*> suiBox = ghost->getSuiBox(boxID);

	if (suiBox == NULL)
		return;

	//Remove the box from the player, callback can readd it to the player if needed.
	ghost->removeSuiBox(boxID);
	suiBox->clearOptions(); //TODO: Eventually SuiBox needs to be cleaned up to not need this.

	Reference<SuiCallback*> callback = suiBox->getCallback();

	if (callback != NULL) {
		callback->run(player, suiBox, cancel, args);
		return;
	}

	StringBuffer msg;
	msg << "Unknown message callback with SuiWindowType: " << hex << windowType << ". Falling back on old handler system.";
	//info(msg, true);

	switch (windowType) {
	case SuiWindowType::MEDIC_CONSENT:
		handleConsentBox(player, suiBox, cancel, args);
		break;
	case SuiWindowType::DANCING_START:
		handleStartDancing(player, suiBox, cancel, args);
		break;
	case SuiWindowType::DANCING_CHANGE:
		handleStartDancing(player, suiBox, cancel, args);
		break;
	case SuiWindowType::MUSIC_START:
		handleStartMusic(player, suiBox, cancel, args);
		break;
	case SuiWindowType::MUSIC_CHANGE:
		handleStartMusic(player, suiBox, cancel, args);
		break;
	case SuiWindowType::BAND_START:
		handleStartMusic(player, suiBox, cancel, args);
		break;
	case SuiWindowType::BAND_CHANGE:
		handleStartMusic(player, suiBox, cancel, args);
		break;
	case SuiWindowType::BANK_TRANSFER:
		handleBankTransfer(player, suiBox, cancel, args);
		break;
	case SuiWindowType::FISHING:
		handleFishingAction(player, suiBox, cancel, args);
		break;
	case SuiWindowType::CHARACTER_BUILDER_LIST:
		handleCharacterBuilderSelectItem(player, suiBox, cancel, args);
		break;
	case SuiWindowType::MEDIC_DIAGNOSE:
		handleDiagnose(player, suiBox, cancel, args);
		break;
	case SuiWindowType::OBJECT_NAME:
		handleSetObjectName(player, suiBox, cancel, args);
		break;
	}
}

void SuiManager::handleSetObjectName(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args) {
	if (!suiBox->isInputBox() || cancel != 0)
		return;

	ManagedReference<SceneObject*> object = suiBox->getUsingObject();

	if (object == NULL)
		return;

	if (args->size() < 1)
		return;

	UnicodeString objectName = args->get(0);

	object->setCustomObjectName(objectName, true);

	if (object->isSignObject()) {
		StringIdChatParameter params("@player_structure:prose_sign_name_updated"); //Sign name successfully updated to '%TO'.
		params.setTO(objectName);

		player->sendSystemMessage(params);
	}
}

void SuiManager::handleStartDancing(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args) {
	if (!suiBox->isListBox() || cancel != 0)
		return;

	if (args->size() < 2)
		return;

	int index = Integer::valueOf(args->get(0).toString());

	uint32 id = suiBox->getBoxID();

	bool change = (uint16)id == SuiWindowType::DANCING_CHANGE;


	SuiListBox* listBox = cast<SuiListBox*>( suiBox);

	if (index == -1)
		return;

	String dance = listBox->getMenuItemName(index);

	if (!change)
		player->executeObjectControllerAction(String("startdance").hashCode(), 0, dance);
	else
		player->executeObjectControllerAction(String("changedance").hashCode(), 0, dance);
}

void SuiManager::handleStartMusic(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args) {
	if (!suiBox->isListBox() || cancel != 0)
		return;

	if (args->size() < 2)
		return;

	int index = Integer::valueOf(args->get(0).toString());

	uint32 id = suiBox->getBoxID();

	SuiListBox* listBox = cast<SuiListBox*>( suiBox);

	if (index == -1)
		return;

	String dance = listBox->getMenuItemName(index);

	switch ((uint16)id) {
	case SuiWindowType::MUSIC_START:
		player->executeObjectControllerAction(String("startmusic").hashCode(), player->getTargetID(), dance);
		break;
	case SuiWindowType::MUSIC_CHANGE:
		player->executeObjectControllerAction(String("changemusic").hashCode(), player->getTargetID(), dance);
		break;
	case SuiWindowType::BAND_CHANGE:
		player->executeObjectControllerAction(String("changebandmusic").hashCode(), player->getTargetID(), dance);
		break;
	case SuiWindowType::BAND_START:
		player->executeObjectControllerAction(String("startband").hashCode(), player->getTargetID(), dance);
		break;
	}
}

/*
void SuiManager::handleTicketCollectorResponse(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args) {
	if (!suiBox->isListBox() || cancel != 0)
		return;

	if (args->size() < 1)
		return;

	SuiListBox* listBox = cast<SuiListBox*>( suiBox);

	int index = Integer::valueOf(args->get(0).toString());

	uint64 ticketObjectID = listBox->getMenuObjectID(index);

	if (ticketObjectID == 0)
		return;

	ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");

	if (inventory == NULL)
		return;

	ManagedReference<SceneObject*> obj = inventory->getContainerObject(ticketObjectID);

	if (obj == NULL || !obj->isTangibleObject())
		return;

	TangibleObject* tano = cast<TangibleObject*>( obj.get());

	if (!tano->isTicketObject())
		return;

	TicketObject* ticket = cast<TicketObject*>( tano);
	ticket->handleObjectMenuSelect(player, 20);
}
 */
void SuiManager::handleBankTransfer(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args) {
	if (!suiBox->isBankTransferBox() || cancel != 0)
		return;

	if (args->size() < 2)
		return;

	int cash = Integer::valueOf(args->get(0).toString());
	int bank = Integer::valueOf(args->get(1).toString());

	SuiBankTransferBox* suiBank = cast<SuiBankTransferBox*>( suiBox);

	ManagedReference<SceneObject*> bankObject = suiBank->getBank();

	if (bankObject == NULL)
		return;

	if (!player->isInRange(bankObject, 5))
		return;

	uint32 currentCash = player->getCashCredits();
	uint32 currentBank = player->getBankCredits();

	if ((currentCash + currentBank) == ((uint32) cash + (uint32) bank)) {
		player->setCashCredits(cash);
		player->setBankCredits(bank);
	}

}

void SuiManager::handleFishingAction(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args) {
	if (cancel != 0)
		return;

	if (args->size() < 1)
		return;

	int index = Integer::valueOf(args->get(0).toString());

	FishingManager* manager = server->getFishingManager();

	manager->setNextAction(player, index + 1);

	uint32 newBoxID = 0;

	switch (index + 1) {
	case FishingManager::TUGUP:
		newBoxID = manager->createWindow(player, suiBox->getBoxID());
		break;
	case FishingManager::TUGRIGHT:
		newBoxID = manager->createWindow(player, suiBox->getBoxID());
		break;
	case FishingManager::TUGLEFT:
		newBoxID = manager->createWindow(player, suiBox->getBoxID());
		break;
	case FishingManager::REEL:
		newBoxID = manager->createWindow(player, suiBox->getBoxID());
		break;
	case FishingManager::STOPFISHING:
		player->sendSystemMessage("@fishing:stop_fishing"); //You reel-in your line and stop fishing...
		manager->stopFishing(player, suiBox->getBoxID(), true);
		return;
		break;
	default:
		newBoxID = manager->createWindow(player, suiBox->getBoxID());
		break;
	}

	manager->setFishBoxID(player, suiBox->getBoxID());
}

void SuiManager::handleCharacterBuilderSelectItem(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args) {
	ZoneServer* zserv = player->getZoneServer();

	if (args->size() < 1)
		return;

	bool otherPressed = false;
	int index = 0;

	if(args->size() > 1) {
		otherPressed = Bool::valueOf(args->get(0).toString());
		index = Integer::valueOf(args->get(1).toString());
	} else {
		index = Integer::valueOf(args->get(0).toString());
	}

	if (!suiBox->isCharacterBuilderBox())
		return;

	ManagedReference<SuiCharacterBuilderBox*> cbSui = cast<SuiCharacterBuilderBox*>( suiBox);

	CharacterBuilderMenuNode* currentNode = cbSui->getCurrentNode();

	PlayerObject* ghost = player->getPlayerObject();

	//If cancel was pressed then we kill the box/menu.
	if (cancel != 0)
		return;

	//Back was pressed. Send the node above it.
	if (otherPressed) {
		CharacterBuilderMenuNode* parentNode = currentNode->getParentNode();

		if(parentNode == NULL)
			return;

		cbSui->setCurrentNode(parentNode);

		ghost->addSuiBox(cbSui);
		player->sendMessage(cbSui->generateMessage());
		return;
	}

	CharacterBuilderMenuNode* node = currentNode->getChildNodeAt(index);

	//Node doesn't exist or the index was out of bounds. Should probably resend the menu here.
	if (node == NULL) {
		ghost->addSuiBox(cbSui);
		player->sendMessage(cbSui->generateMessage());
		return;
	}

	if (node->hasChildNodes()) {
		//If it has child nodes, display them.
		cbSui->setCurrentNode(node);
		ghost->addSuiBox(cbSui);
		player->sendMessage(cbSui->generateMessage());
	} else {

		String templatePath = node->getTemplatePath();

		if (templatePath.indexOf(".iff") < 0) { // Non-item selections

			if (templatePath == "unlearn_all_skills") {

				SkillManager::instance()->surrenderAllSkills(player);
				player->sendSystemMessage("All skills unlearned.");

			} else if (templatePath == "cleanse_character") {

				if (!player->isInCombat()) {
					player->sendSystemMessage("You have been cleansed from the signs of previous battles.");

					for (int i = 0; i < 9; ++i) {
						player->setWounds(i, 0);
					}

					player->setShockWounds(0);
				} else {
					player->sendSystemMessage("Not within combat.");
				}

			} else if (templatePath == "reset_buffs") {

				if (!player->isInCombat()) {
					player->sendSystemMessage("Your buffs have been reset.");

					player->clearBuffs(true);

					ghost->setFoodFilling(0);
					ghost->setDrinkFilling(0);
				} else {
					player->sendSystemMessage("Not within combat.");
				}

			} else if (templatePath.beginsWith("crafting_apron_")) {

				//"object/tangible/wearables/apron/apron_chef_s01.iff"
				//"object/tangible/wearables/ithorian/apron_chef_jacket_s01_ith.iff"

				uint32 itemCrc = ( player->getSpecies() != CreatureObject::ITHORIAN ) ? 0x5DDC4E5D : 0x6C191FBB;

				ManagedReference<WearableObject*> apron = zserv->createObject(itemCrc, 2).castTo<WearableObject*>();

				if (apron == NULL) {
					player->sendSystemMessage("There was an error creating the requested item. Please contact customer support with this issue.");
					ghost->addSuiBox(cbSui);
					player->sendMessage(cbSui->generateMessage());

					error("could not create frog crafting apron");
					return;
				}

				apron->createChildObjects();

				if (apron->isWearableObject()) {
					uint32 bitmask = apron->getOptionsBitmask() | OptionBitmask::YELLOW;
					apron->setOptionsBitmask(bitmask, false);

					UnicodeString modName = "(General)";
					apron->addSkillMod(SkillModManager::WEARABLE, "general_assembly", 25);
					apron->addSkillMod(SkillModManager::WEARABLE, "general_experimentation", 25);

					if(templatePath == "crafting_apron_armorsmith") {
						modName = "(Armorsmith)";
						apron->addSkillMod(SkillModManager::WEARABLE, "armor_assembly", 25);
						apron->addSkillMod(SkillModManager::WEARABLE, "armor_experimentation", 25);
						apron->addSkillMod(SkillModManager::WEARABLE, "armor_repair", 25);
					} else if(templatePath == "crafting_apron_weaponsmith") {
						modName = "(Weaponsmith)";
						apron->addSkillMod(SkillModManager::WEARABLE, "weapon_assembly", 25);
						apron->addSkillMod(SkillModManager::WEARABLE, "weapon_experimentation", 25);
						apron->addSkillMod(SkillModManager::WEARABLE, "weapon_repair", 25);
						apron->addSkillMod(SkillModManager::WEARABLE, "grenade_assembly", 25);
						apron->addSkillMod(SkillModManager::WEARABLE, "grenade_experimentation", 25);
					} else if(templatePath == "crafting_apron_tailor") {
						modName = "(Tailor)";
						apron->addSkillMod(SkillModManager::WEARABLE, "clothing_assembly", 25);
						apron->addSkillMod(SkillModManager::WEARABLE, "clothing_experimentation", 25);
						apron->addSkillMod(SkillModManager::WEARABLE, "clothing_repair", 25);
					} else if(templatePath == "crafting_apron_chef") {
						modName = "(Chef)";
						apron->addSkillMod(SkillModManager::WEARABLE, "food_assembly", 25);
						apron->addSkillMod(SkillModManager::WEARABLE, "food_experimentation", 25);
					} else if(templatePath == "crafting_apron_architect") {
						modName = "(Architect)";
						apron->addSkillMod(SkillModManager::WEARABLE, "structure_assembly", 25);
						apron->addSkillMod(SkillModManager::WEARABLE, "structure_experimentation", 25);
						apron->addSkillMod(SkillModManager::WEARABLE, "structure_complexity", 25);
					} else if(templatePath == "crafting_apron_droid_engineer") {
						modName = "(Droid Engineer)";
						apron->addSkillMod(SkillModManager::WEARABLE, "droid_assembly", 25);
						apron->addSkillMod(SkillModManager::WEARABLE, "droid_experimentation", 25);
						apron->addSkillMod(SkillModManager::WEARABLE, "droid_complexity", 25);
					} else if(templatePath == "crafting_apron_doctor") {
						modName = "(Doctor)";
						apron->addSkillMod(SkillModManager::WEARABLE, "medicine_assembly", 25);
						apron->addSkillMod(SkillModManager::WEARABLE, "medicine_experimentation", 25);
					} else if(templatePath == "crafting_apron_combat_medic") {
						modName = "(Combat Medic)";
						apron->addSkillMod(SkillModManager::WEARABLE, "combat_medicine_assembly", 25);
						apron->addSkillMod(SkillModManager::WEARABLE, "combat_medicine_experimentation", 25);
					}

					UnicodeString apronName = "Crafting Apron " + modName;
					apron->setCustomObjectName(apronName, false);
				}

				ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");
				apron->sendTo(player, true);
				inventory->transferObject(apron, -1, true);

				StringIdChatParameter stringId;
				stringId.setStringId("@faction_perk:bonus_base_name"); //You received a: %TO.
				stringId.setTO(apron);
				player->sendSystemMessage(stringId);

			} else if (templatePath == "enhance_character") {

				ManagedReference<SceneObject*> scob = cbSui->getUsingObject();
				if (scob != NULL) {

					if (scob->getGameObjectType() == SceneObjectType::CHARACTERBUILDERTERMINAL) {
						CharacterBuilderTerminal* bluefrog = cast<CharacterBuilderTerminal*>( scob.get());
						bluefrog->enhanceCharacter(player);
					}
				}

			} else if (templatePath == "credits") {

				player->addCashCredits(50000, true);
				player->sendSystemMessage("You have received 50.000 Credits");

			} else if (templatePath == "faction_rebel") {

				ghost->increaseFactionStanding("rebel", 100000);

			} else if (templatePath == "faction_imperial") {

				ghost->increaseFactionStanding("imperial", 100000);

			} else if (templatePath == "language") {

				ManagedReference<SceneObject*> scob = cbSui->getUsingObject();
				if (scob != NULL) {

					if (scob->getGameObjectType() == SceneObjectType::CHARACTERBUILDERTERMINAL) {
						CharacterBuilderTerminal* bluefrog = cast<CharacterBuilderTerminal*>( scob.get());
						bluefrog->giveLanguages(player);
					}
				}

			} else if (templatePath == "apply_dots") {
				ManagedReference<SceneObject*> scob = cbSui->getUsingObject();
				player->addDotState(CreatureState::POISONED, scob->getObjectID(), 100, CreatureAttribute::HEALTH, 60, 80, 0);
				player->addDotState(CreatureState::BLEEDING, scob->getObjectID(), 100, CreatureAttribute::ACTION, 60, 80, 0);
				player->addDotState(CreatureState::DISEASED, scob->getObjectID(), 100, CreatureAttribute::ACTION, 60, 80, 0);
				player->addDotState(CreatureState::ONFIRE, scob->getObjectID(), 100, CreatureAttribute::HEALTH, 60, 80, 0);
			} else if (templatePath == "clear_dots") {
				player->clearDots();
			} else if (templatePath == "max_xp") {
				ghost->maximizeExperience();
				player->sendSystemMessage("You have maximized all xp types.");
			} else {

				if (templatePath.length() > 0) {

					SkillManager::instance()->awardSkill(templatePath, player, true, true, true);
					if (player->hasSkill(templatePath))
						player->sendSystemMessage("You have learned a skill.");

				} else {

					player->sendSystemMessage("Unknown selection.");

				}
			}

			ghost->addSuiBox(cbSui);
			player->sendMessage(cbSui->generateMessage());
		} else { // Items

			if (templatePath.contains("event_perk")) {
				if (ghost->getEventPerkCount() >= 5) {
					player->sendSystemMessage("@event_perk:pro_too_many_perks"); // You cannot rent any more items right now.
					ghost->addSuiBox(cbSui);
					player->sendMessage(cbSui->generateMessage());
					return;
				}
			}

			ManagedReference<SceneObject*> item = zserv->createObject(node->getTemplateCRC(), 1);

			if (item == NULL) {
				player->sendSystemMessage("There was an error creating the requested item. Please contact customer support with this issue.");
				ghost->addSuiBox(cbSui);
				player->sendMessage(cbSui->generateMessage());

				error("could not create frog item: " + node->getDisplayName());
				return;
			}

			item->createChildObjects();

			if (item->isEventPerkDeed()) {
				EventPerkDeed* deed = cast<EventPerkDeed*>(item.get());
				deed->setOwner(player);
				ghost->addEventPerk(deed);
			}

			ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");
			item->sendTo(player, true);
			inventory->transferObject(item, -1, true);

			StringIdChatParameter stringId;
			stringId.setStringId("@faction_perk:bonus_base_name"); //You received a: %TO.
			stringId.setTO(item);
			player->sendSystemMessage(stringId);

			ghost->addSuiBox(cbSui);
			player->sendMessage(cbSui->generateMessage());
		}
	}
}

void SuiManager::handleDiagnose(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args) {
}

void SuiManager::handleConsentBox(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args) {
	if (suiBox->isListBox() || cancel != 0)
		return;

	if (args->size() < 1)
		return;

	int index = Integer::valueOf(args->get(0).toString());

	if (index == -1)
		return;

	SuiListBox* suiList = cast<SuiListBox*>( suiBox);

	String name = suiList->getMenuItemName(index);
	UnconsentCommand::unconscent(player, name);
}

void SuiManager::sendKeypadSui(SceneObject* keypad, SceneObject* creatureSceneObject, const String& play, const String& callback) {

	if (keypad == NULL)
		return;

	if (creatureSceneObject == NULL || !creatureSceneObject->isCreatureObject())
		return;

	CreatureObject* creature = cast<CreatureObject*>(creatureSceneObject);

	PlayerObject* playerObject = creature->getPlayerObject();

	if (playerObject != NULL) {
		ManagedReference<SuiKeypadBox*> keypadSui = new SuiKeypadBox(creature, 0x00);
		keypadSui->setCallback(new LuaSuiCallback(creature->getZoneServer(), play, callback));
		keypadSui->setUsingObject(keypad);
		keypadSui->setForceCloseDisabled();
		creature->sendMessage(keypadSui->generateMessage());
		playerObject->addSuiBox(keypadSui);
	}

}

void SuiManager::sendConfirmSui(SceneObject* terminal, SceneObject* player, const String& play, const String& callback, const String& prompt, const String& button) {

	if (terminal == NULL)
		return;

	if (player == NULL || !player->isCreatureObject())
		return;

	CreatureObject* creature = cast<CreatureObject*>(player);

	PlayerObject* playerObject = creature->getPlayerObject();

	if (playerObject != NULL) {
		ManagedReference<SuiMessageBox*> confirmSui = new SuiMessageBox(creature, 0x00);
		confirmSui->setCallback(new LuaSuiCallback(creature->getZoneServer(), play, callback));
		confirmSui->setUsingObject(terminal);
		confirmSui->setPromptText(prompt);
		confirmSui->setOkButton(true, button);
		confirmSui->setOtherButton(false, "");
		confirmSui->setCancelButton(false, "");
		confirmSui->setForceCloseDistance(32);
		creature->sendMessage(confirmSui->generateMessage());
		playerObject->addSuiBox(confirmSui);
	}

}



void SuiManager::sendInputBox(SceneObject* terminal, SceneObject* player, const String& play, const String& callback, const String& prompt, const String& button) {
	if (terminal == NULL)
		return;

	if (player == NULL || !player->isCreatureObject())
		return;

	CreatureObject* creature = cast<CreatureObject*>(player);

	PlayerObject* playerObject = creature->getPlayerObject();

	if (playerObject != NULL) {
		ManagedReference<SuiInputBox*> confirmSui = new SuiInputBox(creature, 0x00);
		confirmSui->setCallback(new LuaSuiCallback(creature->getZoneServer(), play, callback));
		confirmSui->setUsingObject(terminal);
		confirmSui->setPromptText(prompt);
		confirmSui->setOkButton(true, button);
		confirmSui->setOtherButton(false, "");
		confirmSui->setCancelButton(false, "");
		confirmSui->setForceCloseDistance(32);
		creature->sendMessage(confirmSui->generateMessage());
		playerObject->addSuiBox(confirmSui);
	}

}

void SuiManager::sendMessageBox(SceneObject* usingObject, SceneObject* player, const String& title, const String& text, const String& okButton, const String& screenplay, const String& callback) {
	if (usingObject == NULL)
		return;

	if (player == NULL || !player->isCreatureObject())
		return;

	CreatureObject* creature = cast<CreatureObject*>(player);

	PlayerObject* playerObject = creature->getPlayerObject();

	if (playerObject != NULL) {
		ManagedReference<SuiMessageBox*> messageBox = new SuiMessageBox(creature, 0x00);
		messageBox->setCallback(new LuaSuiCallback(creature->getZoneServer(), screenplay, callback));
		messageBox->setPromptTitle(title);
		messageBox->setPromptText(text);
		messageBox->setUsingObject(usingObject);
		messageBox->setOkButton(true, okButton);
		messageBox->setCancelButton(true, "@cancel");
		messageBox->setForceCloseDistance(32.f);

		creature->sendMessage(messageBox->generateMessage());
		playerObject->addSuiBox(messageBox);
	}
}

void SuiManager::sendListBox(SceneObject* usingObject, SceneObject* player, const String& title, const String& text, const uint8& numOfButtons, const String& cancelButton, const String& otherButton, const String& okButton, LuaObject& options, const String& screenplay, const String& callback) {
	if (usingObject == NULL)
		return;

	if (player == NULL || !player->isCreatureObject())
		return;

	CreatureObject* creature = cast<CreatureObject*>(player);

	PlayerObject* playerObject = creature->getPlayerObject();

	if (playerObject != NULL) {

		ManagedReference<SuiListBox*> box = NULL;

		switch (numOfButtons) {
		case 1:
			box = new SuiListBox(creature, 0x00, SuiListBox::HANDLESINGLEBUTTON);
			box->setCancelButton(false, "");
			box->setOtherButton(false, "");
			box->setOkButton(true, okButton);
			break;
		case 2:
			box = new SuiListBox(creature, 0x00, SuiListBox::HANDLETWOBUTTON);
			box->setCancelButton(true, cancelButton);
			box->setOtherButton(false, "");
			box->setOkButton(true, okButton);
			break;
		case 3:
			box = new SuiListBox(creature, 0x00, SuiListBox::HANDLETHREEBUTTON);
			box->setCancelButton(true, cancelButton);
			box->setOtherButton(true, otherButton);
			box->setOkButton(true, okButton);
			break;
		default:
			return;
			break;
		}

		if(options.isValidTable()){
			for(int i = 1; i <= options.getTableSize(); ++i){
				String optionString = options.getStringAt(i);
				box->addMenuItem(optionString);
			}
			options.pop();
		}

		box->setCallback(new LuaSuiCallback(creature->getZoneServer(), screenplay, callback));
		box->setPromptTitle(title);
		box->setPromptText(text);
		box->setUsingObject(usingObject);
		box->setForceCloseDistance(32.f);

		creature->sendMessage(box->generateMessage());
		playerObject->addSuiBox(box);
	}
}
