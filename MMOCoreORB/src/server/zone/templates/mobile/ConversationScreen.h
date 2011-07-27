/*
 * ConversationScreen.h
 *
 *  Created on: Jul 8, 2011
 *      Author: crush
 */

#ifndef CONVERSATIONSCREEN_H_
#define CONVERSATIONSCREEN_H_

#include "engine/engine.h"
#include "server/chat/StringIdChatParameter.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/packets/object/NpcConversationMessage.h"
#include "server/zone/packets/object/StringList.h"

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
};

class ConversationScreen : public Object {
	String screenID;

	//TODO: Consider multiple dialog texts that can be displayed for screens
	StringIdChatParameter dialogText;

	Vector<Reference<ConversationOption*> > options;


public:
	ConversationScreen() {
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

		ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();

		if (ghost != NULL)
			ghost->setLastNpcConvMessStr(screenID);
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
