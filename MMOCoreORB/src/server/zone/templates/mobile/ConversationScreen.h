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

	Vector<Reference<ConversationOption*> > options;


public:
	ConversationScreen() {
	}

	/**
	 * Copy constructor.
	 */
	ConversationScreen(const ConversationScreen& objectToCopy) : Object(objectToCopy) {
		screenID = objectToCopy.screenID;
		dialogText = objectToCopy.dialogText;
		options = objectToCopy.options;
	}

	inline void setDialogText(const String& fullPath) {
		dialogText.setStringId(fullPath);
	}

	inline void setCustomDialogText(const UnicodeString& customText) {
		dialogText.setCustomString(customText);
	}

	inline void setDialogText(const StringIdChatParameter& param) {
		dialogText = param;
	}

	inline StringIdChatParameter* getDialogText() {
		return &dialogText;
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
			text = opt->getOptionText().getDisplayedName();

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
	 * @param creature The creature receiving the message.
	 */
	void sendTo(CreatureObject* creature) {
		NpcConversationMessage* message = new NpcConversationMessage(creature, dialogText);

		//Encapsulate this logic better?
		StringList* optionsList = new StringList(creature);

		for (int i = 0; i < options.size(); ++i) {
			Reference<ConversationOption*> option = options.get(i);

			if (option == NULL)
				continue;

			optionsList->insertOption(option->getOptionText());
		}

		creature->sendMessage(message);
		creature->sendMessage(optionsList);

		ConversationSession* session = cast<ConversationSession* >(creature->getActiveSession(SessionFacadeType::CONVERSATION));
		if (session != NULL) {
			session->setLastConversationScreenName(screenID);
		}
	}

	inline String& getScreenID() {
		return screenID;
	}

	void readObject(LuaObject* luaObject) {
		screenID = luaObject->getStringField("id");
		dialogText.setStringId(luaObject->getStringField("leftDialog"));

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
};

}
}
}
}

using namespace server::zone::templates::mobile;

#endif /* CONVERSATIONSCREEN_H_ */
