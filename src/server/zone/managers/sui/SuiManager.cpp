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

#include "../../objects.h"
#include "../../objects/player/sui/colorpicker/SuiColorPicker.h"

#include "../item/ItemManager.h"
#include "../../objects/creature/bluefrog/BlueFrogVector.h"

#include "../../ZoneProcessServerImplementation.h"

SuiManager::SuiManager(ZoneProcessServerImplementation* serv) : Logger("SuiManager") {
	server = serv;

	setGlobalLogging(true);
	setLogging(false);
}

void SuiManager::handleSuiEventNotification(uint32 boxID, Player* player, uint32 cancel, const string& value, const string& value2) {
	uint16 type = (uint16) boxID;

	int range;

	switch (type) {
	case 0xC057:
		handleConsentBox(boxID, player, cancel, atoi(value.c_str()));
		break;
	case 0xC103:
		handleCloneRequest(boxID, player, cancel, atoi(value.c_str()));
		break;
	case 0x5553:
		handleStartMusic(boxID, player, cancel, value.c_str(), false);
		break;
	case 0x414E:
		handleStartDancing(boxID, player, cancel, value.c_str(), false);
		break;
	case 0x5A53: // changemusic
		handleStartMusic(boxID, player, cancel, value.c_str(), true);
		break;
	case 0x4B4E: // changedance
		handleStartDancing(boxID, player, cancel, value.c_str(), true);
		break;
	case 0x7259:
		range = (atoi(value.c_str()) * 64) + 64;
		handleSurveyToolRange(boxID, player, cancel, range);
		break;
	case 0xAAAA:	// slice weapon
		handleSliceWeapon(boxID, player, cancel, atoi(value.c_str()));
		break;
	case 0xAABA:	// slice armor
		handleSliceArmor(boxID, player, cancel, atoi(value.c_str()));
		break;
	case 0xAACA:	// repair weapon
		handleRepairWeapon(boxID, player, cancel, atoi(value.c_str()));
		break;
	case 0xAADA:	// repair armor
		handleRepairArmor(boxID, player, cancel, atoi(value.c_str()));
		break;
	case 0xDAAD:
		handleTicketPurchaseMessageBox(boxID, player);
		break;
	case 0xAFAF:
		handleTicketCollectorRespones(boxID, player, cancel, atoi(value.c_str()));
		break;
	case 0x7280:   // Generate security code for Redeed
		handleCodeForRedeed(boxID, player, cancel, value.c_str());
		break;
	case 0x7281:   // Redeed or Destroy Structure
		handleRedeedStructure(boxID, player, cancel, atoi(value.c_str()));
		break;
	case 0x7282:   // Refresh Status Listbox
		handleRefreshStatusListBox(boxID, player, cancel, atoi(value.c_str()));
		break;
	case 0x7283:   // Set Object Name
		handleSetObjectName(boxID, player, cancel, value.c_str());
		break;
	case 0x7284:	// Add Maintenance
		handleAddMaintenance(boxID, player, cancel, value.c_str());
		break;
	case 0x7285:	// Add Energy
		handleAddEnergy(boxID, player, cancel, value.c_str());
		break;
	case 0xBABE:
		handleColorPicker(boxID, player, cancel, value);
		break;
	case 0xD65E:
		handleBankTransfer(boxID, player, atoi(value.c_str()), atoi(value2.c_str()));
		break;
	case 0xBF06:
		handleBlueFrogItemRequest(boxID, player, cancel, atoi(value.c_str()));
		break;
	case 0xBFDA:
		handleWoundTerminalRequest(boxID, player, cancel, atoi(value.c_str()));
		break;
	case 0xBFD0:
		handleStateTerminalRequest(boxID, player, cancel, atoi(value.c_str()));
		break;
	case 0xD1A6:
		handleDiagnose(boxID, player);
		break;
	default:
		//error("Unknown SuiBoxNotification opcode");
		break;
	}
}

void SuiManager::handleCodeForRedeed(uint32 boxID, Player* player,
		uint32 cancel, const string& extra) {
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

			if(extra == inso->getDestroyCode()){			
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
		uint32 cancel, const string& name) {
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

			TangibleObject * tano = (TangibleObject *) tano;
			
			if(tano!= NULL)	{
				
				//tano->setTemplateName(name);
				
			}
			
			/*else {
				BuildingObject * buio = (BuildingObject * ) obj;
									
				if(buio!= NULL)
					buio->setName(unicode(name));
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
		uint32 cancel, const string& newCashVal) {
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
			
			if(inso!= NULL && atoi(newCashVal.c_str()) != 0)	{
				int maint = (player->getCashCredits() - atoi(newCashVal.c_str()));
				
				inso->addMaintenance(maint);			
				player->subtractCashCredits(maint);
				
				stringstream report;
				report << "You successfully make a payment of " << maint << " to "
					<< inso->getName().c_str();
				
				player->sendSystemMessage(report.str());
				
			}
			
			/*else {
				BuildingObject * buio = (BuildingObject * ) obj;
									
				if(buio!= NULL)
					
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
		uint32 cancel, const string& newEnergyVal) {
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
			
			if(inso!= NULL)	{
				uint energy = (inso->getEnergy() - atoi(newEnergyVal.c_str()));
				
				inso->addEnergy(energy);			
				//player->removeEnergy(energy);
				
				stringstream report;
				report << "You successfully deposit " << energy << " units of energy.\n"
					<< "Energy reserves now at " << inso->getEnergy() << " units.";
				
				player->sendSystemMessage(report.str());
				
			}
			
			/*else {
				BuildingObject * buio = (BuildingObject * ) obj;
									
				if(buio!= NULL)
					
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

void SuiManager::handleStartMusic(uint32 boxID, Player* player, uint32 cancel, const string& song, bool change) {
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
		stringstream msg;
		msg << "Exception in SuiManager::handleStartMusic " << e.getMessage();
		error(msg.str());

		player->unlock();
	} catch (...) {
		error("Unreported exception caught in SuiManager::handleStartMusic(Player* player, const string& music)");
		player->unlock();
	}
}

void SuiManager::handleStartDancing(uint32 boxID, Player* player, uint32 cancel, const string& dance, bool change) {
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
		stringstream msg;
		msg << "Exception in SuiManager::handleStartDancing " << e.getMessage();
		error(msg.str());

		player->unlock();
	} catch (...) {
		error("Unreported exception caught in SuiManager::handleStartDancing(Player* player, const string& music)");
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
		stringstream msg;
		msg << "Exception in SuiManager::handleSurveyToolRange " << e.getMessage();
		error(msg.str());

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
		stringstream msg;
		msg << "Exception in SuiManager::handleSliceWeapon " << e.getMessage();
		error(msg.str());

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
		stringstream msg;
		msg << "Exception in SuiManager::handleSliceArmor " << e.getMessage();
		error(msg.str());

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
		stringstream msg;
		msg << "Exception in SuiManager::handleRepairWeapon " << e.getMessage();
		error(msg.str());

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
		stringstream msg;
		msg << "Exception in SuiManager::handleRepairArmor " << e.getMessage();
		error(msg.str());

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
		stringstream msg;
		msg << "Exception in SuiManager::handleTicketPurchaseMessageBox " << e.getMessage();
		error(msg.str());

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

			if(itemIndex >= 0 && itemIndex < bfVector->size()) {
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

void SuiManager::handleColorPicker(uint32 boxID, Player* player, uint32 cancel, const string& value) {
	try {
		player->wlock();

		if (!player->hasSuiBox(boxID)) {
			player->unlock();
			return;
		}

		SuiBox* sui = player->getSuiBox(boxID);

		if (sui->isColorPicker()) {
			SuiColorPicker* colorPicker = (SuiColorPicker*) sui;

			int val = atoi(value.c_str());

			if (val >= 0 && val < 144) {
				uint64 oID = colorPicker->getObjectID();

				SceneObject* obj = player->getInventoryItem(oID);

				if (obj != NULL && obj->isTangible()) {
					TangibleObject* tano = (TangibleObject*) obj;

					tano->wlock();

					tano->setCustomizationVariable(2, val);
					tano->setUpdated(true);

					TangibleObjectDeltaMessage3* delta = new TangibleObjectDeltaMessage3(tano);
					delta->updateCustomizationString();
					delta->close();

					tano->unlock();

					player->broadcastMessage(delta);
				}
			}
		}

		player->removeSuiBox(boxID);

		sui->finalize();

		player->unlock();
	} catch (Exception& e) {
		stringstream msg;
		msg << "Exception in SuiManager::handleColorPicker" << e.getMessage();
		error(msg.str());

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
		stringstream msg;
		msg << "Exception in SuiManager::handleBankTransfer" << e.getMessage();
		error(msg.str());

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
