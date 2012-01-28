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
   namespace creature {
	   class CreatureObject;
   }

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
using namespace server::zone::objects::creature;

namespace server {
 namespace zone {
  namespace managers {
   namespace sui {

	  class SuiManager : public Singleton<SuiManager>, public Logger, public Object {
	  	ZoneProcessServer* server;

	  public:
	  	SuiManager();
	  	SuiManager(ZoneProcessServer* serv);

	  	void handleSuiEventNotification(uint32 boxID, CreatureObject* player, uint32 cancel, Vector<UnicodeString>* args);

	  	//Handlers
	  	void handleMessageoftheDay(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
	  	void handleSetMOTD(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);

	  	void handleStartMusic(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
	  	void handleStartDancing(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);

	  	void handleSampleRadioactiveConfirm(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
	  	void handleSurveyConcentratedMinigame(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
	  	void handleSurveyConcentratedMinigame2(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);

	  	void handleRepairWeapon(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
	  	void handleRepairArmor(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);

	  	void handleTicketPurchaseMessageBox(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
	  	void handleTicketCollectorResponse(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);

	  	void handleCodeForRedeed(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
	  	void handleRedeedStructure(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
	  	void handleRefreshStatusListBox(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
	  	void handleSetObjectName(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
	  	void handleManageMaintenance(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
	  	void handleAddEnergy(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);

	  	void handleColorPicker(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);

	  	void handleBankTransfer(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
	  	void handleFishingAction(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);

	  	void handleBlueFrogItemRequest(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
	  	void handleWoundTerminalRequest(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
	  	void handleStateTerminalRequest(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);

	  	void handleDiagnose(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);

	  	void handleCloneConfirm(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
	  	void handleCloneRequest(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
	  	void handleConsentBox(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);

	  	void handleDenyTrainingList(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);

	  	void handleInsureAllConfirm(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);

	  	void handleBankTipConfirm(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
	  	void handleSlicingMenu(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
	  	void handleRangerWhatToTrackBox(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);

	  	void handleInsertFactorySchem2(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
	  	void handleInsertFactorySchem3(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);

	  	void handleBanListSelection(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
	  	void handleCommandsListSelection(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
	  	void handleAccountListSelection(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
	  	void handleCharacterListSelection(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);

	  	void handleCharacterBuilderSelectItem(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);

	  	void handleChangeCityName(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
	  	void handleCreateCity(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
	  	void handleCityEnableZoning(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
	  	void handleManageMilitia(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
	  	void handleAddMilitia(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);

	  	void handleGamblingSlotPayout(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
	  	void handleGamblingSlot(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
	  	void handleGamblingRoulette(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
	  };
   }
  }
 }
}

using namespace server::zone::managers::sui;



#endif /*SUIMANAGER_H_*/
