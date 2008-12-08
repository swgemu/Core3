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

#include "engine/orb/DistributedObjectBroker.h"

#include "../../objects/player/sui/messagebox/SuiMessageBox.h"
#include "../../objects/player/sui/colorpicker/SuiColorPicker.h"

#include "../radial/RadialManager.h"

#include "../../ZoneProcessServerImplementation.h"
#include "../../objects.h"

#include "../item/ItemManager.h"
#include "../../objects/creature/bluefrog/BlueFrogVector.h"

#include "../../../login/packets/ErrorMessage.h"

#include "../../objects/tangible/deed/resourcedeed/ResourceDeedImplementation.h"
#include "../../objects/tangible/deed/resourcedeed/ResourceDeed.h"

#include "../resource/ResourceManagerImplementation.h"

SuiManager::SuiManager(ZoneProcessServerImplementation* serv) : Logger("SuiManager") {
	server = serv;

	setGlobalLogging(true);
	setLogging(false);
}

void SuiManager::handleSuiEventNotification(uint32 boxID, Player* player, uint32 cancel, const String& value, const String& value2) {
	uint16 type = (uint16) boxID;
	int range;
	String returnString;

	GuildManager* pGuild = server->getGuildManager();

	switch (type) {
	case 0xC057:
		handleConsentBox(boxID, player, cancel, atoi(value.toCharArray()));
		break;
	case 0xC103:
		handleCloneRequest(boxID, player, cancel, atoi(value.toCharArray()));
		break;
	case 0x5553:
		handleStartMusic(boxID, player, cancel, value.toCharArray(), false);
		break;
	case 0x414E:
		handleStartDancing(boxID, player, cancel, value.toCharArray(), false);
		break;
	case 0x5A53: // changemusic
		handleStartMusic(boxID, player, cancel, value.toCharArray(), true);
		break;
	case 0x4B4E: // changedance
		handleStartDancing(boxID, player, cancel, value.toCharArray(), true);
		break;
	case 0x7259:
		range = (atoi(value.toCharArray()) * 64) + 64;
		handleSurveyToolRange(boxID, player, cancel, range);
		break;
	case 0x7270: // Guild creation InputBox #1 (Tag)
		returnString = value;
		pGuild->handleGuildTag(boxID, player, cancel, returnString);
		if (!cancel)
			pGuild->handleGuildName(boxID, player, cancel, returnString);
		break;
	case 0x7271: // Guild creation InputBox #2 (name)
		returnString = value;
		pGuild->handleGuildName(boxID, player, cancel, returnString);
		break;
	case 0x7272: // Guild Sponsoring Member InputBox (name)
		returnString = value;
		pGuild->handleGuildSponsor(boxID, player, cancel, returnString);
		break;
	case 0x7273: // Verify Messagebox Guild Sponsoring Target
		pGuild->handleVerifyBoxSponsorTargetforGuildMembership(boxID, player, cancel);
		break;
	case 0x7274: // Sponsored guild member box
		pGuild->handleSponsoredGuildMembersBox(boxID, player, cancel, atoi(value.toCharArray()));
		break;
	case 0x7275: // Sponsored guild member accept/decline box
		pGuild->handleSponsoredGuildMembersAcceptBox(boxID, player, cancel, atoi(value.toCharArray()));
		break;
	case 0x7277: // Disband guild verify box
		returnString = value;
		pGuild->handleGuildDisbandBox(boxID, player, cancel, returnString);
		break;
	case 0x7278: // Namechange guild (Tag box)
		returnString = value;
		pGuild->handleGuildNameChange(boxID, player, cancel, returnString);
		break;
	case 0x7279: // Namechange guild (Tag box)
		returnString = value;
		pGuild->handleGuildNameChangeName(boxID, player, cancel, returnString);
		break;
	case 0x7280: // Guild Information - Members
		pGuild->handleGuildInformationMembersBox(boxID, player, cancel, atoi(value.toCharArray()));
		break;
	case 0x7281: // Guild Information - Member options
		pGuild->handleGuildMemberOptions(boxID, player, cancel, atoi(value.toCharArray()));
		break;
	case 0x7282: // Guild member permissions
		pGuild->handleGuildPermissionSelection(boxID, player, cancel, atoi(value.toCharArray()));
		break;
	case 0x7283: // Guild remove from guild exec
		pGuild->execRemoveFromGuild(boxID, player, cancel);
		break;
	case 0x7284: // Guild Transfer-Leadership Name of Target SUI Box return
		returnString = value;
		pGuild->handleGuildTransferLeaderBox(boxID, player, cancel, returnString);
		break;
	case 0x7285: // Guild Transfer-Leadership Accept/Decline Box Return
		pGuild->handleGuildTransferLeaderVerifyBox(boxID, player, cancel);
		break;
	case 0xAAAA:	// slice weapon
		handleSliceWeapon(boxID, player, cancel, atoi(value.toCharArray()));
		break;
	case 0xAABA:	// slice armor
		handleSliceArmor(boxID, player, cancel, atoi(value.toCharArray()));
		break;
	case 0xAACA:	// repair weapon
		handleRepairWeapon(boxID, player, cancel, atoi(value.toCharArray()));
		break;
	case 0xAADA:	// repair armor
		handleRepairArmor(boxID, player, cancel, atoi(value.toCharArray()));
		break;
	case 0xDAAD:
		handleTicketPurchaseMessageBox(boxID, player);
		break;
	case 0xAFAF:
		handleTicketCollectorRespones(boxID, player, cancel, atoi(value.toCharArray()));
		break;
	case 0xBABE:
		handleColorPicker(boxID, player, cancel, value, 2);
		break;
	case 0xBABB:
		handleColorPicker(boxID, player, cancel, value, 1);
		break;
	case 0xD65E:
		handleBankTransfer(boxID, player, atoi(value.toCharArray()), atoi(value2.toCharArray()));
		break;
	case 0xBF06:
		handleBlueFrogItemRequest(boxID, player, cancel, atoi(value.toCharArray()));
		break;
	case 0xBFDA:
		handleWoundTerminalRequest(boxID, player, cancel, atoi(value.toCharArray()));
		break;
	case 0xBFD0:
		handleStateTerminalRequest(boxID, player, cancel, atoi(value.toCharArray()));
		break;
	case 0xD1A6:
		handleDiagnose(boxID, player);
		break;
	case 0xE4F2:
		handleFreeResource(boxID, player, cancel, atoi(value.toCharArray()));
		break;
	case 0xE4F3:
		handleGiveFreeResource(boxID, player, cancel, atoi(value.toCharArray()));
		break;
	default:
		//Clean up players sui box:

		try {
			player->wlock();

			if (player->hasSuiBox(boxID)) {
				SuiBox* sui = player->getSuiBox(boxID);

				player->removeSuiBox(boxID);

				sui->finalize();
			}

			player->unlock();
		} catch (...) {
			player->error("error while cleaning sui in SuiManager::handleSuiEventNotification");
			player->unlock();
		}
	}
}

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

			SceneObject * scno = zone->lookupObject(player->getCurrentStructureID());

			InstallationObject * inso = (InstallationObject *) scno;

			inso->handleStructureRedeedConfirm(player);
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

			SceneObject * scno = zone->lookupObject(player->getCurrentStructureID());

			InstallationObject * inso = (InstallationObject *) scno;

			if (extra == inso->getDestroyCode()){
				inso->handleMakeDeed(player);
			}
			else{
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

			SceneObject * scno = zone->lookupObject(player->getCurrentStructureID());

			InstallationObject * inso = (InstallationObject *) scno;

			inso->handleStructureStatus(player);
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
}

void SuiManager::handleSetObjectName(uint32 boxID, Player* player,
		uint32 cancel, const String& name) {
	try {

		player->wlock();

		if (!player->hasSuiBox(boxID)) {
			player->unlock();
			return;
		}

		SuiBox* sui = player->getSuiBox(boxID);

		if (sui->isInputBox() && cancel != 1) {
			Zone * zone = player->getZone();

			SceneObject * scno = zone->lookupObject(player->getCurrentStructureID());

			TangibleObject * tano = (TangibleObject *) scno;

			if (tano!= NULL)	{

				//tano->setTemplateName(name);

			}

			/*else {
				BuildingObject * buio = (BuildingObject * ) obj;

				if (buio!= NULL)
					buio->setName(UnicodeString(name));
			}*/

		}

		player->removeSuiBox(boxID);

		sui->finalize();
		sui = NULL;

		player->unlock();
	} catch (Exception& e) {
		error("Exception in SuiManager::handleSetObjectName ");
		e.printStackTrace();

		player->unlock();
	} catch (...) {
		error("Unreported exception caught in SuiManager::handleSetObjectName");
		player->unlock();
	}
}

void SuiManager::handleAddMaintenance(uint32 boxID, Player* player,
		uint32 cancel, const String& newCashVal) {
	try {

		player->wlock();

		if (!player->hasSuiBox(boxID)) {
			player->unlock();
			return;
		}

		SuiBox* sui = player->getSuiBox(boxID);

		if (sui->isTransferBox() && cancel != 1) {

			Zone * zone = player->getZone();

			SceneObject * scno = zone->lookupObject(player->getCurrentStructureID());

			InstallationObject * inso = (InstallationObject *) scno;

			if (inso!= NULL && atoi(newCashVal.toCharArray()) != 0)	{
				int maint = (player->getCashCredits() - atoi(newCashVal.toCharArray()));

				inso->addMaintenance(maint);
				player->subtractCashCredits(maint);

				StringBuffer report;
				report << "You successfully make a payment of " << maint << " to "
					<< inso->getName().toString();

				player->sendSystemMessage(report.toString());

			}

			/*else {
				BuildingObject * buio = (BuildingObject * ) obj;

				if (buio!= NULL)

			}*/

		}

		player->removeSuiBox(boxID);

		sui->finalize();
		sui = NULL;

		player->unlock();
	} catch (Exception& e) {
		error("Exception in SuiManager::handleAddMaintenance ");
		e.printStackTrace();

		player->unlock();
	} catch (...) {
		error("Unreported exception caught in SuiManager::handleAddMaintenance");
		player->unlock();
	}
}
void SuiManager::handleAddEnergy(uint32 boxID, Player* player,
		uint32 cancel, const String& newEnergyVal) {
	try {

		player->wlock();

		if (!player->hasSuiBox(boxID)) {
			player->unlock();
			return;
		}

		SuiBox* sui = player->getSuiBox(boxID);

		if (sui->isTransferBox() && cancel != 1) {

			Zone * zone = player->getZone();

			SceneObject * scno = zone->lookupObject(player->getCurrentStructureID());

			InstallationObject * inso = (InstallationObject *) scno;

			if (inso!= NULL)	{
				uint energy = (inso->getSurplusPower() - atoi(newEnergyVal.toCharArray()));

				inso->addPower(energy);
				//player->removeEnergy(energy);

				StringBuffer report;
				report << "You successfully deposit " << energy << " units of energy.\n"
					<< "Energy reserves now at " << inso->getSurplusPower() << " units.";

				player->sendSystemMessage(report.toString());

			}

			/*else {
				BuildingObject * buio = (BuildingObject * ) obj;

				if (buio!= NULL)

			}*/

		}

		player->removeSuiBox(boxID);

		sui->finalize();
		sui = NULL;

		player->unlock();
	} catch (Exception& e) {
		error("Exception in SuiManager::handleAddPower ");
		e.printStackTrace();

		player->unlock();
	} catch (...) {
		error("Unreported exception caught in SuiManager::handleAddPower");
		player->unlock();
	}
}

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
}

void SuiManager::handleSurveyToolRange(uint32 boxID, Player* player, uint32 cancel, int range) {
	try {
		player->wlock();

		if (!player->hasSuiBox(boxID)) {
			player->unlock();
			return;
		}

		SuiBox* sui = player->getSuiBox(boxID);

		if (cancel != 1) {
			SurveyTool* surveyTool =  player->getSurveyTool();

			if (surveyTool != NULL) {
				surveyTool->wlock();

				surveyTool->setSurveyToolRange(range);

				surveyTool->unlock();
			} else
				player->sendSystemMessage("Error, invalid tool.");
		}

		player->removeSuiBox(boxID);

		sui->finalize();

		player->unlock();
	} catch (Exception& e) {
		StringBuffer msg;
		msg << "Exception in SuiManager::handleSurveyToolRange " << e.getMessage();
		error(msg.toString());

		player->unlock();
	} catch (...) {
		error("Unreported exception caught in SuiManager::handleSurveyToolRange(uint32 boxID, Player* player, int range)");
		player->unlock();
	}
}

void SuiManager::handleSliceWeapon(uint32 boxID, Player* player, uint32 cancel, int itemindex) {
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

			for (int i = 0; i < inventory->objectsSize(); i++) {
				TangibleObject* item = (TangibleObject*) inventory->getObject(i);

				if (item->isWeapon()) {
					Weapon* weapon = (Weapon*) item;

					if (!weapon->isSliced()) {
						if (weaponCount == itemindex)
							weapon->sliceWeapon(player);

						weaponCount++;
					}
				}
			}
		}

		player->removeSuiBox(boxID);

		sui->finalize();

		player->unlock();
	} catch (Exception& e) {
		StringBuffer msg;
		msg << "Exception in SuiManager::handleSliceWeapon " << e.getMessage();
		error(msg.toString());

		player->unlock();
	} catch (...) {
		error("Unreported exception caught in SuiManager::handleSliceWeapon(uint32 boxID, Player* player, int itemindex)");
		player->unlock();
	}
}

void SuiManager::handleSliceArmor(uint32 boxID, Player* player, uint32 cancel, int itemindex) {
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

			for (int i = 0; i < inventory->objectsSize(); i++) {
				TangibleObject* item = (TangibleObject*) inventory->getObject(i);

				if (item->isArmor()) {
					Armor* armor = (Armor*) item;

					if (!armor->isSliced()) {
						if (armorCount == itemindex)
							armor->sliceArmor(player);

						armorCount++;
					}
				}
			}
		}

		player->removeSuiBox(boxID);

		sui->finalize();

		player->unlock();
	} catch (Exception& e) {
		StringBuffer msg;
		msg << "Exception in SuiManager::handleSliceArmor " << e.getMessage();
		error(msg.toString());

		player->unlock();
	} catch (...) {
		error("Unreported exception caught in SuiManager::handleSliceArmor(uint32 boxID, Player* player, int itemindex)");
		player->unlock();
	}
}

void SuiManager::handleRepairWeapon(uint32 boxID, Player* player, uint32 cancel, int itemindex) {
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

			for (int i = 0; i < inventory->objectsSize(); i++) {
				TangibleObject* item = (TangibleObject*) inventory->getObject(i);

				item->wlock();

				if (item->isWeapon()) {
					Weapon* weapon = (Weapon*) item;

					if (weaponCount == itemindex)
						weapon->repairWeapon(player);

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

			for (int i = 0; i < inventory->objectsSize(); i++) {
				TangibleObject* item = (TangibleObject*) inventory->getObject(i);

				item->wlock();

				if (item->isArmor()) {
					Armor* armor = (Armor*) item;

					if (armorCount == itemindex)
						armor->repairArmor(player);

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

		/*sui->addMenuItem("@wound_terminal:inflict_wound_health");
		sui->addMenuItem("@wound_terminal:inflict_wound_strength");
		sui->addMenuItem("@wound_terminal:inflict_wound_constitution");
		sui->addMenuItem("@wound_terminal:inflict_wound_action");
		sui->addMenuItem("@wound_terminal:inflict_wound_quickness");
		sui->addMenuItem("@wound_terminal:inflict_wound_stamina");
		sui->addMenuItem("@wound_terminal:inflict_wound_mind");
		sui->addMenuItem("@wound_terminal:inflict_wound_focus");
		sui->addMenuItem("@wound_terminal:inflict_wound_willpower");*/
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

		/*	sui->addMenuItem("Test Fire State.");
			sui->addMenuItem("Test Disease State");
			sui->addMenuItem("Test Poison State");
			sui->addMenuItem("Test Dizzied State.");
			sui->addMenuItem("Test Blinded State");
			sui->addMenuItem("Test Intimidated State");
			sui->addMenuItem("Test Stunned State");  */

		if (sui->isListBox() && cancel != 1) {
			switch (itemIndex) {
			case 0:
				player->setOnFireState(150,1,180);
				break;
			case 1:
				player->setDiseasedState(150, 1, 180);
				break;
			case 2:
				player->setPoisonedState(150, 1, 180);
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

}
void SuiManager::handleTicketCollectorRespones(uint32 boxID, Player* player, uint32 cancel, int ticketIndex) {
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
				SceneObject* invObj = player->getInventoryItem(ticketObjectID);

				if (invObj != NULL && invObj->isTangible()) {
					TangibleObject* object = (TangibleObject*) invObj;

					if (object->isTicket()) {
						Ticket* ticket = (Ticket*) object;

						ticket->useObject(player);
					}
				}
			}
		}

		player->removeSuiBox(boxID);

		sui->finalize();

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
				SuiColorPicker* sui2 = new SuiColorPicker(player, colorPicker->getObjectID(), "private/index_color_2", 0xBABB);

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

void SuiManager::handleBankTransfer(uint32 boxID, Player* player, int cash, int bank) {
	try {
		player->wlock();

		if (!player->hasSuiBox(boxID)) {
			player->unlock();
			return;
		}

		SuiBox* sui = player->getSuiBox(boxID);

		player->removeSuiBox(boxID);

		sui->finalize();

		uint32 currentCash = player->getCashCredits();
		uint32 currentBank = player->getBankCredits();

		if ((currentCash + currentBank) == ((uint32)cash + (uint32)bank)) {
			player->updateCashCredits(cash);
			player->updateBankCredits(bank);
		}

		player->unlock();
	} catch (Exception& e) {
		StringBuffer msg;
		msg << "Exception in SuiManager::handleBankTransfer" << e.getMessage();
		error(msg.toString());

		player->unlock();
	} catch (...) {
		error("Unreported exception caught in SuiManager::handleBankTransfer");
		player->unlock();
	}
}
void SuiManager::handleCloneRequest(uint32 boxID, Player* player, uint32 cancel, int index) {
	try {
		player->wlock();

		if (!player->hasSuiBox(boxID)) {
			player->unlock();
			return;
		}

		SuiBox* sui = player->getSuiBox(boxID);

		player->removeSuiBox(boxID);

		sui->finalize();

		if (index >= 0) {
			if (!player->isDead()) {
				player->sendSystemMessage("You must be dead to activate your clone.");
			} else {
				player->doClone();
			}
		} else {
			if (player->isDead())
				player->sendSystemMessage("You will remain dead until you choose a location to clone or you are revived. Type /activateClone to restore the clone window.");
		}

		player->unlock();
	} catch (...) {
		error("Unreported exception caught in SuiManager::handleCloneRequest");
		player->unlock();
	}
}

void SuiManager::handleDiagnose(uint32 boxID, Player* player) {
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
		error("Exception in SuiManager::handleDiagnose ");
		e.printStackTrace();

		player->unlock();
	} catch (...) {
		error("Unreported exception caught in SuiManager::handleDiagnose");
		player->unlock();
	}
}

void SuiManager::handleFreeResource(uint32 boxID, Player* player, uint32 cancel, int index) {
	try{
		player->wlock();
		if (!player->hasSuiBox(boxID)){
			player->unlock();
			return;
		}

		SuiBox* sui = player->getSuiBox(boxID);
		ResourceManager* resManager = player->getZone()->getZoneServer()->getResourceManager();
		if (sui->isListBox()) {
			SuiListBox* listBox = (SuiListBox*)sui;
			if (cancel!=1){
				if (index==-1){//sui returns -1 if nothing is selected
					player->sendMessage(listBox->generateMessage());
					player->unlock();
					return;
				}
				String choice = listBox->getMenuItemName(index);
				player->addSuiBoxChoice(choice);

				SuiListBoxVector* choicesList = player->getSuiBoxChoices();

				if (resManager->containsResource(choice)){//display the resource stats
					/*
					 * If we get to a resource but there are still more list boxes ahead of
					 * this list box, we delete them so that we can insert the final box.
					 */
					bool hasNextBox = false;
					SuiListBox* nextListBox;
					if (listBox->getNextBox()!=0 && player->hasSuiBox(listBox->getNextBox())){
						hasNextBox = true;
						nextListBox = (SuiListBox*)player->getSuiBox(listBox->getNextBox());
					}
					while (hasNextBox){
						if (nextListBox->getNextBox()==0){
							uint32 zero = 0;
							nextListBox->setPreviousBox(zero);
							player->removeSuiBox(nextListBox->getBoxID());
							nextListBox->finalize();
							hasNextBox=false;
						}
						else if (player->getSuiBox(nextListBox->getNextBox())->isListBox()){
							uint32 nextBox = nextListBox->getNextBox();
							uint32 zero = 0;
							nextListBox->setNextBox(zero);
							nextListBox->setPreviousBox(zero);
							player->removeSuiBox(nextListBox->getBoxID());
							nextListBox->finalize();
							nextListBox = (SuiListBox*)player->getSuiBox(nextBox);
						}
					}


					SuiListBox* finalListBox = new SuiListBox(player, 0xE4F3);
					player->addSuiBox(finalListBox);
					listBox->setNextBox(finalListBox->getBoxID());
					finalListBox->setPreviousBox(listBox->getBoxID());
					finalListBox->setBackButton(true);
					finalListBox->setPromptTitle(choice);
					finalListBox->setPromptText("Please confirm that you would like to select this resource as your Veteran Reward Crate of Resources. Use the BACK button to go back and select a different resource.");
					resManager->generateSUI(player, finalListBox);
					player->sendMessage(finalListBox->generateMessage());
				}
				else{//use a listbox to show the next set of classes to choose from
					if (listBox->getNextBox()!=0){ //already a listbox ahead so no need to create one
						SuiBox* nextSui = player->getSuiBox(listBox->getNextBox());
						if (nextSui->isListBox()){
							SuiListBox* nextListBox = (SuiListBox*)nextSui;
							nextListBox->removeAllMenuItems();
							String text = ("Choose resource class from " + choice);
							nextListBox->setPromptText(text);
							resManager->generateSUI(player, nextListBox);
							player->sendMessage(nextListBox->generateMessage());
						}
					}
					else if (listBox->getNextBox()==0){ //no listbox ahead so we create one
						SuiListBox* listBox2 = new SuiListBox(player, 0xE4F2);
						player->addSuiBox(listBox2);
						listBox->setNextBox(listBox2->getBoxID());
						listBox2->setPreviousBox(listBox->getBoxID());
						listBox2->setPromptTitle("Resources");
						String text = ("Choose resource class from " + choice);
						listBox2->setPromptText(text);
						listBox2->setBackButton(true);
						resManager->generateSUI(player, listBox2);
						player->sendMessage(listBox2->generateMessage());
					}
				}
			}
			if (cancel==1 && listBox->getPreviousBox()!=0){//clicked BACK. return to previous menu
				SuiBox* prevSui = player->getSuiBox(listBox->getPreviousBox());
				if (prevSui->isListBox()){
					SuiListBox* prevListBox = (SuiListBox*)prevSui;
					player->removeLastSuiBoxChoice();
					player->sendMessage(prevListBox->generateMessage());
				}
			}
			else if (cancel==1 && listBox->getPreviousBox()==0){//clicked CANCEL. removing every menu
				while (listBox->getNextBox()!=0 && player->hasSuiBox(listBox->getNextBox())){
					if (player->getSuiBox(listBox->getNextBox())->isListBox()){
						uint32 nextBox = listBox->getNextBox();
						uint32 zero = 0;
						listBox->setNextBox(zero);
						listBox->setPreviousBox(zero);
						player->removeSuiBox(listBox->getBoxID());
						listBox->finalize();
						listBox = (SuiListBox*)player->getSuiBox(nextBox);
					}
				}

				uint32 zero = 0;
				if (player->hasSuiBox(listBox->getBoxID())){
					listBox->setPreviousBox(zero);
					player->removeSuiBox(listBox->getBoxID());
					listBox->finalize();
				}
				player->clearSuiBoxChoices();
			}
		}

		player->unlock();
	} catch (Exception& e) {
		error("Exception in SuiManager::handleFreeResource");
		e.printStackTrace();

		player->unlock();;
	} catch (...) {
		error("Unreported exception caught in SuiManager::handleFreeResource");
		player->unlock();
	}
}

void SuiManager::handleGiveFreeResource(uint32 boxID, Player* player, uint32 cancel, int index) {
	try{
		player->wlock();
		if (!player->hasSuiBox(boxID)){
			player->unlock();
			return;
		}

		SuiBox* sui = player->getSuiBox(boxID);
		ResourceManager* resManager = player->getZone()->getZoneServer()->getResourceManager();
		if (sui->isListBox()) {
			SuiListBox* listBox = (SuiListBox*)sui;
			if (cancel!=1){//give the resources to the player then remove all listboxes
				SuiListBoxVector* choicesList = player->getSuiBoxChoices();
				resManager->useResourceDeed(player, choicesList->get(choicesList->size()-1), ResourceManagerImplementation::RESOURCE_DEED_QUANTITY);
				player->clearSuiBoxChoices();
				player->sendSystemMessage("You received 30k of resources.");

				uint64 oID = player->getResourceDeedID();

				SceneObject* obj = player->getPlayerItem(oID);
				ResourceDeed* deed = (ResourceDeed*)obj;
				deed->destroyDeed(player);

				uint32 zero = 0;
				while (listBox->getPreviousBox()!=0 && player->hasSuiBox(listBox->getPreviousBox())){
					if (player->getSuiBox(listBox->getPreviousBox())->isListBox()){
						uint32 prevBox = listBox->getPreviousBox();
						player->removeSuiBox(listBox->getBoxID());
						listBox->setNextBox(zero);
						listBox->setPreviousBox(zero);
						listBox->finalize();
						listBox = (SuiListBox*)player->getSuiBox(prevBox);
					}
				}
				if (player->hasSuiBox(listBox->getBoxID())){
					listBox->setNextBox(zero);
					player->removeSuiBox(listBox->getBoxID());
					listBox->finalize();
				}
				player->clearSuiBoxChoices();
			}
			if (cancel==1 && listBox->getPreviousBox()!=0){//clicked BACK. just remove the final box.
				SuiBox* prevSui = player->getSuiBox(listBox->getPreviousBox());
				if (prevSui->isListBox()){
					SuiListBox* prevListBox = (SuiListBox*)prevSui;
					player->removeLastSuiBoxChoice();
					player->removeSuiBox(listBox->getBoxID());
					uint32 zero = 0;
					prevListBox->setNextBox(zero);
					listBox->setPreviousBox(zero);
					listBox->finalize();
					player->sendMessage(prevListBox->generateMessage());
				}
			}
		}

		player->unlock();
	} catch (Exception& e) {
		error("Exception in SuiManager::handleGiveFreeResource");
		e.printStackTrace();

		player->unlock();;
	} catch (...) {
		error("Unreported exception caught in SuiManager::handleGiveFreeResource");
		player->unlock();
	}

}

void SuiManager::handleConsentBox(uint32 boxID, Player* player, uint32 cancel, int index) {
	try {
		player->wlock();

		if (!player->hasSuiBox(boxID)) {
			player->unlock();
			return;
		}

		SuiBox* sui = player->getSuiBox(boxID);

		//TODO: Remove from consent list?

		player->removeSuiBox(boxID);

		sui->finalize();

		player->unlock();
	} catch (Exception& e) {
		error("Exception in SuiManager::handleDiagnose ");
		e.printStackTrace();

		player->unlock();
	} catch (...) {
		error("Unreported exception caught in SuiManager::handleDiagnose");
		player->unlock();
	}
}
