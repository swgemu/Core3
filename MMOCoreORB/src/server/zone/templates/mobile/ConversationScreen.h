/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

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
	UnicodeString customOption;
	String linkedScreenID;

public:
	ConversationOption(const StringIdChatParameter& opttext, const String& screenid) {
		optionText = opttext;
		linkedScreenID = screenid;
	}

	ConversationOption(const UnicodeString& customopt, const String& screenid) {
		customOption = customopt;
		linkedScreenID = screenid;
	}

	inline String& getLinkedScreenID() {
		return linkedScreenID;
	}

	inline StringIdChatParameter& getOptionText() {
		return optionText;
	}

	inline UnicodeString& getCustomOption() {
		return customOption;
	}

	inline String getDisplayedName() {
		if (customOption.isEmpty())
			return optionText.getFullPath();
		else
			return customOption.toString();
	}

	inline bool isLinked() {
		return !linkedScreenID.isEmpty();
	}

	inline void setOptionText(const StringIdChatParameter& optionText) {
		this->optionText = optionText;
	}
};

class ConversationScreen : public Object {
	String screenID;

	//TODO: Consider multiple dialog texts that can be displayed for screens
	StringIdChatParameter dialogText;

	UnicodeString customText;

	Vector<Reference<ConversationOption*> > options;

	bool stopConversation, readOnly;

public:
	ConversationScreen() {
		stopConversation = false;
		readOnly = false;
	}

	/**
	 * Copy constructor.
	 */
	ConversationScreen(const ConversationScreen& objectToCopy) : Object() {
		screenID = objectToCopy.screenID;
		dialogText = objectToCopy.dialogText;
		options = objectToCopy.options;
		stopConversation = objectToCopy.stopConversation;
		readOnly = objectToCopy.readOnly;
		customText = objectToCopy.customText;
	}

	ConversationScreen* cloneScreen() {
		ConversationScreen* clone = new ConversationScreen(*this);
		clone->readOnly = false;

		return clone;
	}

	/**
	 * Adds an option to this conversation screen.
	 * @param optionText The text to be displayed for the option.
	 * @param linkedScreenID The ID of the screen this option is linked.
	 */
	void addOption(const String& optionText, const String& linkedScreenID) {
		if (readOnly)
			throw Exception("Can't modify read only Conversation Screen!");

		if (optionText.beginsWith("@"))
			options.add(new ConversationOption(StringIdChatParameter(optionText), linkedScreenID));
		else
			options.add(new ConversationOption(UnicodeString(optionText), linkedScreenID));
	}

	void removeOption(int idx) {
		if (readOnly)
			throw Exception("Can't modify read only Conversation Screen!");

		options.remove(idx);
	}

	void removeAllOptions() {
		if (readOnly)
			throw Exception("Can't modify read only Conversation Screen!");

		options.removeAll();
	}

	ConversationOption* getOption(int idx) {
		return options.get(idx);
	}

	String getOptionText(int idx) const {
		String text;

		Reference<ConversationOption*> opt = options.get(idx);

		if (opt != NULL)
			text = opt->getOptionText().getFullPath();

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
		NpcConversationMessage* message;

		if (customText.isEmpty())
			message = new NpcConversationMessage(player, dialogText);
		else
			message = new NpcConversationMessage(player, customText);

		//Encapsulate this logic better?
		StringList* optionsList = new StringList(player);

		for (int i = 0; i < options.size(); ++i) {
			Reference<ConversationOption*> option = options.get(i);

			if (option == NULL)
				continue;

			optionsList->insertOption(option->getDisplayedName());
		}

		player->sendMessage(message);
		player->sendMessage(optionsList);

		ConversationScreen* screenToSave = this;

		//Check if the conversation should be stopped.
		if (stopConversation) {
			player->sendMessage(new StopNpcConversation(player, npc->getObjectID()));
			npc->notifyObservers(ObserverEventType::STOPCONVERSATION, player);
			screenToSave = NULL;
		}

		Reference<ConversationSession*> session = player->getActiveSession(SessionFacadeType::CONVERSATION).castTo<ConversationSession* >();
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
		customText = luaObject->getStringField("customDialogText");

		if (luaObject->getStringField("stopConversation").toLowerCase() == "true") {
			stopConversation = true;
		} else {
			stopConversation = false;
		}

		LuaObject optionsTable = luaObject->getObjectField("options");

		for (int i = 1; i <= optionsTable.getTableSize(); ++i) {
			lua_rawgeti(luaObject->getLuaState(), -1, i);

			LuaObject luaObj(luaObject->getLuaState());

			String optionString = luaObj.getStringAt(1);
			String linkedId = luaObj.getStringAt(2);

			Reference<ConversationOption*> option = NULL;

			if (optionString.beginsWith("@"))
				option = new ConversationOption(StringIdChatParameter(optionString), linkedId);
			else
				option = new ConversationOption(UnicodeString(optionString), linkedId);

			options.add(option);

			luaObj.pop();
		}

		optionsTable.pop();

		readOnly = true;
	}

	template<class T>
	inline void setDialogTextTT(const T& obj) {
		if (readOnly)
			throw Exception("Can't modify read only Conversation Screen!");

		dialogText.setTT(obj);
	}

	inline void setDialogTextTT(const String& file, const String& id) {
		if (readOnly)
			throw Exception("Can't modify read only Conversation Screen!");

		dialogText.setTT(file, id);
	}

	template<class T>
	inline void setDialogTextTO(const T& obj) {
		if (readOnly)
			throw Exception("Can't modify read only Conversation Screen!");

		dialogText.setTO(obj);
	}

	inline void setDialogTextTO(const String& file, const String& id) {
		if (readOnly)
			throw Exception("Can't modify read only Conversation Screen!");

		dialogText.setTO(file, id);
	}

	template<class T>
	inline void setDialogTextTU(const T& obj) {
		if (readOnly)
			throw Exception("Can't modify read only Conversation Screen!");

		dialogText.setTO(obj);
	}

	inline void setDialogTextTU(const String& file, const String& id) {
		if (readOnly)
			throw Exception("Can't modify read only Conversation Screen!");

		dialogText.setTU(file, id);
	}

	inline void setDialogTextDI(uint32 val) {
		if (readOnly)
			throw Exception("Can't modify read only Conversation Screen!");

		dialogText.setDI(val);
	}

	inline void setDialogTextDF(float val) {
		if (readOnly)
			throw Exception("Can't modify read only Conversation Screen!");

		dialogText.setDF(val);
	}

	inline void setDialogText(const String& fullPath) {
		if (readOnly)
			throw Exception("Can't modify read only Conversation Screen!");

		dialogText.setStringId(fullPath);
	}

	inline void setCustomDialogText(const UnicodeString& custom) {
		if (readOnly)
			throw Exception("Can't modify read only Conversation Screen!");

		customText = custom;
	}

	inline void setDialogText(const StringIdChatParameter& param) {
		if (readOnly)
			throw Exception("Can't modify read only Conversation Screen!");

		dialogText = param;
	}

	inline void setStopConversation(bool stopConversation) {
		if (readOnly)
			throw Exception("Can't modify read only Conversation Screen!");

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
