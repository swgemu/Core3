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

#ifndef CONVERSATIONSCREEN_H_
#define CONVERSATIONSCREEN_H_

#include "engine/engine.h"
#include "server/chat/StringIdChatParameter.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/packets/object/NpcConversationMessage.h"
#include "server/zone/packets/object/StopNpcConversation.h"
#include "server/zone/packets/object/StringList.h"
#include "server/zone/objects/player/sessions/ConversationSession.h"

namespace server {
namespace zone {
namespace templates {
namespace mobile {

class ConversationOption : public Object {
	StringIdChatParameter optionText;
	String linkedScreenID;

public:
	ConversationOption(const StringIdChatParameter& opttext, const String& screenid) {
		optionText = opttext;
		linkedScreenID = screenid;
	}

	inline String& getLinkedScreenID() {
		return linkedScreenID;
	}

	inline StringIdChatParameter& getOptionText() {
		return optionText;
	}

	inline bool isLinked() {
		return !linkedScreenID.isEmpty();
	}

	inline void setOptionText(StringIdChatParameter optionText) {
		this->optionText = optionText;
	}
};

class ConversationScreen : public Object {
	String screenID;

	//TODO: Consider multiple dialog texts that can be displayed for screens
	StringIdChatParameter dialogText;

	UnicodeString customText;

	Vector<Reference<ConversationOption*> > options;

	bool stopConversation;

public:
	ConversationScreen() {
	}

	/**
	 * Copy constructor.
	 */
	ConversationScreen(const ConversationScreen& objectToCopy) : Object() {
		screenID = objectToCopy.screenID;
		dialogText = objectToCopy.dialogText;
		options = objectToCopy.options;
		stopConversation = objectToCopy.stopConversation;
	}

	ConversationScreen* cloneScreen() {
		return new ConversationScreen(*this);
	}

	/**
	 * Adds an option to this conversation screen.
	 * @param optionText The text to be displayed for the option.
	 * @param linkedScreenID The ID of the screen this option is linked.
	 */
	void addOption(const String& optionText, const String& linkedScreenID) {
		options.add(new ConversationOption(optionText, linkedScreenID));
	}

	void removeOption(int idx) {
		options.remove(idx);
	}

	ConversationOption* getOption(int idx) {
		return options.get(idx);
	}

	String getOptionText(int idx) const {
		String text;

		Reference<ConversationOption*> opt = options.get(idx);

		if (opt != NULL)
			text = customText.toString();

		return text;
	}

	String getOptionLink(int idx) const {
		String link;

		Reference<ConversationOption*> opt = options.get(idx);

		if (opt != NULL)
			link = opt->getLinkedScreenID();

		return link;
	}

	inline int getOptionCount() {
		return options.size();
	}

	/**
	 * Sends this ConversationScreen to the creature passed in.
	 * @param player The player receiving the message.
	 * @param npc The npc the player is talking to.
	 */
	void sendTo(CreatureObject* player, CreatureObject* npc) {
		NpcConversationMessage* message = new NpcConversationMessage(player, dialogText);

		//Encapsulate this logic better?
		StringList* optionsList = new StringList(player);

		for (int i = 0; i < options.size(); ++i) {
			Reference<ConversationOption*> option = options.get(i);

			if (option == NULL)
				continue;

			optionsList->insertOption(customText);
		}

		player->sendMessage(message);
		player->sendMessage(optionsList);

		ConversationScreen* screenToSave = this;

		//Check if the conversation should be stopped.
		if (stopConversation) {
			player->sendMessage(new StopNpcConversation(player, npc->getObjectID()));
			screenToSave = NULL;
		}

		ConversationSession* session = cast<ConversationSession* >(player->getActiveSession(SessionFacadeType::CONVERSATION));
		if (session != NULL) {
			session->setLastConversationScreen(screenToSave);
		}
	}

	inline String& getScreenID() {
		return screenID;
	}

	void readObject(LuaObject* luaObject) {
		screenID = luaObject->getStringField("id");
		dialogText.setStringId(luaObject->getStringField("leftDialog"));

		if (luaObject->getStringField("stopConversation").toLowerCase() == "true") {
			stopConversation = true;
		} else {
			stopConversation = false;
		}

		LuaObject optionsTable = luaObject->getObjectField("options");

		for (int i = 1; i <= optionsTable.getTableSize(); ++i) {
			lua_rawgeti(luaObject->getLuaState(), -1, i);

			LuaObject luaObj(luaObject->getLuaState());

			StringIdChatParameter stringId(luaObj.getStringAt(1));
			String linkedId = luaObj.getStringAt(2);

			Reference<ConversationOption*> option = new ConversationOption(stringId, linkedId);

			options.add(option);

			luaObj.pop();
		}

		optionsTable.pop();
	}

	template<class T>
	inline void setDialogTextTT(const T& obj) {
		dialogText.setTT(obj);
	}

	inline void setDialogTextTT(const String& file, const String& id) {
		dialogText.setTT(file, id);
	}

	template<class T>
	inline void setDialogTextTO(const T& obj) {
		dialogText.setTO(obj);
	}

	inline void setDialogTextTO(const String& file, const String& id) {
		dialogText.setTO(file, id);
	}

	template<class T>
	inline void setDialogTextTU(const T& obj) {
		dialogText.setTO(obj);
	}

	inline void setDialogTextTU(const String& file, const String& id) {
		dialogText.setTU(file, id);
	}

	inline void setDialogTextDI(uint32 val) {
		dialogText.setDI(val);
	}

	inline void setDialogTextDF(float val) {
		dialogText.setDF(val);
	}

	inline void setDialogText(const String& fullPath) {
		dialogText.setStringId(fullPath);
	}

	inline void setCustomDialogText(const UnicodeString& custom) {
		customText = custom;
	}

	inline void setDialogText(const StringIdChatParameter& param) {
		dialogText = param;
	}

	inline void setStopConversation(bool stopConversation) {
		this->stopConversation = stopConversation;
	}

	inline StringIdChatParameter* getDialogText() {
		return &dialogText;
	}
};

}
}
}
}

using namespace server::zone::templates::mobile;

#endif /* CONVERSATIONSCREEN_H_ */
