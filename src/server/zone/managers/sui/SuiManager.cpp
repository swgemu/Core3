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

/*
#include "../../objects/player/sui/messagebox/SuiMessageBox.h"
#include "../../objects/player/sui/colorpicker/SuiColorPicker.h"*/

#include "../radial/RadialManager.h"

#include "server/zone/ZoneProcessServerImplementation.h"
#include "server/zone/objects/player/PlayerCreature.h"
#include "server/zone/objects/player/sui/SuiWindowType.h"
#include "server/zone/objects/player/sui/banktransferbox/SuiBankTransferBox.h"
#include "server/zone/objects/player/sui/characterbuilderbox/SuiCharacterBuilderBox.h"
#include "server/zone/objects/player/sui/transferbox/SuiTransferBox.h"
#include "server/zone/objects/creature/commands/UnconsentCommand.h"
#include "server/zone/managers/objectcontroller/ObjectController.h"
#include "server/zone/managers/resource/ResourceManager.h"
#include "server/zone/managers/professions/ProfessionManager.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/managers/structure/StructureManager.h"
#include "server/zone/objects/group/GroupObject.h"
#include "server/zone/packets/chat/ChatSystemMessage.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/player/sui/listbox/teachplayerlistbox/TeachPlayerListBox.h"
#include "server/zone/objects/player/sui/listbox/playerlearnlistbox/PlayerLearnListBox.h"
#include "server/zone/objects/player/sui/inputbox/SuiInputBox.h"
#include "server/zone/Zone.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/managers/minigames/FishingManager.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/objects/tangible/tool/SurveyTool.h"
#include "server/zone/objects/tangible/ticket/TicketObject.h"
#include "server/zone/objects/installation/InstallationObject.h"
#include "server/zone/objects/installation/factory/FactoryObject.h"
#include "server/zone/objects/manufactureschematic/ManufactureSchematic.h"
#include "server/zone/objects/building/city/CityHallObject.h"
#include "server/zone/objects/tangible/terminal/characterbuilder/CharacterBuilderTerminal.h"


/*#include "../item/ItemManager.h"
#include "../../objects/creature/bluefrog/BlueFrogVector.h"

#include "../../../login/packets/ErrorMessage.h"

#include "../../objects/tangible/deed/resourcedeed/ResourceDeedImplementation.h"
#include "../../objects/tangible/deed/resourcedeed/ResourceDeed.h"

#include "../resource/ResourceManagerImplementation.h"

#include "../../objects/creature/skills/self/events/AreaTrackEvent.h"

#include "../../../chat/GameCommandHandler.h"*/

SuiManager::SuiManager(ZoneProcessServerImplementation* serv) : Logger("SuiManager") {
	server = serv;

	setGlobalLogging(true);
	setLogging(false);
}

void SuiManager::handleSuiEventNotification(uint32 boxID, PlayerCreature* player, uint32 cancel, const String& value, const String& value2) {
	uint16 type = (uint16) boxID;
	int range;
	String returnString;

	//GuildManager* pGuild = server->getGuildManager();

	switch (type) {
	/*case SuiWindowType::CHARACTERLIST:
		handleCharacterListSelection(boxID, player, cancel, atoi(value.toCharArray()));
		break;
	case SuiWindowType::ACCOUNTLIST:
		handleAccountListSelection(boxID, player, cancel, atoi(value.toCharArray()));
		break;
	case SuiWindowType::COMMANDSLIST:
		handleCommandsListSelection(boxID, player, cancel, atoi(value.toCharArray()));
		break;
	case SuiWindowType::BANLIST:
		handleBanListSelection(boxID, player, cancel, atoi(value.toCharArray()));
		break;
	case SuiWindowType::TUNE_CRYSTAL:
		handleTuneCrystal(boxID, player, cancel);
		break;
	case SuiWindowType::INSERT_COLOR_CRYSTAL:
		handleChangeColorCrystal(boxID, player, cancel, atoi(value.toCharArray()));
		break;*/
	case SuiWindowType::JUNK_DEALER_SELL_LIST:
		handleSellJunkLootSelection(boxID, player, cancel, value.toLowerCase() == "true", atoi(value2.toCharArray()));
		break;
	case SuiWindowType::STRUCTURE_STATUS:
		handleStructureStatus(boxID, player, cancel, atoi(value.toCharArray()));
		break;
	case SuiWindowType::STRUCTURE_DESTROY_CONFIRM:
		handleStructureDestroyConfirm(boxID, player, cancel, atoi(value.toCharArray()));
		break;
	case SuiWindowType::STRUCTURE_DESTROY_CODE:
		handleStructureDestroyCode(boxID, player, cancel, value);
		break;
	case SuiWindowType::STRUCTURE_MANAGE_MAINTENANCE:
		handleManageMaintenance(boxID, player, cancel, atoi(value.toCharArray()));
		break;
	case SuiWindowType::CONSENT:
		handleConsentBox(boxID, player, cancel, atoi(value.toCharArray()));
		break;
	case SuiWindowType::CLONE_REQUEST:
		handleCloneRequest(boxID, player, cancel, atoi(value.toCharArray()));
		break;/*
	case SuiWindowType::CLONE_CONFIRM:
		handleCloneConfirm(boxID, player, cancel, atoi(value.toCharArray()));
		break;
	case SuiWindowType::START_MUSIC:
		handleStartMusic(boxID, player, cancel, value.toCharArray(), false);
		break;
	case SuiWindowType::START_DANCING:
		handleStartDancing(boxID, player, cancel, value.toCharArray(), false);
		break;
	case SuiWindowType::CHANGE_MUSIC: // changemusic
		handleStartMusic(boxID, player, cancel, value.toCharArray(), true);
		break;
	case SuiWindowType::CHANGE_DANCING: // changedance
		handleStartDancing(boxID, player, cancel, value.toCharArray(), true);
		break;*/
	case SuiWindowType::SURVEY_TOOL_RANGE:
		range = (atoi(value.toCharArray()) * 64) + 64;
		if(range == 576)
			range = 1024;
		handleSurveyToolRange(boxID, player, cancel, range);
		break;
	case SuiWindowType::SAMPLERADIOACTIVECONFIRM:
		handleSampleRadioactiveConfirm(boxID, player, cancel, atoi(value.toCharArray()));
		break;
	case SuiWindowType::SURVEY_TOOL_CONCENTRATED_MINIGAME:
		handleSurveyConcentratedMinigame(boxID, player, cancel, atoi(value.toCharArray()));
		break;
	case SuiWindowType::SURVEY_TOOL_CONCENTRATED_MINIGAME2:
		handleSurveyConcentratedMinigame2(boxID, player, cancel, atoi(value.toCharArray()));
		break;
	/*case SuiWindowType::GUILD_CREATION_INPUT_FOR_TAG: // Guild creation InputBox #1 (Tag)
		returnString = value;
		pGuild->handleGuildTag(boxID, player, cancel, returnString);
		if (!cancel)
			pGuild->handleGuildName(boxID, player, cancel, returnString);
		break;
	case SuiWindowType::GUILD_CREATION_INPUT_FOR_NAME: // Guild creation InputBox #2 (name)
		returnString = value;
		pGuild->handleGuildName(boxID, player, cancel, returnString);
		break;
	case SuiWindowType::GUILD_SPONSORING_MEMBER_INPUT_FOR_NAME: // Guild Sponsoring Member InputBox (name)
		returnString = value;
		pGuild->handleGuildSponsor(boxID, player, cancel, returnString);
		break;
	case SuiWindowType::VERIFY_SPONSOR_TARGET_FOR_GUILD_MEMBERSHIP: // Verify Messagebox Guild Sponsoring Target
		pGuild->handleVerifyBoxSponsorTargetforGuildMembership(boxID, player, cancel);
		break;
	case SuiWindowType::SPONSORED_GUILD_MEMBERS: // Sponsored guild member box
		pGuild->handleSponsoredGuildMembersBox(boxID, player, cancel, atoi(value.toCharArray()));
		break;
	case SuiWindowType::SPONSORED_GUILD_MEMBERS_ACCEPT: // Sponsored guild member accept/decline box
		pGuild->handleSponsoredGuildMembersAcceptBox(boxID, player, cancel, atoi(value.toCharArray()));
		break;
	case SuiWindowType::GUILD_DISBAND: // Disband guild verify box
		returnString = value;
		pGuild->handleGuildDisbandBox(boxID, player, cancel, returnString);
		break;
	case SuiWindowType::GUILD_NAME_CHANGE: // Namechange guild (Tag box)
		returnString = value;
		pGuild->handleGuildNameChange(boxID, player, cancel, returnString);
		break;
	case SuiWindowType::GUILD_NAME_CHANGE_NAME: // Namechange guild (Tag box)
		returnString = value;
		pGuild->handleGuildNameChangeName(boxID, player, cancel, returnString);
		break;
	case SuiWindowType::GUILD_INFORMATION_MEMBERS: // Guild Information - Members
		pGuild->handleGuildInformationMembersBox(boxID, player, cancel, atoi(value.toCharArray()));
		break;
	case SuiWindowType::GUILD_MEMBER_OPTIONS: // Guild Information - Member options
		pGuild->handleGuildMemberOptions(boxID, player, cancel, atoi(value.toCharArray()));
		break;
	case SuiWindowType::GUILD_PERMISSION_SELECTION: // Guild member permissions
		pGuild->handleGuildPermissionSelection(boxID, player, cancel, atoi(value.toCharArray()));
		break;
	case SuiWindowType::REMOVE_FROM_GUILD: // Guild remove from guild exec
		pGuild->execRemoveFromGuild(boxID, player, cancel);
		break;
	case SuiWindowType::GUILD_TRANSFER_LEADER: // Guild Transfer-Leadership Name of Target SUI Box return
		returnString = value;
		pGuild->handleGuildTransferLeaderBox(boxID, player, cancel, returnString);
		break;
	case SuiWindowType::GUILD_TRANSFER_LEADER_VERIFY: // Guild Transfer-Leadership Accept/Decline Box Return
		pGuild->handleGuildTransferLeaderVerifyBox(boxID, player, cancel);
		break;
	case SuiWindowType::TICKET_PURCHASE_MESSAGE:
		handleTicketPurchaseMessageBox(boxID, player);
		break;*/
	case SuiWindowType::TICKET_COLLECTOR_RESPONSES:
		handleTicketCollectorRespones(boxID, player, cancel, atoi(value.toCharArray()));
		break;/*
	case SuiWindowType::COLOR_PICKER1:
		handleColorPicker(boxID, player, cancel, value, 2);
		break;
	case SuiWindowType::COLOR_PICKER2:
		handleColorPicker(boxID, player, cancel, value, 1);
		break;*/
	case SuiWindowType::BANK_TRANSFER:
		handleBankTransfer(boxID, player, atoi(value.toCharArray()), atoi(value2.toCharArray()));
		break;
	case SuiWindowType::FISHING:
		handleFishingAction(boxID, player, cancel, atoi(value.toCharArray()));
		break;
	case SuiWindowType::CHARACTERBUILDERITEMSELECT:
		handleCharacterBuilderSelectItem(boxID, player, cancel, atoi(value.toCharArray()));
		break;
	/*case SuiWindowType::BLUE_FROG_ITEM_REQUEST:
		handleBlueFrogItemRequest(boxID, player, cancel, atoi(value.toCharArray()));
		break;
	case SuiWindowType::WOUND_TERMINAL_REQUEST:
		handleWoundTerminalRequest(boxID, player, cancel, atoi(value.toCharArray()));
		break;
	case SuiWindowType::STATE_TERMINAL_REQUEST:
		handleStateTerminalRequest(boxID, player, cancel, atoi(value.toCharArray()));
		break;*/
	case SuiWindowType::DIAGNOSE:
		handleDiagnose(boxID, player);
		break;
	case SuiWindowType::FREE_RESOURCE:
		handleFreeResource(boxID, player, cancel, atoi(value.toCharArray()));
		break;
	case SuiWindowType::GIVE_FREE_RESOURCE:
		handleGiveFreeResource(boxID, player, cancel, atoi(value.toCharArray()));
		break;
	case SuiWindowType::TEACH_SKILL:
		handleTeachSkill(boxID, player, cancel);
		break;
	case SuiWindowType::TEACH_PLAYER:
		handleTeachPlayer(boxID, player, atoi(value.toCharArray()), cancel);
		break;
	/*case SuiWindowType::DENY_TRAINING_LIST:
		handleDenyTrainingList(boxID, player);
		break;*/
	case SuiWindowType::OBJECT_NAME:   // Set Object Name
		handleSetObjectName(boxID, player, cancel, value.toCharArray());
		break;
	case SuiWindowType::ADD_ENERGY:    // Add Energy
		handleAddEnergy(boxID, player, cancel, atoi(value.toCharArray()));
		break;
	/*case SuiWindowType::INSTALLATION_REDEED:    // Redeed Verification Prompt
		handleCodeForRedeed(boxID, player, cancel, value.toCharArray());
		break;
	case SuiWindowType::INSTALLATION_REDEED_CONFIRM:    // Re-Deed Confirm
		handleRedeedStructure(boxID, player, cancel, atoi(value.toCharArray()));
		break;
	case SuiWindowType::INSURANCE_MENU:
		handleInsuranceMenu(boxID, player, cancel, atoi(value.toCharArray()));
		break;
	case SuiWindowType::INSURE_ALL_CONFIRM:
		handleInsureAllConfirm(boxID, player, cancel);
		break;
	case SuiWindowType::BANK_TIP_CONFIRM:
		handleBankTipConfirm(boxID, player, cancel);
		break;
	case SuiWindowType::SLICING_MENU:
		handleSlicingMenu(boxID, player, cancel, atoi(value.toCharArray()));
		break;
	case SuiWindowType::RANGER_WHAT_TO_TRACK:
		handleRangerWhatToTrackBox(boxID, player, cancel, atoi(value.toCharArray()));
		break;
	case SuiWindowType::SET_MOTD:
		returnString = value;
		handleSetMOTD(boxID, player, cancel, returnString);
		break;*/
	case SuiWindowType::FACTORY_SCHEMATIC:
		handleInsertFactorySchem(boxID, player, cancel, value.toLowerCase() == "true", atoi(value2.toCharArray()));
		break;
	case SuiWindowType::CREATE_CITY_HALL_NAME:
		handleSetCityHallName(boxID, player, cancel, value);
		break;
	default:
		//Clean up players sui box:

		Locker _locker(player);

		if (player->hasSuiBox(boxID)) {
			ManagedReference<SuiBox*> sui = player->getSuiBox(boxID);

			player->removeSuiBox(boxID);
		}

	}
}
/*
void SuiManager::handleCodeForRedeed(uint32 boxID, Player* player,
		uint32 cancel, const String& extra) {
	try {
		player->wlock();

		if (!player->hasSuiBox(boxID)) {
			player->unlock();
			return;
		}

		SuiBox* sui = player->getSuiBox(boxID);

		if (sui->isListBox() && cancel != 1) {
			Zone * zone = player->getZone();

			ManagedReference<SceneObject*> scno = zone->lookupObject(player->getCurrentStructureID());

			InstallationObject * inso = (InstallationObject *) scno.get();

			if (inso != NULL) {
				try {
					inso->wlock(player);

					inso->handleStructureRedeedConfirm(player);

					inso->unlock();
				} catch (...) {
					inso->unlock();
				}
			}
		}

		player->removeSuiBox(boxID);

		sui->finalize();
		sui = NULL;

		player->unlock();
	} catch (Exception& e) {
		error("Exception in SuiManager::handleCodeForRedeed ");
		e.printStackTrace();

		player->unlock();
	} catch (...) {
		error("Unreported exception caught in SuiManager::handleCodeForRedeed");
		player->unlock();
	}
}

void SuiManager::handleRedeedStructure(uint32 boxID, Player* player,
		uint32 cancel, const int extra) {
	try {
		player->wlock();

		if (!player->hasSuiBox(boxID)) {
			player->unlock();
			return;
		}

		SuiBox* sui = player->getSuiBox(boxID);

		if (sui->isInputBox() && cancel != 1) {
			Zone * zone = player->getZone();

			ManagedReference<SceneObject*> scno = zone->lookupObject(player->getCurrentStructureID());

			InstallationObject * inso = (InstallationObject *) scno.get();

			if (scno != NULL && extra == inso->getDestroyCode()) {
				try {
					inso->wlock(player);

					inso->handleMakeDeed(player);

					inso->unlock();
				} catch (...) {
					inso->unlock();
				}
			} else {
				SuiMessageBox* wrongCode = new SuiMessageBox(player, 0x00);
				wrongCode->setPromptTitle("Star Wars Galaxies");
				wrongCode->setPromptText("You have entered an incorrect code.  You will"
						" have to issue the /destroyStructure again if you wish to continue.");
				player->addSuiBox(wrongCode);
				player->sendMessage(wrongCode->generateMessage());
			}

		}

		player->removeSuiBox(boxID);

		sui->finalize();

		player->unlock();
	} catch (Exception& e) {
		error("Exception in SuiManager::handleRedeedStructure ");
		e.printStackTrace();

		player->unlock();
	} catch (...) {
		error("Unreported exception caught in SuiManager::handleRedeedStructure");
		player->unlock();
	}
}

void SuiManager::handleRefreshStatusListBox(uint32 boxID, Player* player,
		uint32 cancel, const int extra) {
	try {
		player->wlock();

		if (!player->hasSuiBox(boxID)) {
			player->unlock();
			return;
		}

		SuiBox* sui = player->getSuiBox(boxID);

		if (sui->isListBox() && cancel != 1) {
			Zone * zone = player->getZone();

			ManagedReference<SceneObject*> scno = zone->lookupObject(player->getCurrentStructureID());

			InstallationObject * inso = (InstallationObject *) scno.get();

			if (inso != NULL) {
				inso->handleStructureStatus(player);
			}
		}

		player->removeSuiBox(boxID);

		sui->finalize();
		sui = NULL;

		player->unlock();
	} catch (Exception& e) {
		error("Exception in SuiManager::handleRefreshStatusListBox ");
		e.printStackTrace();

		player->unlock();
	} catch (...) {
		error("Unreported exception caught in SuiManager::handleRefreshStatusListBox");
		player->unlock();
	}
}*/

void SuiManager::handleSetObjectName(uint32 boxID, PlayerCreature* player,
		uint32 cancel, const String& name) {
	Locker _locker(player);

	if (!player->hasSuiBox(boxID)) {
		return;
	}

	ManagedReference<SuiBox*> sui = player->getSuiBox(boxID);

	if (sui->isInputBox() && cancel != 1) {
		SuiInputBox* inputBox = (SuiInputBox*) sui.get();

		Zone* zone = player->getZone();

		ManagedReference<SceneObject*> object = inputBox->getUsingObject();

		if (object != NULL)	{
			object->setCustomObjectName(name , true);
		}
	}

	player->removeSuiBox(boxID);
}

void SuiManager::handleManageMaintenance(uint32 boxID, PlayerCreature* player,
		uint32 cancel, const int newCashVal) {

	Locker _locker(player);

	if (!player->hasSuiBox(boxID)) {
		return;
	}

	ManagedReference<SuiBox*> sui = player->getSuiBox(boxID);

	player->removeSuiBox(boxID);

	if (!sui->isTransferBox() || cancel == 1) {
		return;
	}

	SuiTransferBox* transferBox = (SuiTransferBox*) sui.get();

	Zone* zone = player->getZone();

	ManagedReference<SceneObject*> usingObject = transferBox->getUsingObject();

	if (usingObject == NULL || !usingObject->isStructureObject())
		return;

	StructureObject* structureObject = (StructureObject*) usingObject.get();

	int currentCash = player->getCashCredits();

	if (newCashVal > currentCash || newCashVal < 0)
		return;

	try {
		structureObject->wlock(player);

		int maint = currentCash - newCashVal;

		structureObject->addMaintenance(maint);
		player->substractCashCredits(maint);

		ParameterizedStringId stringId("base_player", "prose_pay_success");
		stringId.setTT(structureObject->getObjectID());
		stringId.setDI(maint);

		/*StringBuffer report;
		report << "You successfully make a payment of " << maint << " to "
				<< inso->getCustomName().toString() << ".\n"
				<< "Maintenance is now at " << inso->getSurplusMaintenance() << " credits.";*/

		player->sendSystemMessage(stringId);
		structureObject->updateToDatabase();

		structureObject->unlock();
	} catch (...) {
		structureObject->unlock();
	}

	player->updateToDatabase();
}


void SuiManager::handleAddEnergy(uint32 boxID, PlayerCreature* player,
		uint32 cancel, const int newEnergyVal) {
	Locker locker(player);

	if (!player->hasSuiBox(boxID))
		return;

	ManagedReference<SuiBox*> sui = player->getSuiBox(boxID);
	player->removeSuiBox(boxID);

	if (sui == NULL || !sui->isTransferBox() || cancel == 1)
		return;

	SuiTransferBox* transferBox = (SuiTransferBox*) sui.get();

	ManagedReference<SceneObject*> usingObject = transferBox->getUsingObject();

	if (usingObject == NULL || !usingObject->isInstallationObject())
		return;

	InstallationObject* installation = (InstallationObject*) usingObject.get();

	ResourceManager* resourceManager = player->getZoneServer()->getResourceManager();

	try {
		installation->wlock(player);

		uint32 energyFromPlayer = resourceManager->getAvailablePowerFromPlayer(player);
		uint32 energy = energyFromPlayer - newEnergyVal;

		if (energy > energyFromPlayer) {
			installation->unlock();
			return;
		}

		installation->addPower(energy);
		resourceManager->removePowerFromPlayer(player, energy);

		ParameterizedStringId stringId("player_structure", "deposit_successful");
		stringId.setDI(energy);

		player->sendSystemMessage(stringId);

		stringId.setStringId("player_structure", "reserve_report");
		stringId.setDI(energy);

		player->sendSystemMessage(stringId);

		installation->updateToDatabase();

		installation->unlock();
	} catch (...) {
		installation->unlock();
	}

}

/*
void SuiManager::handleStartMusic(uint32 boxID, Player* player, uint32 cancel, const String& song, bool change) {
	try {
		player->wlock();

		if (!player->hasSuiBox(boxID)) {
			player->unlock();
			return;
		}

		SuiBox* sui = player->getSuiBox(boxID);

		if (cancel != 1)
			player->startPlayingMusic(song, change);

		player->removeSuiBox(boxID);

		sui->finalize();

		player->unlock();
	} catch (Exception& e) {
		StringBuffer msg;
		msg << "Exception in SuiManager::handleStartMusic " << e.getMessage();
		error(msg.toString());

		player->unlock();
	} catch (...) {
		error("Unreported exception caught in SuiManager::handleStartMusic(Player* player, const String& music)");
		player->unlock();
	}
}

void SuiManager::handleStartDancing(uint32 boxID, Player* player, uint32 cancel, const String& dance, bool change) {
	try {
		player->wlock();

		if (!player->hasSuiBox(boxID)) {
			player->unlock();
			return;
		}

		SuiBox* sui = player->getSuiBox(boxID);

		if (cancel != 1)
			player->startDancing(dance, change);

		player->removeSuiBox(boxID);

		sui->finalize();

		player->unlock();
	} catch (Exception& e) {
		StringBuffer msg;
		msg << "Exception in SuiManager::handleStartDancing " << e.getMessage();
		error(msg.toString());

		player->unlock();
	} catch (...) {
		error("Unreported exception caught in SuiManager::handleStartDancing(Player* player, const String& music)");
		player->unlock();
	}
}*/

void SuiManager::handleSurveyToolRange(uint32 boxID, PlayerCreature* player, uint32 cancel, int range) {

	Locker _locker(player);

	if (player->hasSuiBox(boxID)) {

		ManagedReference<SuiBox*> sui = player->getSuiBox(boxID);

		if (sui != NULL) {

			ManagedReference<SurveyTool* > surveyTool =  player->getSurveyTool();

			if(surveyTool != NULL) {
				Locker _locker2(surveyTool);
				surveyTool->setRange(range);
			}

			player->removeSuiBox(boxID, true);
		}
	}
}

void SuiManager::handleSampleRadioactiveConfirm(uint32 boxID, PlayerCreature* player, uint32 cancel, int value) {
	Locker _locker(player);

	if (player->hasSuiBox(boxID)) {

		ManagedReference<SuiBox*> sui = player->getSuiBox(boxID);

		if (sui != NULL) {

			ManagedReference<SurveyTool* > surveyTool =  player->getSurveyTool();

			if(surveyTool != NULL && cancel == 0) {
				Locker _locker2(surveyTool);
				surveyTool->consentRadioactiveSample(player);
			}

			player->removeSuiBox(boxID, true);
		}
	}
}

void SuiManager::handleSurveyConcentratedMinigame(uint32 boxID, PlayerCreature* player, uint32 cancel, int value) {
	Locker _locker(player);

	if (player->hasSuiBox(boxID)) {

		ManagedReference<SuiBox*> sui = player->getSuiBox(boxID);

		if (sui != NULL) {

			ManagedReference<SurveyTool* > surveyTool =  player->getSurveyTool();

			if(surveyTool != NULL && cancel == 0) {
				Locker _locker2(surveyTool);
				surveyTool->surveyCnodeMinigame(player, value);
			}

			player->removeSuiBox(boxID, true);
		}
	}
}

void SuiManager::handleSurveyConcentratedMinigame2(uint32 boxID, PlayerCreature* player, uint32 cancel, int value) {
	Locker _locker(player);

	if (player->hasSuiBox(boxID)) {

		ManagedReference<SuiBox*> sui = player->getSuiBox(boxID);

		if (sui != NULL) {

			ManagedReference<SurveyTool* > surveyTool =  player->getSurveyTool();

			if(surveyTool != NULL && cancel == 0) {
				Locker _locker2(surveyTool);
				surveyTool->surveyGnodeMinigame(player, value);
			}

			player->removeSuiBox(boxID, true);
		}
	}
}


/*void SuiManager::handleRepairWeapon(uint32 boxID, Player* player, uint32 cancel, int itemindex) {
	try {
		player->wlock();

		if (!player->hasSuiBox(boxID)) {
			player->unlock();
			return;
		}

		SuiBox* sui = player->getSuiBox(boxID);

		if (cancel != 1) {
			Inventory* inventory = player->getInventory();

			int weaponCount = 0;

			for (int i = 0; i < inventory->getContainerObjectsSize(); i++) {
				TangibleObject* item = (TangibleObject*) inventory->getObject(i);

				item->wlock();

				if (item->isWeapon()) {
					Weapon* weapon = (Weapon*) item;

					if (weaponCount == itemindex)
						weapon->repairItem(player);

					weaponCount++;
				}

				item->unlock();
			}
		}

		player->removeSuiBox(boxID);

		sui->finalize();

		player->unlock();
	} catch (Exception& e) {
		StringBuffer msg;
		msg << "Exception in SuiManager::handleRepairWeapon " << e.getMessage();
		error(msg.toString());

		player->unlock();
	} catch (...) {
		error("Unreported exception caught in SuiManager::handleRepairWeapon(uint32 boxID, Player* player, int itemindex)");
		player->unlock();
	}
}

void SuiManager::handleRepairArmor(uint32 boxID, Player* player, uint32 cancel, int itemindex) {
	try {
		player->wlock();

		if (!player->hasSuiBox(boxID)) {
			player->unlock();
			return;
		}

		SuiBox* sui = player->getSuiBox(boxID);

		if (cancel != 1) {
			Inventory* inventory = player->getInventory();

			int armorCount = 0;

			for (int i = 0; i < inventory->getContainerObjectsSize(); i++) {
				TangibleObject* item = (TangibleObject*) inventory->getObject(i);

				item->wlock();

				if (item->isArmor()) {
					Armor* armor = (Armor*) item;

					if (armorCount == itemindex)
						armor->repairItem(player);

					armorCount++;
				}

				item->unlock();
			}
		}

		player->removeSuiBox(boxID);

		sui->finalize();

		player->unlock();
	} catch (Exception& e) {
		StringBuffer msg;
		msg << "Exception in SuiManager::handleRepairArmor " << e.getMessage();
		error(msg.toString());

		player->unlock();
	} catch (...) {
		error("Unreported exception caught in SuiManager::handleRepairArmor(uint32 boxID, Player* player, int itemindex)");
		player->unlock();
	}
}

void SuiManager::handleTicketPurchaseMessageBox(uint32 boxID, Player* player) {
	try {
		player->wlock();

		if (!player->hasSuiBox(boxID)) {
			player->unlock();
			return;
		}

		SuiBox* sui = player->getSuiBox(boxID);

		player->removeSuiBox(boxID);

		sui->finalize();

		player->unlock();
	} catch (Exception& e) {
		StringBuffer msg;
		msg << "Exception in SuiManager::handleTicketPurchaseMessageBox " << e.getMessage();
		error(msg.toString());

		player->unlock();
	} catch (...) {
		error("Unreported exception caught in SuiManager::handleTicketPurchaseMessageBox");
		player->unlock();
	}
}

void SuiManager::handleBlueFrogItemRequest(uint32 boxID, Player* player, uint32 cancel, int itemIndex) {
	try {
		player->wlock();

		if (!player->hasSuiBox(boxID)) {
			player->unlock();
			return;
		}

		SuiBox* sui = player->getSuiBox(boxID);

		ItemManager * itemManager = player->getZone()->getZoneServer()->getItemManager();

		if (sui->isListBox() && cancel != 1) {
			SuiListBox* listBox = (SuiListBox*)sui;
			BlueFrogVector * bfVector = itemManager->getBFItemList();

			if (itemIndex >= 0 && itemIndex < bfVector->size()) {
				itemManager->giveBFItemSet(player, bfVector->get(itemIndex));
				player->sendSystemMessage("You received a " + bfVector->get(itemIndex));
			}
		}

		player->removeSuiBox(boxID);

		sui->finalize();

		player->unlock();
	} catch (Exception& e) {
		error("Exception in SuiManager::handleBlueFrogItemRequest ");
		e.printStackTrace();

		player->unlock();
	} catch (...) {
		error("Unreported exception caught in SuiManager::handleBlueFrogItemRequest");
		player->unlock();
	}

}

void SuiManager::handleWoundTerminalRequest(uint32 boxID, Player* player, uint32 cancel, int itemIndex) {
	try {
		player->wlock();

		if (!player->hasSuiBox(boxID)) {
			player->unlock();
			return;
		}

		SuiBox* sui = player->getSuiBox(boxID);

		if (sui->isListBox() && cancel != 1) {
			switch (itemIndex) {
			case 0:
				player->changeHealthWoundsBar(500);
				break;
			case 1:
				player->changeStrengthWoundsBar(500);
				break;
			case 2:
				player->changeConstitutionWoundsBar(500);
				break;
			case 3:
				player->changeActionWoundsBar(500);
				break;
			case 4:
				player->changeQuicknessWoundsBar(500);
				break;
			case 5:
				player->changeStaminaWoundsBar(500);
				break;
			case 6:
				player->changeMindWoundsBar(500);
				break;
			case 7:
				player->changeFocusWoundsBar(500);
				break;
			case 8:
				player->changeWillpowerWoundsBar(500);
				break;
			}
		}

		player->removeSuiBox(boxID);
		sui->finalize();

		player->unlock();
	} catch (Exception& e) {
		error("Exception in SuiManager::handleWoundTerminalRequest ");
		e.printStackTrace();

		player->unlock();
	} catch (...) {
		error("Unreported exception caught in SuiManager::handleWoundTerminalRequest");
		player->unlock();
	}

}

void SuiManager::handleStateTerminalRequest(uint32 boxID, Player* player, uint32 cancel, int itemIndex) {
	try {
		player->wlock();

		if (!player->hasSuiBox(boxID)) {
			player->unlock();
			return;
		}

		SuiBox* sui = player->getSuiBox(boxID);



		if (sui->isListBox() && cancel != 1) {
			switch (itemIndex) {
			case 0:
				player->addDotState(player,System::random(10000),CreatureState::ONFIRE, 50, CreatureAttribute::HEALTH, 60,50,0);
				break;
			case 1:
				player->addDotState(player,System::random(10000),CreatureState::DISEASED, 50, CreatureAttribute::HEALTH, 60,50,0);
				break;
			case 2:
				player->addDotState(player,System::random(10000),CreatureState::POISONED, 50, CreatureAttribute::HEALTH, 60,50,0);
				break;
			case 3:
				player->setDizziedState();
				break;
			case 4:
				player->setBlindedState();
				break;
			case 5:
				player->setIntimidatedState();
				break;
			case 6:
				player->setStunnedState();
				break;
			}

			player->updateStates();
			player->activateRecovery();
		}

		player->removeSuiBox(boxID);
		sui->finalize();

		player->unlock();
	} catch (Exception& e) {
		error("Exception in SuiManager::handleDOTTerminalRequest ");
		e.printStackTrace();

		player->unlock();
	} catch (...) {
		error("Unreported exception caught in SuiManager::handleDOTTerminalRequest");
		player->unlock();
	}

}*/

void SuiManager::handleTicketCollectorRespones(uint32 boxID, PlayerCreature* player, uint32 cancel, int ticketIndex) {
	try {
		player->wlock();

		if (!player->hasSuiBox(boxID)) {
			player->unlock();
			return;
		}

		SuiBox* sui = player->getSuiBox(boxID);

		if (sui->isListBox() && cancel != 1) {
			SuiListBox* listBox = (SuiListBox*)sui;

			uint64 ticketObjectID = listBox->getMenuObjectID(ticketIndex);

			if (ticketObjectID != 0) {
				SceneObject* inventory = player->getSlottedObject("inventory");
				SceneObject* invObj = inventory->getContainerObject(ticketObjectID);

				if (invObj != NULL && invObj->isTangibleObject()) {
					TangibleObject* object = (TangibleObject*) invObj;

					if (object->isTicketObject()) {
						TicketObject* ticket = (TicketObject*) object;

						ticket->handleObjectMenuSelect(player, 20);
					}
				}
			}
		}

		player->removeSuiBox(boxID);

		player->unlock();
	} catch (Exception& e) {
		error("Exception in SuiManager::handleTicketCollectorRespones ");
		e.printStackTrace();

		player->unlock();
	} catch (...) {
		error("Unreported exception caught in SuiManager::handleTicketCollectorRespones");
		player->unlock();
	}
}
/*
void SuiManager::handleColorPicker(uint32 boxID, Player* player, uint32 cancel, const String& value, int var) {
	try {
		player->wlock();

		if (!player->hasSuiBox(boxID)) {
			player->unlock();
			return;
		}

		SuiBox* sui = player->getSuiBox(boxID);

		if (sui->isColorPicker()) {
			SuiColorPicker* colorPicker = (SuiColorPicker*) sui;

			int val = atoi(value.toCharArray());

			if (val >= 0 && val < 144) {
				uint64 oID = colorPicker->getObjectID();

				SceneObject* obj = player->getInventoryItem(oID);

				if (obj != NULL && obj->isTangible()) {
					TangibleObject* tano = (TangibleObject*) obj;

					tano->wlock();

					tano->setCustomizationVariable(var, val);
					tano->setUpdated(true);

					TangibleObjectDeltaMessage3* delta = new TangibleObjectDeltaMessage3(tano);
					delta->updateCustomizationString();
					delta->close();

					tano->unlock();

					player->broadcastMessage(delta);
				}
			}

			if (var != 1) {
				SuiColorPicker* sui2 = new SuiColorPicker(player, colorPicker->getObjectID(), "private/index_color_0", SuiWindowType::COLOR_PICKER2);

				player->addSuiBox(sui2);
				player->sendMessage(sui2->generateMessage());
			}
		}

		player->removeSuiBox(boxID);

		sui->finalize();

		player->unlock();
	} catch (Exception& e) {
		StringBuffer msg;
		msg << "Exception in SuiManager::handleColorPicker" << e.getMessage();
		error(msg.toString());

		player->unlock();
	} catch (...) {
		error("Unreported exception caught in SuiManager::handleColorPicker");
		player->unlock();
	}
}
*/
void SuiManager::handleBankTransfer(uint32 boxID, PlayerCreature* player, int cash, int bank) {
	Locker _locker(player);

	if (!player->hasSuiBox(boxID)) {
		return;
	}

	ManagedReference<SuiBox*> sui = player->getSuiBox(boxID);

	player->removeSuiBox(boxID);

	if (!sui->isBankTransferBox()) {
		return;
	}

	SuiBankTransferBox* suiBank = (SuiBankTransferBox*) sui.get();
	ManagedReference<SceneObject*> bankObject = suiBank->getBank();

	if (bankObject == NULL) {
		return;
	}

	if (!player->isInRange(bankObject, 5)) {
		return;
	}

	uint32 currentCash = player->getCashCredits();
	uint32 currentBank = player->getBankCredits();

	if ((currentCash + currentBank) == ((uint32)cash + (uint32)bank)) {
		player->setCashCredits(cash);
		player->setBankCredits(bank);
	}

}

/*void SuiManager::handleGamblingRoulette(uint32 boxID, PlayerCreature* player, uint32 cancel, const String& value, const String& value2) {
	GamblingManager* manager = player->getZone()->getZoneServer()->getGamblingManager();
	if (cancel) {
		manager->leaveTerminal(player, 0);
	} else {
		manager->refreshRouletteMenu(player);
	}
}
void SuiManager::handleGamblingSlot(uint32 boxID, PlayerCreature* player, uint32 cancel, int value, const String& value2) {
	GamblingManager* manager = player->getZone()->getZoneServer()->getGamblingManager();

	if (cancel) {
		manager->leaveTerminal(player, 1);
	} else {
		manager->startGame(player, 1);
	}
}

void SuiManager::handleGamblingSlotPayout(uint32 boxID, PlayerCreature* player, uint32 cancel, const String& value, const String& value2) {
	if (player->hasSuiBox(boxID)) {
		player->sendMessage(player->getSuiBox(boxID)->generateCloseMessage());
		player->removeSuiBox(boxID);
	}
}

void SuiManager::handleGamblingStartSabacc(uint32 boxID, PlayerCreature* player, uint32 cancel, int index, const String& value2) {
	if (!cancel) {
		String sabacc[] = {"Bespin Standard", "Empress Teta Preferred", "Cloud City Casino", "Random Sabacc", "Bespin Standard Variety", "Random Sabacc Variety"};
		String game;
		if ((index >= 0) && (index < 4)) {
			game = sabacc[index];
		} else {
			game = "None";
		}
		player->sendSystemMessage("Start Game: " + game + " " + *value2);
	}
}


void SuiManager::handleGamblingSabacc(uint32 boxID, PlayerCreature* player, uint32 cancel, const String& value, const String& value2) {
	if (cancel) {
		if (player->hasSuiBox(boxID)) {
			SuiSlotMachineBox* suiTableBox = (SuiSlotMachineBox*)player->getSuiBox(boxID);
			uint32 tableBox = suiTableBox->getPayoutBoxID();
			if (player->hasSuiBox(tableBox)) {
				player->sendMessage(player->getSuiBox(tableBox)->generateCloseMessage());
				player->removeSuiBox(tableBox);
			}
			uint32 handBox = suiTableBox->getAnotherBoxID();
			if (player->hasSuiBox(handBox)) {
				player->sendMessage(player->getSuiBox(handBox)->generateCloseMessage());
				player->removeSuiBox(handBox);
			}
			player->sendMessage(player->getSuiBox(boxID)->generateCloseMessage());
			player->removeSuiBox(boxID);
		}
	}
}*/

void SuiManager::handleFishingAction(uint32 boxID, PlayerCreature* player, uint32 cancel, int index) {
	Locker _locker(player);

	//player->info("boxID: "+String::valueOf(boxID)+" Index: "+String::valueOf(index),true);
	if (player->hasSuiBox(boxID)) {
		ManagedReference<SuiBox*> sui = player->getSuiBox(boxID);
		if (sui != NULL) {
			FishingManager* manager = player->getZone()->getZoneServer()->getFishingManager();
			//Locker lockerManager(manager);
			manager->setNextAction(player,index + 1);
			uint32 newBoxID;
			switch (index+1) {
				case FishingManager::TUGUP:
					newBoxID = manager->createWindow(player,boxID);
					break;
				case FishingManager::TUGRIGHT:
					newBoxID = manager->createWindow(player,boxID);
					break;
				case FishingManager::TUGLEFT:
					newBoxID = manager->createWindow(player,boxID);
					break;
				case FishingManager::REEL:
					newBoxID = manager->createWindow(player,boxID);
					break;
				case FishingManager::STOPFISHING:
					player->sendSystemMessage("You give up and reel in your line!");
					manager->stopFishing(player, boxID, true);
					return;
					break;
				default:
					newBoxID = manager->createWindow(player,boxID);
					break;
			}
			manager->setFishBoxID(player,newBoxID);
		}
	}
}

void SuiManager::handleCharacterBuilderSelectItem(uint32 boxID, PlayerCreature* player, int cancel, int index) {
	Locker _locker(player);

	if (!player->hasSuiBox(boxID))
		return;

	ZoneServer* zserv = player->getZoneServer();

	ManagedReference<SuiBox*> sui = player->getSuiBox(boxID);

	if (!sui->isCharacterBuilderBox())
		return;

	ManagedReference<SuiCharacterBuilderBox*> cbSui = (SuiCharacterBuilderBox*) sui.get();

	CharacterBuilderMenuNode* currentNode = cbSui->getCurrentNode();

	//If cancel was pressed and there is no parent node to backup too, then we kill the box/menu.
	if (currentNode == NULL || (cancel > 0 && !currentNode->hasParentNode())) {
		player->removeSuiBox(boxID);
		return;
	}

	//Back was pressed. Send the node above it.
	if (cancel > 0) {
		CharacterBuilderMenuNode* parentNode = currentNode->getParentNode();
		cbSui->setCurrentNode(parentNode);
		cbSui->clearOptions();
		player->sendMessage(cbSui->generateMessage());
		return;
	}

	CharacterBuilderMenuNode* node = currentNode->getChildNodeAt(index);

	//Node doesn't exist or the index was out of bounds. Should probably resend the menu here.
	if (node == NULL) {
		player->removeSuiBox(boxID);
		return;
	}

	if (node->hasChildNodes()) {
		cbSui->setCurrentNode(node);
		cbSui->clearOptions();
		player->sendMessage(cbSui->generateMessage());
	} else {

		String templatePath = node->getTemplatePath();

		if (templatePath.indexOf(".iff") < 0) { // Non-item selections

			if (templatePath == "unlearn_all_skills") {

				player->sendSystemMessage("All skills unlearned.");
				server->getProfessionManager()->surrenderAll(player);

			} else if (templatePath == "cleanse_character") {

				if (!player->isInCombat()) {
					player->sendSystemMessage("You have been cleansed from the signs of previous battles.");

					for (int i=0; i<9; i++) {
						player->setWounds(i, 0);
					}

					player->setShockWounds(0);
				} else {
					player->sendSystemMessage("Not within combat.");
				}

			} else if (templatePath == "enhance_character") {

				SceneObject* scob = cbSui->getUsingObject();
				if (scob->getGameObjectType() == SceneObjectImplementation::CHARACTERBUILDERTERMINAL) {
					CharacterBuilderTerminal* bluefrog = (CharacterBuilderTerminal*) scob;
					bluefrog->enhanceCharacter(player);
				}

			} else if (templatePath == "credits") {

				player->addCashCredits(50000, true);
				player->sendSystemMessage("You have received 50.000 Credits");

			} else {

				if (templatePath.length() > 0) {

					server->getProfessionManager()->awardSkillBox(templatePath, player, true, true);
					if (player->hasSkillBox(templatePath))
						player->sendSystemMessage("You have learned a skill.");

				} else {

					player->sendSystemMessage("Unknown selection.");

				}
			}

			cbSui->clearOptions();
			player->sendMessage(cbSui->generateMessage());
		} else { // Items

			ManagedReference<SceneObject*> item = zserv->createObject(node->getTemplateCRC(), 1);

			if (item == NULL) {
				player->sendSystemMessage("There was an error creating the requested item. Please contact customer support with this issue.");
				cbSui->clearOptions();
				player->sendMessage(cbSui->generateMessage());
				return;
			}

			ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");
			item->sendTo(player, true);
			inventory->addObject(item, -1, true);

			ParameterizedStringId stringId;
			stringId.setStringId("@faction_perk:bonus_base_name"); //You received a: %TO.
			stringId.setTO(item);
			player->sendSystemMessage(stringId);

			cbSui->clearOptions();
			player->sendMessage(cbSui->generateMessage());
		}
	}
}
/*
void SuiManager::handleCloneConfirm(uint32 boxID, Player* player, uint32 cancel, int index) {
	try {
		player->wlock();

		if (!player->hasSuiBox(boxID)) {
			player->unlock();
			return;
		}

		SuiBox* sui = player->getSuiBox(boxID);

		if (sui != NULL && sui->isMessageBox() && cancel != 1) {
			CloningTerminal* terminal = NULL;
			SceneObject* scoTerminal = player->getZone()->lookupObject(sui->getUsingObjectID());

			if (scoTerminal != NULL) {
				TangibleObject* tanoTerminal = (TangibleObject*) scoTerminal;
				if (tanoTerminal->isTerminal()) {
					Terminal* termTerminal = (Terminal*) tanoTerminal;
					if (termTerminal->isCloningTerminal())
						terminal = (CloningTerminal*) termTerminal;
				}
			}

			if (terminal != NULL) {
				terminal->storeData(player);
			}
		}

		player->removeSuiBox(boxID);

		sui->finalize();

		player->unlock();
	} catch (...) {
		error("Unreported exception caught in SuiManager::handleCloneConfirm()");
		player->unlock();
	}
}
*/
void SuiManager::handleCloneRequest(uint32 boxID, PlayerCreature* player, uint32 cancel, int index) {
	Locker locker(player);

	if (!player->hasSuiBox(boxID)) {
		return;
	}

	info("activating sui cloner option", true);

	ZoneServer* zoneServer = server->getZoneServer();
	PlayerManager* playerManager = zoneServer->getPlayerManager();

	ManagedReference<SuiBox*> sui = player->getSuiBox(boxID);

	if (index >= 0) {
		if (!player->isDead()) {
			player->sendSystemMessage("You must be dead to activate your clone.");
		} else {
			SuiListBox* suiListBox = (SuiListBox*) sui.get();
			playerManager->sendPlayerToCloner(player, suiListBox->getMenuObjectID(index));
		}
	} else {
		if (player->isDead())
			player->sendSystemMessage("You will remain dead until you choose a location to clone or you are revived. Type /activateClone to restore the clone window.");
	}

	player->removeSuiBox(boxID);

}

void SuiManager::handleDiagnose(uint32 boxID, PlayerCreature* player) {
	Locker locker(player);

	if (!player->hasSuiBox(boxID)) {
		return;
	}

	//Reference<SuiBox*> sui = player->getSuiBox(boxID);

	player->removeSuiBox(boxID);
}

void SuiManager::handleFreeResource(uint32 boxID, PlayerCreature* player, uint32 cancel, int index) {
	/*Locker locker(player);

	if (player == NULL)
		return;

	if (!player->hasSuiBox(boxID))
		return;

	ManagedReference<SuiBox*> sui = player->getSuiBox(boxID);
	SuiListBox* suiListBox = (SuiListBox*) sui.get();
	if (suiListBox == NULL)
		return;

	String nodeName = suiListBox->getMenuItemName(index);

	int menuSize = suiListBox->getMenuSize();

	SceneObject* deedObject = suiListBox->getUsingObject();

	ManagedReference<ResourceManager*> resourceManager = server->getZoneServer()->getResourceManager();

	player->removeSuiBox(boxID);

	if (cancel) {

		String parent = resourceManager->getParent(nodeName);

		if (parent != "resource") {

			SuiListBox* sui = new SuiListBox(player, SuiWindowType::FREE_RESOURCE, SuiListBox::HANDLETWOBUTTON);

			sui->setPromptTitle("Resources");

			if (resourceManager->isType(parent))
				sui->setPromptText("Choose resource.");
			else
				sui->setPromptText("Choose resource class.");

			if (resourceMaresourceManager->getParent(parent) == "resource")
				sui->setCancelButton(true, "");
			else
				sui->setCancelButton(true, "Back");

			sui->setUsingObject(deedObject);

			player->addSuiBox(sui);
			resourceManager->addChildrenToListBox(nodeName, sui);

			player->sendMessage(sui->generateMessage());

		}

	} else {

		if (menuSize > index) {

			if (resourceManager->typeHasChildren(nodeName)) {

				SuiListBox* sui = new SuiListBox(player, SuiWindowType::FREE_RESOURCE, SuiListBox::HANDLETWOBUTTON);

				sui->setPromptTitle("Resources");
				sui->setPromptText("Choose resource class.");
				sui->setCancelButton(true, "Back");

				sui->setUsingObject(deedObject);

				player->addSuiBox(sui);
				resourceManager->addChildrenToListBox(nodeName, sui);

				player->sendMessage(sui->generateMessage());

			} else if (resourceManager->isType(nodeName)) {

				SuiListBox* sui = new SuiListBox(player, SuiWindowType::FREE_RESOURCE, SuiListBox::HANDLETWOBUTTON);

				sui->setPromptTitle("Resources");
				sui->setPromptText("Choose resource.");
				sui->setCancelButton(true, "Back");

				sui->setUsingObject(deedObject);

				player->addSuiBox(sui);
				resourceManager->addSpawnsToListBox(nodeName, sui);

				player->sendMessage(sui->generateMessage());

			} else {

				SuiListBox* sui = new SuiListBox(player, SuiWindowType::GIVE_FREE_RESOURCE, SuiListBox::HANDLETWOBUTTON);

				sui->setPromptTitle("Resource: " + nodeName);
				sui->setPromptText("Please confirm that you would like to select this resource as your Veteran Reward Crate of Resources. Use the BACK button to go back and select a different resource.");
				sui->setCancelButton(true, "Back");

				sui->setUsingObject(deedObject);

				player->addSuiBox(sui);
				resourceManager->resourceInfoToListBox(nodeName, sui);

				player->sendMessage(sui->generateMessage());

			}
		}
	}*/
}

void SuiManager::handleGiveFreeResource(uint32 boxID, PlayerCreature* player, uint32 cancel, int index) {
/*
	Locker locker(player);

	if (player == NULL)
		return;

	if (!player->hasSuiBox(boxID))
		return;

	ManagedReference<SuiBox*> sui = player->getSuiBox(boxID);
	SuiListBox* suiListBox = (SuiListBox*) sui.get();
	if (suiListBox == NULL)
		return;

	String nodeName = suiListBox->getMenuItemName(0);

	SceneObject* deedObject = suiListBox->getUsingObject();

	ManagedReference<ResourceManager*> resourceManager = server->getZoneServer()->getResourceManager();

	player->removeSuiBox(boxID);

	if (cancel) {

		String parent = resourceManager->getParent(nodeName);

		SuiListBox* sui = new SuiListBox(player, SuiWindowType::FREE_RESOURCE, SuiListBox::HANDLETWOBUTTON);

		sui->setPromptTitle("Resources");
		sui->setPromptText("Choose resource.");
		sui->setCancelButton(true, "Back");

		sui->setUsingObject(deedObject);

		player->addSuiBox(sui);
		resourceManager->addChildrenToListBox(nodeName, sui);

		player->sendMessage(sui->generateMessage());


	} else {

		resourceManager->givePlayerResource(player, nodeName, ResourceManagerImplementation::RESOURCE_DEED_QUANTITY);
		player->sendSystemMessage("You received 100k of resources.");

		if (deedObject->getGameObjectType() == SceneObjectImplementation::RESOURCEDEED) {
			ResourceDeed* deed = (ResourceDeed*) deedObject;

			Locker cLocker(deed, player);
			deed->destroyDeed();
		}
	}
*/
}

void SuiManager::handleConsentBox(uint32 boxID, PlayerCreature* player, uint32 cancel, int index) {
	Locker locker(player);

	if (!player->hasSuiBox(boxID)) {
		return;
	}

	ManagedReference<SuiBox*> sui = player->getSuiBox(boxID);

	if (sui != NULL && cancel != 1 && sui->isListBox()) {
		SuiListBox* suiList = (SuiListBox*) sui.get();

		if (index != -1) {
			String name = suiList->getMenuItemName(index);
			UnconsentCommand::unconscent(player, name);
		}
	}

	player->removeSuiBox(boxID);
}
/*
void SuiManager::handleDenyTrainingList(uint32 boxID, Player* player) {
        try {
               player->wlock();

               if (!player->hasSuiBox(boxID)) {
                       player->unlock();
                       return;
               }

               SuiBox* sui = player->getSuiBox(boxID);

               player->removeSuiBox(boxID);

	       sui->finalize();

       	       player->unlock();
       } catch (Exception& e) {
               error("Exception in SuiManager::handleDenyTrainingList ");
	       e.printStackTrace();
               player->unlock();
       } catch (...) {
               error("Unreported exception caught in SuiManager::handleDenyTrainingList");
               player->unlock();
       }
}
*/

void SuiManager::handleTeachPlayer(uint32 boxID, PlayerCreature* player, int value, uint32 cancel) {
	PlayerCreature* student = NULL;

	try {

		player->wlock();
		player->setTeachingOrLearning(false);

		if(!player->hasSuiBox(boxID)) {
			player->unlock();
			return;
		}

		ManagedReference<SuiBox*> sui = player->getSuiBox(boxID);
		player->removeSuiBox(boxID);

		if(!sui->isListBox() || sui->getWindowType() != 36) {
			player->unlock();
			return;
		}

		TeachPlayerListBox* listBox = (TeachPlayerListBox*) sui.get();

		student = listBox->getStudent();

		if (student == NULL) {
			player->unlock();
			return;
		}

		try {
			if (student != player)
				student->wlock(player);

			if ( cancel == 1 || value == -1 ) {

				if (student != player)
					student->unlock();

				player->unlock();
				return;
			}

			//if they are no longer in the same group we cancel
			if ( player->getGroup() == NULL || !player->getGroup()->hasMember(student) ) {

				player->sendSystemMessage("teaching","not_in_same_group");
				player->setTeachingOrLearning(false);

				if (student != player)
					student->unlock();

				player->unlock();
				return;
			}

			//student->setTeachingOffer(listBox->getTeachingSkillOption(value));

			ParameterizedStringId message("teaching","offer_given");
			message.setTT(student->getFirstName());
			message.setTO("skl_n", listBox->getTeachingSkillOption(value));
			player->sendSystemMessage(message);

			PlayerLearnListBox* mbox = new PlayerLearnListBox(student);

			student->setTeachingOrLearning(true);

			// TODO: redo this after I find the proper String
			StringBuffer prompt, skillname;
			skillname << "@skl_n:" << listBox->getTeachingSkillOption(value);
			prompt << "Do you wish to learn the following from " << player->getFirstName() << "?";
			mbox->setPromptTitle("@sui:teach");
			mbox->setPromptText(prompt.toString());
			mbox->addMenuItem(skillname.toString());
			mbox->setCancelButton(true, "");
			mbox->setTeacher(player);
			mbox->setTeachingOffer(listBox->getTeachingSkillOption(value));

			student->addSuiBox(mbox);
			student->sendMessage(mbox->generateMessage());

			if (student != player)
				student->unlock();

		} catch (...) {
			student->unlock();
		}

		player->unlock();
	} catch (Exception& e) {
		error("Exception in SuiManager::handleTeachPlayer");
	    	e.printStackTrace();

        	player->unlock();
	} catch (...) {
		error("Unreported exception caught in SuiManager::handleTeachPlayer");

        player->unlock();
	}
}

void SuiManager::handleTeachSkill(uint32 boxID, PlayerCreature* player, uint32 cancel) {
	try {
		player->wlock();
		player->setTeachingOrLearning(false);

		if(!player->hasSuiBox(boxID)) {
			player->unlock();
			return;
		}

		ManagedReference<SuiBox*> sui = player->getSuiBox(boxID);
		player->removeSuiBox(boxID);

		if(!sui->isListBox() || sui->getWindowType() != 35) {
			player->unlock();
			return;
		}

		PlayerLearnListBox* listBox = (PlayerLearnListBox*) sui.get();

		if (cancel != 1) {

			if (listBox->getTeacher() == NULL) {

				player->sendSystemMessage("teaching","teacher_too_far");
				//player->getTeacher()->sendSystemMessage("teaching","teaching_failed"); TEACHER IS NULL..
				//player->getTeacher()->clearTeachingSkillOptions();

			} else if (!player->isInRange(listBox->getTeacher(), 128)) {

				ParameterizedStringId message("teaching","teacher_too_far_target");
				message.setTT(listBox->getTeacher()->getObjectID());
				message.setTO("skl_n", listBox->getTeachingOffer());
				player->sendSystemMessage(message);

				listBox->getTeacher()->sendSystemMessage("teaching","teaching_failed");

			} else if ( player->getGroup() == NULL || !player->getGroup()->hasMember(listBox->getTeacher()) ) {

				ParameterizedStringId message("teaching","not_in_same_group");
				message.setTT(listBox->getTeacher()->getObjectID());
				player->sendSystemMessage(message);

				listBox->getTeacher()->sendSystemMessage("teaching","teaching_failed");

			} else
				server->getProfessionManager()->playerTeachSkill(listBox->getTeachingOffer(), player, listBox->getTeacher());
				//player->teachSkill(player->getTeachingOffer());

		} else {// if (listBox->getTeacher() != NULL){

			ParameterizedStringId message("teaching","offer_refused");
			message.setTT(player->getObjectID());
			message.setTO("skl_n", listBox->getTeachingOffer());
			listBox->getTeacher()->sendSystemMessage(message);

		}

		player->unlock();
	} catch (Exception& e) {
		error("Exception in SuiManager::handleTeachSkill");
		e.printStackTrace();
       		player->unlock();
	} catch (...) {
		error("Unreported exception caught in SuiManager::handleTeachSkill");
        	player->unlock();
	}
}
/*

void SuiManager::handleInsuranceMenu(uint32 boxID, Player* player, uint32 cancel, int index) {
	try {
		player->wlock();

		if (!player->hasSuiBox(boxID)) {
			player->unlock();
			return;
		}

		SuiBox* sui = player->getSuiBox(boxID);

		if (sui != NULL && sui->isListBox() && cancel != 1) {
			SuiListBox* suiList = (SuiListBox*) sui;
			uint64 oid = suiList->getMenuObjectID(index);

			uint64 terminalID = suiList->getUsingObjectID();

			InsuranceTerminal* terminal = NULL;
			SceneObject* scoTerminal = player->getZone()->lookupObject(terminalID);

			if (scoTerminal != NULL) {
				TangibleObject* tanoTerminal = (TangibleObject*) scoTerminal;
				if (tanoTerminal->isTerminal()) {
					Terminal* termTerminal = (Terminal*) tanoTerminal;
					if (termTerminal->isInsuranceTerminal())
						terminal = (InsuranceTerminal*) termTerminal;
				}
			}

			if (terminal != NULL)
				player->insureItem(terminal, oid);
			else
				player->onInsureItemInvalidTerminal();
		}

		player->removeSuiBox(boxID);

		sui->finalize();

		player->unlock();
	} catch (Exception& e) {
		error("Exception in SuiManager::handleInsuranceMenu ");
		e.printStackTrace();

		player->unlock();
	} catch (...) {
		error("Unreported exception caught in SuiManager::handleInsuranceMenu");
		player->unlock();
	}
}


void SuiManager::handleInsureAllConfirm(uint32 boxID, Player* player, uint32 cancel) {
	try {
		player->wlock();

		if (!player->hasSuiBox(boxID)) {
			player->unlock();
			return;
		}

		SuiBox* sui = player->getSuiBox(boxID);

		if (sui != NULL && cancel != 1)
			player->insureAllItems(sui->getUsingObjectID());

		player->removeSuiBox(boxID);

		sui->finalize();

		player->unlock();
	} catch (Exception& e) {
		error("Exception in SuiManager::handleInsureAllConfirm ");
		e.printStackTrace();

		player->unlock();
	} catch (...) {
		error("Unreported exception caught in SuiManager::handleInsureAllConfirm");
		player->unlock();
	}
}

void SuiManager::handleBankTipConfirm(uint32 boxID, Player* player, uint32 cancel) {
	try {
		player->wlock();

		if (!player->hasSuiBox(boxID)) {
			player->unlock();
			return;
		}

		SuiBox* sui = player->getSuiBox(boxID);

		if (sui != NULL && sui->isMessageBox() && cancel != 1) {
			SuiBankTipConfirmBox* bankTip = (SuiBankTipConfirmBox*) sui;

			Player* recipient = bankTip->getRecipient();
			int32 amount = bankTip->getTipAmount();

			recipient->wlock(player);

			player->bankTipFinish(recipient, amount);

			recipient->unlock();
		}

		player->removeSuiBox(boxID);

		sui->finalize();

		player->unlock();
	} catch (Exception& e) {
		error("Exception in SuiManager::handleBankTipConfirm ");
		e.printStackTrace();

		player->unlock();
	} catch (...) {
		error("Unreported exception caught in SuiManager::handleBankTipConfirm");
		player->unlock();
	}
}



void SuiManager::handleSlicingMenu(uint32 boxid, Player* player, uint32 cancel, int index) {
	try {
		player->wlock();

		SuiBox* suibox = player->getSuiBox(boxid);

		//Make sure the box exists.
		if (suibox == NULL) {
			player->unlock();
			return;
		}

		//Make sure the suibox is a slicing box and that it was not cancelled.
		if (suibox->isSlicingBox()) {
			SuiSlicingBox* slicingbox = (SuiSlicingBox*) suibox;

			//If the user didn't hit cancel, then we want to handle the option selected.
			if (cancel != 1 && index > -1) {

				//Handle the last selected index. Make sure that it hasn't been completed.
				if (slicingbox->getProgress() != 2 && slicingbox->getProgress() != -1) {
					slicingbox->handleSelection(index);

					player->sendMessage(slicingbox->generateMessage());
					player->unlock();
					return;
				}
			}

			//Reset the item to have no slicer id set.
			TangibleObject* item = slicingbox->getSlicingObject();

			if (item != NULL)
				item->setSlicerID(0);
		}

		//Since we are done with the box, remove it from the player and finalize it.
		player->removeSuiBox(boxid);
		suibox->finalize();

		player->unlock();
	} catch (Exception& e) {
		error("Exception in SuiManager::handleSlicingMenu");
		e.printStackTrace();

		player->unlock();
	} catch (...) {
		error("Unreported exception caught in SuiManager::handleSlicingMenu");
		player->unlock();
	}
}

void SuiManager::handleRangerWhatToTrackBox(uint32 boxID, Player* player, uint32 cancel, int index) {
	try {
		player->wlock();

		if (!player->hasSuiBox(boxID)) {
			player->unlock();
			return;
		}

		SuiBox* sui = player->getSuiBox(boxID);

		player->removeSuiBox(boxID);

		sui->finalize();

		if(cancel != 1) {
				player->doEmote(0, 72, false); // 72 is "/combarea" emote

			if(server != NULL) {
				AreaTrackEvent* ate = new AreaTrackEvent(player, 5000, index);
				server->addEvent(ate);
			}
		}

		player->unlock();
	} catch (Exception& e) {
		error("Exception in SuiManager::handleInsuranceMenu ");
		e.printStackTrace();

		player->unlock();
	} catch (...) {
		error("Unreported exception caught in SuiManager::handleInsuranceMenu");
		player->unlock();
	}
}

void SuiManager::handleSetMOTD(uint32 boxID, Player* player, uint32 cancel, const String& returnString) {
	try {
		player->wlock();

		if (!player->hasSuiBox(boxID)) {
			player->unlock();
			return;
		}

		SuiBox* sui = player->getSuiBox(boxID);

		player->removeSuiBox(boxID);

		sui->finalize();

		if(cancel != 1) {
			if(server != NULL) {
				ZoneServer* zone = server->getZoneServer();
				if(returnString.length() <= 1024)
					zone->changeMessageoftheDay(returnString);
				else
					player->sendSystemMessage("Message exceeded character limit!");
			}
		}

		player->unlock();
	} catch (Exception& e) {
		error("Exception in SuiManager::handleSetMOTD ");
		e.printStackTrace();

		player->unlock();
	} catch (...) {
		error("Unreported exception caught in SuiManager::handleSetMOTD");
		player->unlock();
	}
}
*/
void SuiManager::handleInsertFactorySchem(uint32 boxID, PlayerCreature* player, uint32 cancel, bool otherPressed, int index) {

	Locker _locker(player);

	if (player->hasSuiBox(boxID)) {

		ManagedReference<SuiListBox*> sui = (SuiListBox*) player->getSuiBox(boxID);

		/// Cancel = Remove
		if (sui != NULL) {

			if(cancel != 1) {

				ManagedReference<FactoryObject* > factory =  (FactoryObject*) server->getZoneServer()->getObject(sui->getUsingObjectID());

					if(factory != NULL && factory->isFactory()) {

					Locker _locker2(factory);

					factory->handleRemoveFactorySchem(player);

					if(!otherPressed) {
						ManagedReference<ManufactureSchematic* > schematic = (ManufactureSchematic*) server->getZoneServer()->getObject(sui->getMenuObjectID(index));
						factory->handleInsertFactorySchem(player, schematic);
					}
				}
			}
			player->removeSuiBox(boxID, true);
			return;
		}
	}
}
/*
void SuiManager::handleTuneCrystal(uint32 boxID, Player* player, uint32 cancel) {
	try {
		player->wlock();

		if (!player->hasSuiBox(boxID)) {
			player->unlock();
			return;
		}

		SuiMessageBox* sui = (SuiMessageBox*) player->getSuiBox(boxID);

		if(cancel != 1) {
			SceneObject* object = player->getZone()->lookupObject(sui->getUsingObjectID());

			if (object->isTangible() && ((TangibleObject*)object)->getObjectSubType() == TangibleObjectImplementation::LIGHTSABERCRYSTAL) {
				LightsaberCrystalComponent* crystal = (LightsaberCrystalComponent*) object;
				crystal->tune(player);
			}
		}


		player->removeSuiBox(boxID);
		sui->finalize();
		player->unlock();

	} catch (Exception& e) {
		error("Exception in SuiManager::handleTuneCrystal");
		player->unlock();
	} catch (...) {
		error("Unreported exception caught in SuiManager::handleTuneCrystal");
		player->unlock();
	}
}

void SuiManager::handleChangeColorCrystal(uint32 boxID, Player* player, uint32 cancel, int itemindex) {
	try {
		player->wlock();

		if (!player->hasSuiBox(boxID)) {
			player->unlock();
			return;
		}

		SuiListBox* sui = (SuiListBox*) player->getSuiBox(boxID);

		if (cancel != 1) {
			SceneObject* object = player->getZone()->lookupObject(
					sui->getUsingObjectID());
			if (object != NULL && object->isTangible() && ((TangibleObject*) object)->getObjectSubType()
					& TangibleObjectImplementation::LIGHTSABER) {

				JediWeapon* saber = (JediWeapon*) object;

				Inventory* inventory = player->getInventory();

				int crystalCount = 0;

				for (int i = 0; i < inventory->getContainerObjectsSize(); i++) {
					TangibleObject* item =
							(TangibleObject*) inventory->getObject(i);

					item->wlock();

					if (item->isLightsaberCrystal()) {
						LightsaberCrystalComponent* crystal = (LightsaberCrystalComponent*) item;

						if (crystal->isColorCrystal()) {

							if (crystalCount == itemindex) {

								if (saber->hasColorCrystal()) {
									int color = crystal->getColor();
									crystal->setColor(saber->getBladeColor());
									saber->setBladeColor(color);

									TangibleObjectDeltaMessage3* dtano3 = new TangibleObjectDeltaMessage3(saber);
									dtano3->updateCustomizationString();
									dtano3->close();
									player->sendMessage(dtano3);

									dtano3 = new TangibleObjectDeltaMessage3(crystal);
									dtano3->updateCustomizationString();
									dtano3->close();
									player->sendMessage(dtano3);
								} else {
									saber->setBladeColor(crystal->getColor());
									crystal->sendDestroyTo(player);
									player->removeInventoryItem(crystal);
									player->getZoneProcessServer()->getItemManager()->deletePlayerItem(player, crystal, false);
									crystal->finalize();

									TangibleObjectDeltaMessage3* dtano3 = new TangibleObjectDeltaMessage3(saber);
									dtano3->updateCustomizationString();
									dtano3->close();
									player->sendMessage(dtano3);
								}
								saber->generateAttributes(player);
								item->unlock();
								break;
							}
							crystalCount++;
						}
					}

					item->unlock();
				}
			}
		}


		player->removeSuiBox(boxID);
		sui->finalize();
		player->unlock();

	} catch (Exception& e) {
		error("Exception in SuiManager::handleTuneCrystal");
		player->unlock();
	} catch (...) {
		error("Unreported exception caught in SuiManager::handleTuneCrystal");
		player->unlock();
	}
}
*/
void SuiManager::handleSellJunkLootSelection(uint32 boxid, PlayerCreature* player, uint32 cancel, bool otherPressed, int index) {
	if (otherPressed)
		info("Sell All",true);
	else if (cancel == 0)
		info("Sell",true);

	//player->sendSystemMessage("Index: " + String::valueOf(index) + " Cancel: " + String::valueOf(cancel) + " Other: " + String::valueOf(otherPressed));
	/*try {
		player->wlock();

		SuiListBox* listbox = (SuiListBox*) player->getSuiBox(boxid);

		if (listbox == NULL) {
			player->unlock();
			return;
		}

		if (cancel != 1 && index != -1) {
			Zone* zone = player->getZone();

			if (zone == NULL || zone->getZoneServer() == NULL) {
				player->removeSuiBox(boxid);
				listbox->finalize();
				player->unlock();
				return;
			}

			ZoneServer* zoneserver = zone->getZoneServer();

			ItemManager* itemmanager = zoneserver->getItemManager();

			if (itemmanager == NULL) {
				player->removeSuiBox(boxid);
				listbox->finalize();
				player->unlock();
				return;
			}

			uint64 junkdealerid = listbox->getUsingObjectID();
			JunkDealer* junkdealer = (JunkDealer*) zone->lookupObject(junkdealerid);

			if (junkdealer == NULL) {
				player->sendSystemMessage("An error has occurred, preventing you from selling your junk to the junk dealer.");
				player->removeSuiBox(boxid);
				listbox->finalize();
				player->unlock();
				return;
			}

			uint64 itemid = listbox->getMenuObjectID(index);
			TangibleObject* item = (TangibleObject*) player->getInventoryItem(itemid);

			if (item == NULL) {
				player->sendSystemMessage("An error has occurred, preventing you from selling your junk to the junk dealer.");
				player->removeSuiBox(boxid);
				listbox->finalize();
				player->unlock();
				return;
			}

			int lootvalue = item->getLootValue();

			if (lootvalue <= 0) {
				StfParameter* params = new StfParameter();
				params->addTU(junkdealerid);
				params->addTT(itemid);
				player->sendSystemMessage("junk_dealer", "prose_no_buy", params); //%TU shows no interest in purchasing %TT.
				delete params;

				player->removeSuiBox(boxid);
				listbox->finalize();
				player->unlock();
				return;
			}

			player->removeInventoryItem(itemid);
			item->sendDestroyTo(player);
			itemmanager->deletePlayerItem(player, item, false);
			item->finalize();

			player->addCashCredits(lootvalue);

			StfParameter* params = new StfParameter();
			params->addTT(itemid);
			params->addDI(lootvalue);
			player->sendSystemMessage("junk_dealer", "prose_sold_junk", params);
			delete params;

			//Send the list again.
			junkdealer->sendSellJunkListTo(player);
		}

		player->removeSuiBox(boxid);
		listbox->finalize();
		player->unlock();
	} catch (...) {
		error("Unreported exception caught in SuiManager::handleSellJunkLootSelection");
		player->unlock();
	}*/
}
/*
void SuiManager::handleBanListSelection(uint32 boxid, Player* player, uint32 cancel, int index) {
	try {
		player->wlock();

		SuiListBox* listbox = (SuiListBox*) player->getSuiBox(boxid);

		if (listbox == NULL) {
			player->unlock();
			return;
		}

		if (cancel != 1 && index != -1) {
			Zone* zone = player->getZone();

			if (zone != NULL) {
				ZoneServer* zserv = zone->getZoneServer();

				if (zserv != NULL) {
					String menutext = listbox->getMenuItemName(index);
					String username = menutext.subString(9, menutext.indexOf("-") - 1);

					GMCommand* command = GameCommandHandler::getCommand("unban");

					if (command != NULL) {
						StringTokenizer tokenizer(username);

						if (player->getAdminLevel() & command->getRequiredAdminLevel())
							command->exec(tokenizer, player);
						else
							player->sendSystemMessage("You don't have permission to execute this command.");
					}
				}
			}
		}

		player->removeSuiBox(boxid);
		listbox->finalize();

		player->unlock();
	} catch (...) {
		error("Unreported exception caught in SuiManager::handleBanListSelection");
		player->unlock();
	}
}


void SuiManager::handleCommandsListSelection(uint32 boxid, Player* player, uint32 cancel, int index) {
	try {
		player->wlock();

		SuiListBox* listbox = (SuiListBox*) player->getSuiBox(boxid);

		if (listbox == NULL) {
			player->unlock();
			return;
		}

		if (cancel != 1 && index != -1) {
			Zone* zone = player->getZone();

			if (zone != NULL) {
				ZoneServer* zserv = zone->getZoneServer();

				if (zserv != NULL) {
					player->sendSystemMessage("Command syntax would be shown here.");
				}
			}
		}

		player->removeSuiBox(boxid);
		listbox->finalize();

		player->unlock();
	} catch (...) {
		error("Unreported exception caught in SuiManager::handleCommandsListSelection.");
		player->unlock();
	}
}

void SuiManager::handleAccountListSelection(uint32 boxid, Player* player, uint32 cancel, int index) {
	try {
		player->wlock();

		SuiListBox* listbox = (SuiListBox*) player->getSuiBox(boxid);

		if (listbox == NULL) {
			player->unlock();
			return;
		}

		if (cancel != 1 && index != -1) {
			Zone* zone = player->getZone();

			if (zone != NULL) {
				ZoneServer* zserv = zone->getZoneServer();

				if (zserv != NULL) {
					String menutext = listbox->getMenuItemName(index);

					if (!menutext.isEmpty()) {
						String firstname = menutext.subString(0, menutext.indexOf(" "));

						GMCommand* command = GameCommandHandler::getCommand("getplayerinfo");

						StringTokenizer tokenizer(firstname);

						if (command != NULL && player->getAdminLevel() & command->getRequiredAdminLevel())
							command->exec(tokenizer, player);
						else
							player->sendSystemMessage("You don't have permission to execute this command.");
					}
				}
			}
		}

		player->removeSuiBox(boxid);
		listbox->finalize();

		player->unlock();
	} catch (...) {
		error("Unreported exception caught in SuiManager::handleAccountListSelection.");
		player->unlock();
	}
}

void SuiManager::handleCharacterListSelection(uint32 boxid, Player* player, uint32 cancel, int index) {
	try {
		player->wlock();

		SuiListBox* listbox = (SuiListBox*) player->getSuiBox(boxid);

		if (listbox == NULL) {
			player->unlock();
			return;
		}

		if (cancel != 1 && index != -1) {
			Zone* zone = player->getZone();

			if (zone != NULL) {
				ZoneServer* zserv = zone->getZoneServer();

				Player* targetplayer = (Player*) zone->lookupObject(listbox->getUsingObjectID());

				if (targetplayer != NULL && zserv != NULL) {
					String targetname = targetplayer->getFirstName();

					GMCommand* command = NULL;
					String arguments;
					bool closebox = false;

					int choice = listbox->getMenuObjectID(index);

					switch (choice) {
					case 0: //Lookup account details
					{
						command = GameCommandHandler::getCommand("getaccountinfo");
						arguments = targetname;
						closebox = true;
						break;
					}
					case 1: //Summon
					{
						command = GameCommandHandler::getCommand("summon");
						arguments = targetname;
						break;
					}
					case 2: //Warp to
					{
						command = GameCommandHandler::getCommand("warpto");
						arguments = targetname;
						closebox = true;
						break;
					}
					case 3: //Save
					{
						command = GameCommandHandler::getCommand("saveplayer");
						arguments = targetname;
						break;
					}
					case 4: //Resuscitate
					{
						command = GameCommandHandler::getCommand("rez");
						arguments = targetname;
						break;
					}
					case 5: //Heal all
					{
						command = GameCommandHandler::getCommand("heal");
						arguments = targetname;
						break;
					}
					case 6: //Buff
					{
						command = GameCommandHandler::getCommand("buff");
						arguments = "2000" + targetname;
						break;
					}
					case 7: //Mind Buff
					{
						command = GameCommandHandler::getCommand("mindbuff");
						arguments = "1000" + targetname;
						break;
					}
					case 8: //Open Inventory
					{
						command = GameCommandHandler::getCommand("openinventory");
						arguments = targetname;
						break;
					}
					case 9: //Open Bank
					{
						command = GameCommandHandler::getCommand("openbankinventory");
						arguments = targetname;
						break;
					}
					case 10: //Mute
					{
						command = GameCommandHandler::getCommand("muteplayer");
						arguments = targetname;
						break;
					}
					case 11: //Freeze
					{
						command = GameCommandHandler::getCommand("freeze");
						arguments = targetname;
						break;
					}
					case 12: //Punish - Jail Cell A
					{
						command = GameCommandHandler::getCommand("warpplayer");
						arguments = "125.3 -74.3 1 8575753 " + targetname;
						break;
					}
					case 13: //Punish - Jail Cell B
					{
						command = GameCommandHandler::getCommand("warpplayer");
						arguments = "130 -33.7 1 8575754 " + targetname;
						break;
					}
					case 14: //Punish - Space
					{
						command = GameCommandHandler::getCommand("warpplayer");
						arguments = "0 0 10 0 " + targetname;
						break;
					}
					case 15: //Kill
					{
						command = GameCommandHandler::getCommand("kill");
						arguments = targetname;
						break;
					}
					case 16: //Kick
					{
						command = GameCommandHandler::getCommand("kick");
						arguments = targetname;
						break;
					}
					case 17: //Ban
					{
						command = GameCommandHandler::getCommand("ban");
						arguments = targetname;
						break;
					}
					default:
						player->sendSystemMessage("Unknown menu selection.");
						break;
					}

					if (command != NULL) {
						StringTokenizer tokenizer(arguments);

						if (command->getRequiredAdminLevel() & player->getAdminLevel())
							command->exec(tokenizer, player);
						else
							player->sendSystemMessage("You don't have permission to execute that command.");

						//Resend the menu again until they decide they don't need it. - TODO: Make this box it's own class and make it update on each send.
						if (!closebox) {
							if (listbox->hasGeneratedMessage())
								listbox->clearOptions();

							player->sendMessage(listbox->generateMessage());
							player->unlock();
							return;
						}
					}
				}
			}
		}

		player->removeSuiBox(boxid);
		listbox->finalize();

		player->unlock();
	} catch (...) {
		error("Unreported exception caught in SuiManager::handleCharacterListSelection.");
		player->unlock();
	}
}
*/

void SuiManager::handleStructureStatus(uint32 boxID, PlayerCreature* player, uint32 cancel, int value) {

}

void SuiManager::handleStructureDestroyConfirm(uint32 boxID, PlayerCreature* player, uint32 cancel, int value) {
	Locker locker(player);

	if (!player->hasSuiBox(boxID))
		return;

	ManagedReference<SuiBox*> box = player->getSuiBox(boxID);

	player->removeSuiBox(boxID);

	if (!box->isListBox())
		return;

	SuiListBox* listBox = (SuiListBox*) box.get();

	ManagedReference<SceneObject*> usingObject = listBox->getUsingObject();

	if (usingObject == NULL || !usingObject->isStructureObject())
		return;

	StructureObject* structureObject = (StructureObject*) usingObject.get();

	Locker structureLocker(structureObject, player);

	structureObject->sendDestroyCodeTo(player);
}

void SuiManager::handleStructureDestroyCode(uint32 boxID, PlayerCreature* player, uint32 cancel, const String& input) {
	Locker locker(player);

	if (!player->hasSuiBox(boxID))
		return;

	ManagedReference<SuiBox*> box = player->getSuiBox(boxID);

	player->removeSuiBox(boxID);

	if (!box->isInputBox())
		return;

	SuiInputBox* inputBox = (SuiInputBox*) box.get();

	ManagedReference<SceneObject*> usingObject = inputBox->getUsingObject();

	if (usingObject == NULL || !usingObject->isStructureObject())
		return;

	ManagedReference<StructureObject*> structureObject = (StructureObject*) usingObject.get();

	Zone* zone = structureObject->getZone();

	if (zone == NULL)
		return;

	PlanetManager* planetManager = zone->getPlanetManager();

	if (planetManager == NULL)
		return;

	StructureManager* structureManager = planetManager->getStructureManager();

	if (structureManager == NULL)
		return;

	Locker structureLocker(structureObject, player);

	if (structureObject->getDestroyCode() == Integer::valueOf(input)) {
		structureManager->redeedStructure(player, structureObject);
	} else {
		player->sendSystemMessage("@player_structure:incorrect_destroy_code"); //You have entered an incorrect code. You will have to issue the /destroyStructure again if you wish to continue.
		return;
	}
}

void SuiManager::handleSetCityHallName(int boxID, PlayerCreature* player, int cancel, const String& input) {
	Locker locker(player);

	if (!player->hasSuiBox(boxID))
		return;

	ManagedReference<SuiBox*> box = player->getSuiBox(boxID);

	player->removeSuiBox(boxID);

	if (!box->isInputBox())
		return;

	SuiInputBox* inputBox = (SuiInputBox*) box.get();

	ManagedReference<SceneObject*> usingObject = inputBox->getUsingObject();

	if (usingObject == NULL)
		return;

	if (!usingObject->isBuildingObject())
		return;

	BuildingObject* building = (BuildingObject*) usingObject.get();

	if (!building->isCityHallBuilding())
		return;

	CityHallObject* cityHall = (CityHallObject*) building;

	Locker clocker(cityHall, player);

	cityHall->trySetCityName(player, input);
}
