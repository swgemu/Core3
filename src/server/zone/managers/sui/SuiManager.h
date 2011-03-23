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

#ifndef SUIMANAGER_H_
#define SUIMANAGER_H_

#include "engine/engine.h"

#include "server/zone/ZoneProcessServer.h"

namespace server {
 namespace zone {
  namespace objects {
   namespace player {
    class PlayerCreature;
     namespace sui {
      class SuiBox;
     }
   }
  }
 }
}

using namespace server::zone::objects::player;
using namespace server::zone::objects::player::sui;

namespace server {
 namespace zone {
  namespace managers {
   namespace sui {

	  class SuiManager : public Logger {
	  	ZoneProcessServer* server;

	  public:
	  	SuiManager(ZoneProcessServer* serv);

	  	void handleSuiEventNotification(uint32 boxID, PlayerCreature* player, uint32 cancel, Vector<UnicodeString>* args);

	  	//Handlers
	  	void handleMessageoftheDay(PlayerCreature* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
	  	void handleSetMOTD(PlayerCreature* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);

	  	void handleStartMusic(PlayerCreature* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
	  	void handleStartDancing(PlayerCreature* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);

	  	void handleSampleRadioactiveConfirm(PlayerCreature* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
	  	void handleSurveyConcentratedMinigame(PlayerCreature* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
	  	void handleSurveyConcentratedMinigame2(PlayerCreature* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);

	  	void handleRepairWeapon(PlayerCreature* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
	  	void handleRepairArmor(PlayerCreature* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);

	  	//Structure Stuff
	  	void handleStructureStatus(PlayerCreature* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
	  	void handleStructureDestroyConfirm(PlayerCreature* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
	  	void handleStructureDestroyCode(PlayerCreature* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);

	  	void handleTicketPurchaseMessageBox(PlayerCreature* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
	  	void handleTicketCollectorResponse(PlayerCreature* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);

	  	void handleCodeForRedeed(PlayerCreature* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
	  	void handleRedeedStructure(PlayerCreature* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
	  	void handleRefreshStatusListBox(PlayerCreature* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
	  	void handleSetObjectName(PlayerCreature* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
	  	void handleManageMaintenance(PlayerCreature* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
	  	void handleAddEnergy(PlayerCreature* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);

	  	void handleColorPicker(PlayerCreature* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);

	  	void handleBankTransfer(PlayerCreature* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
	  	void handleFishingAction(PlayerCreature* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);

	  	void handleBlueFrogItemRequest(PlayerCreature* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
	  	void handleWoundTerminalRequest(PlayerCreature* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
	  	void handleStateTerminalRequest(PlayerCreature* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);

	  	void handleDiagnose(PlayerCreature* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
	  	void handleFreeResource(PlayerCreature* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
	  	void handleGiveFreeResource(PlayerCreature* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);

	  	void handleCloneConfirm(PlayerCreature* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
	  	void handleCloneRequest(PlayerCreature* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
	  	void handleConsentBox(PlayerCreature* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);

	  	void handleDenyTrainingList(PlayerCreature* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);

	  	void handleTeachPlayer(PlayerCreature* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
	  	void handleTeachSkill(PlayerCreature* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);

	  	void handleInsuranceMenu(PlayerCreature* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
	  	void handleInsureAllConfirm(PlayerCreature* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);

	  	void handleBankTipConfirm(PlayerCreature* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
	  	void handleSlicingMenu(PlayerCreature* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
	  	void handleRangerWhatToTrackBox(PlayerCreature* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);

	  	void handleInsertFactorySchem2(PlayerCreature* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
	  	void handleInsertFactorySchem3(PlayerCreature* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);

	  	void handleSellJunkLootSelection(PlayerCreature* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
	  	void handleBanListSelection(PlayerCreature* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
	  	void handleCommandsListSelection(PlayerCreature* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
	  	void handleAccountListSelection(PlayerCreature* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
	  	void handleCharacterListSelection(PlayerCreature* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);

	  	void handleCharacterBuilderSelectItem(PlayerCreature* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);

	  	void handleChangeCityName(PlayerCreature* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
	  	void handleCreateCity(PlayerCreature* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
	  	void handleCityEnableZoning(PlayerCreature* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
	  	void handleManageMilitia(PlayerCreature* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
	  	void handleAddMilitia(PlayerCreature* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);

	  	void handleGamblingSlotPayout(PlayerCreature* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
	  	void handleGamblingSlot(PlayerCreature* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
	  	void handleGamblingRoulette(PlayerCreature* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
	  };
   }
  }
 }
}

using namespace server::zone::managers::sui;



#endif /*SUIMANAGER_H_*/
