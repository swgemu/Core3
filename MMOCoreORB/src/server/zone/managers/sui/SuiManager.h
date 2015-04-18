/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SUIMANAGER_H_
#define SUIMANAGER_H_

#include "engine/engine.h"

#include "server/zone/ZoneProcessServer.h"

namespace server {
 namespace zone {
  namespace objects {
   namespace scene {
   	   class SceneObject;
   }

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
using namespace server::zone::objects::scene;

namespace server {
 namespace zone {
  namespace managers {
   namespace sui {

	  class SuiManager : public Singleton<SuiManager>, public Logger, public Object {
	  	ManagedReference<ZoneProcessServer*> server;

	  public:
	  	SuiManager();

	  	void handleSuiEventNotification(uint32 boxID, CreatureObject* player, uint32 cancel, Vector<UnicodeString>* args);

	  	//Handlers
	  	/*void handleMessageoftheDay(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
	  	void handleSetMOTD(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
*/
	  	void handleStartMusic(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
	  	void handleStartDancing(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);

/*
	  	void handleRepairWeapon(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
	  	void handleRepairArmor(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);

	  	void handleTicketPurchaseMessageBox(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
	  	void handleTicketCollectorResponse(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);

	  	void handleCodeForRedeed(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
	  	void handleRedeedStructure(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
	  	void handleRefreshStatusListBox(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
	*/  void handleSetObjectName(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
/*
	  	void handleColorPicker(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
*/
	  	void handleBankTransfer(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
	  	void handleFishingAction(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
/*
	  	void handleBlueFrogItemRequest(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
	  	void handleWoundTerminalRequest(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
	  	void handleStateTerminalRequest(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
*/
	  	void handleDiagnose(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
/*
	  	void handleCloneConfirm(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
	  	void handleCloneRequest(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
*/  	void handleConsentBox(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
/*
	  	void handleDenyTrainingList(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);

	  	void handleInsureAllConfirm(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);

	  	void handleBankTipConfirm(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
	  	void handleSlicingMenu(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
	  	void handleRangerWhatToTrackBox(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);

	  	void handleBanListSelection(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
	  	void handleCommandsListSelection(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
	  	void handleAccountListSelection(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
	  	void handleCharacterListSelection(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
		*/
	  	void handleCharacterBuilderSelectItem(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);

	  	void sendKeypadSui(SceneObject* keypad, SceneObject* creatureSceneObject, const String& play, const String& callback);
	  	void sendConfirmSui(SceneObject* terminal, SceneObject* player, const String& play, const String& callback, const String& prompt, const String& button);
	  	void sendMessageBox(SceneObject* usingObject, SceneObject* player, const String& title, const String& text, const String& okButton, const String& screenplay, const String& callback, unsigned int windowType = 0x0 );
	  	void sendInputBox(SceneObject* terminal, SceneObject* player, const String& play, const String& callback, const String& prompt, const String& button);
	  	void sendListBox(SceneObject* usingObject, SceneObject* player, const String& title, const String& text, const uint8& numOfButtons, const String& cancelButton, const String& otherButton, const String& okButton, LuaObject& options, const String& screenplay, const String& callback);
	  	void sendTransferBox(SceneObject* usingObject, SceneObject* player, const String& title, const String& text, LuaObject& optionsAddFrom, LuaObject& optionsAddTo, const String& screenplay, const String& callback);

	  	void setZoneProcessServer(ZoneProcessServer* srv) {
	  		server = srv;
	  	}
	  };
   }
  }
 }
}

using namespace server::zone::managers::sui;



#endif /*SUIMANAGER_H_*/
