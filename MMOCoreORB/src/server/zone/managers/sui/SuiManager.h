/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SUIMANAGER_H_
#define SUIMANAGER_H_

#include "server/zone/objects/player/sui/SuiPageData.h"
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
     namespace sui {
      class SuiBox;
     }
   }
  }
 }
}

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
	  	void handleStartMusic(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
	  	void handleStartDancing(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
	  	void handleSetObjectName(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
	  	void handleBankTransfer(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
	  	void handleFishingAction(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);
	  	void handleCharacterBuilderSelectItem(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args);

	  	void sendKeypadSui(SceneObject* keypad, SceneObject* creatureSceneObject, const String& play, const String& callback);
	  	void sendConfirmSui(SceneObject* terminal, SceneObject* player, const String& play, const String& callback, const String& prompt, const String& button);
	  	void sendMessageBox(SceneObject* usingObject, SceneObject* player, const String& title, const String& text, const String& okButton, const String& screenplay, const String& callback, unsigned int windowType = 0x0 );
	  	void sendInputBox(SceneObject* terminal, SceneObject* player, const String& play, const String& callback, const String& prompt, const String& button);
	  	void sendListBox(SceneObject* usingObject, SceneObject* player, const String& title, const String& text, const uint8& numOfButtons, const String& cancelButton, const String& otherButton, const String& okButton, LuaObject& options, const String& screenplay, const String& callback, const float& forceCloseDist);
	  	void sendTransferBox(SceneObject* usingObject, SceneObject* player, const String& title, const String& text, LuaObject& optionsAddFrom, LuaObject& optionsAddTo, const String& screenplay, const String& callback);
	  	int32 sendSuiPage(CreatureObject* creature, SuiPageData* pageData, const String& play, const String& callback, unsigned int windowType);

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
