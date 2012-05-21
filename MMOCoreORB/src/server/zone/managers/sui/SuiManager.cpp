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

#include "../radial/RadialManager.h"

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
#include "server/zone/managers/structure/StructureManager.h"
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
	case SuiWindowType::STRUCTURE_MANAGE_MAINTENANCE:
		handleManageMaintenance(player, suiBox, cancel, args);
		break;
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
	case SuiWindowType::STRUCTURE_ADD_ENERGY:
		handleAddEnergy(player, suiBox, cancel, args);
		break;
	case SuiWindowType::FACTORY_SCHEMATIC2BUTTON:
		handleInsertFactorySchem2(player, suiBox, cancel, args);
		break;
	case SuiWindowType::FACTORY_SCHEMATIC3BUTTON:
		handleInsertFactorySchem3(player, suiBox, cancel, args);
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

void SuiManager::handleManageMaintenance(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args) {
	if (!suiBox->isTransferBox() || cancel != 0)
		return;

	ManagedReference<SceneObject*> object = suiBox->getUsingObject();

	if (object == NULL || !object->isStructureObject())
		return;

	StructureObject* structureObject = cast<StructureObject*>( object.get());

	if (args->size() < 1)
		return;

	int transferAmount = Integer::valueOf(args->get(0).toString());
	int currentCash = player->getCashCredits();

	if (transferAmount > currentCash) {
		//Send a message ot the player, and return.
		return;
	}

	if (transferAmount < 0) {
		//Send a message to the player, and return.
		return;
	}

	Locker _lock(structureObject, player);

	int transferTotal = currentCash - transferAmount;

	//TODO: Handle this in StructureManager.
	//ManagedReference<StructureManager*> structureManager = structureObject->getZone()->getPlanetManager()->getStructureManager();
	//structureManager->depositMaintenance(player, structureObject, transferTotal);

	structureObject->addMaintenance(transferTotal);
	player->subtractCashCredits(transferTotal);

	StringIdChatParameter stringId("base_player", "prose_pay_success");
	stringId.setTT(structureObject->getObjectID());
	stringId.setDI(transferTotal);

	player->sendSystemMessage(stringId);
	structureObject->updateToDatabase();

	player->updateToDatabase();
}


void SuiManager::handleAddEnergy(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args) {
	if (!suiBox->isTransferBox() || cancel != 0)
		return;

	if (args->size() < 1)
		return;

	uint32 newEnergyVal = (uint64) Long::valueOf(args->get(0).toString());

	ManagedReference<SceneObject*> object = suiBox->getUsingObject();

	if (object == NULL || !object->isInstallationObject())
		return;

	InstallationObject* installation = cast<InstallationObject*>( object.get());

	ManagedReference<ResourceManager*> resourceManager = player->getZoneServer()->getResourceManager();

	//TODO: This should be handled in StructureManager

	Locker _lock(installation, player);

	uint32 energyFromPlayer = resourceManager->getAvailablePowerFromPlayer(player);
	uint32 energy = energyFromPlayer - newEnergyVal;

	if (energy > energyFromPlayer)
		return;

	installation->addPower(energy);
	resourceManager->removePowerFromPlayer(player, energy);

	StringIdChatParameter stringId("player_structure", "deposit_successful");
	stringId.setDI(energy);

	player->sendSystemMessage(stringId);

	stringId.setStringId("player_structure", "reserve_report");
	stringId.setDI(installation->getSurplusPower());

	player->sendSystemMessage(stringId);

	installation->updateToDatabase();
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

	bool change = (uint16)id == SuiWindowType::MUSIC_CHANGE;

	SuiListBox* listBox = cast<SuiListBox*>( suiBox);

	if (index == -1)
		return;

	String dance = listBox->getMenuItemName(index);

	if (!change)
		player->executeObjectControllerAction(String("startmusic").hashCode(), player->getTargetID(), dance);
	else
		player->executeObjectControllerAction(String("changemusic").hashCode(), player->getTargetID(), dance);
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

			} else if (templatePath == "enhance_character") {

				SceneObject* scob = cbSui->getUsingObject();
				if (scob != NULL) {

					if (scob->getGameObjectType() == SceneObjectType::CHARACTERBUILDERTERMINAL) {
						CharacterBuilderTerminal* bluefrog = cast<CharacterBuilderTerminal*>( scob);
						bluefrog->enhanceCharacter(player);
					}
				}

			} else if (templatePath == "credits") {

				player->addCashCredits(50000, true);
				player->sendSystemMessage("You have received 50.000 Credits");

			} else if (templatePath == "language") {

				SceneObject* scob = cbSui->getUsingObject();
				if (scob != NULL) {

					if (scob->getGameObjectType() == SceneObjectType::CHARACTERBUILDERTERMINAL) {
						CharacterBuilderTerminal* bluefrog = cast<CharacterBuilderTerminal*>( scob);
						bluefrog->giveLanguages(player);
					}
				}

			} else if (templatePath == "apply_dots") {
				SceneObject* scob = cbSui->getUsingObject();
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

			ManagedReference<SceneObject*> item = zserv->createObject(node->getTemplateCRC(), 1);

			if (item == NULL) {
				player->sendSystemMessage("There was an error creating the requested item. Please contact customer support with this issue.");
				ghost->addSuiBox(cbSui);
				player->sendMessage(cbSui->generateMessage());

				error("could not craete frog item: " + node->getDisplayName());
				return;
			}

			item->createChildObjects();

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

void SuiManager::handleInsertFactorySchem2(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args) {
	if (!suiBox->isListBox() || cancel != 0)
		return;

	if (args->size() < 1)
		return;

	int index = Integer::valueOf(args->get(0).toString());

	SuiListBox* listBox = cast<SuiListBox*>( suiBox);

	ManagedReference<SceneObject*> object = suiBox->getUsingObject();

	if (object == NULL || !object->isFactory())
		return;

	FactoryObject* factory = cast<FactoryObject*>( object.get());

	Locker _lock(factory, player);

	ManagedReference<ManufactureSchematic*> schematic = dynamic_cast<ManufactureSchematic*>(server->getZoneServer()->getObject(listBox->getMenuObjectID(index)));
	factory->handleInsertFactorySchem(player, schematic);
}

void SuiManager::handleInsertFactorySchem3(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args) {
	if (!suiBox->isListBox() || cancel != 0)
		return;

	if (args->size() < 2)
		return;

	bool otherPressed = Bool::valueOf(args->get(0).toString());
	int index = Integer::valueOf(args->get(1).toString());

	SuiListBox* listBox = cast<SuiListBox*>( suiBox);

	ManagedReference<SceneObject*> object = suiBox->getUsingObject();

	if (object == NULL || !object->isFactory())
		return;

	FactoryObject* factory = cast<FactoryObject*>( object.get());

	Locker _lock(factory, player);

	factory->handleRemoveFactorySchem(player);

	if (!otherPressed) {
		ManagedReference<ManufactureSchematic*> schematic = dynamic_cast<ManufactureSchematic*>(server->getZoneServer()->getObject(listBox->getMenuObjectID(index)));
		factory->handleInsertFactorySchem(player, schematic);
	}
}

void SuiManager::sendKeypadSui(SceneObject* keypad, SceneObject* creatureSceneObject, String play, String callback) {

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

void SuiManager::sendConfirmSui(SceneObject* terminal, SceneObject* player, String play, String callback, String prompt, String button) {

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

void SuiManager::sendMessageBox(SceneObject* usingObject, SceneObject* player, String title, String text, String okButton, String screenplay, String callback) {
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
		messageBox->setForceCloseDistance(32.f);

		creature->sendMessage(messageBox->generateMessage());
		playerObject->addSuiBox(messageBox);
	}
}
