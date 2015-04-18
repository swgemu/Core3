/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef CONVERSATIONTEMPLATE_H_
#define CONVERSATIONTEMPLATE_H_

#include "engine/engine.h"

#include "ConversationScreen.h"

#include "server/zone/managers/conversation/ConversationManager.h"

namespace server {
namespace zone {
namespace templates {
namespace mobile {

class ConversationTemplate : public Object, public Logger {
public:
	enum ConversationTemplateType {
		ConversationTemplateTypeNormal,
		ConversationTemplateTypeTrainer,
		ConversationTemplateTypeDeliverMission,
		ConversationTemplateTypeInformantMission,
		ConversationTemplateTypeLua,
		ConversationTemplateTypePersonality
	};
protected:
	String initialScreenID;
	VectorMap<String, Reference<ConversationScreen*> > screens;
	ConversationTemplateType conversationTemplateType;
	uint32 crc;
	String luaClassHandler;

public:

	ConversationTemplate(uint32 hashCode) : Logger("ConversationTemplate") {
		screens.setNoDuplicateInsertPlan();
		crc = hashCode;

		conversationTemplateType = ConversationTemplateTypeNormal;
	}

	virtual ~ConversationTemplate() {

	}

	void readObject(LuaObject* templateData) {
		initialScreenID = templateData->getStringField("initialScreen");

		String templateType;

		try {
			templateType = templateData->getStringField("templateType");
		}
		catch (Exception&) {
			Logger::info("Missing templateType.", true);
			templateType = "Normal";
		}

		if (templateType == "Trainer") {
			conversationTemplateType = ConversationTemplateTypeTrainer;
		} else if (templateType == "DeliverNPC") {
			conversationTemplateType = ConversationTemplateTypeDeliverMission;
		} else if (templateType == "InformantNPC") {
			conversationTemplateType = ConversationTemplateTypeInformantMission;
		} else if (templateType == "Lua") {
			conversationTemplateType = ConversationTemplateTypeLua;
		} else if (templateType == "Personality") {
			conversationTemplateType = ConversationTemplateTypePersonality;
		} else {
			conversationTemplateType = ConversationTemplateTypeNormal;
		}

		luaClassHandler = templateData->getStringField("luaClassHandler");

		LuaObject screensTable = templateData->getObjectField("screens");

		for (int i = 1; i <= screensTable.getTableSize(); ++i) {
			lua_rawgeti(templateData->getLuaState(), -1, i);

			LuaObject luaObj(templateData->getLuaState());

			Reference<ConversationScreen*> screen = new ConversationScreen();
			screen->readObject(&luaObj);

			screens.put(screen->getScreenID(), screen);

			luaObj.pop();
		}

		screensTable.pop();

		ConversationManager::instance()->getConversationObserver(crc);
	}

	String getLuaClassHandler() {
		return luaClassHandler;
	}

	ConversationScreen* getInitialScreen() {
		return screens.get(initialScreenID);
	}

	ConversationScreen* getScreen(const String& screenID) {
		return screens.get(screenID);
	}

	ConversationTemplateType getConversationTemplateType() {
		return conversationTemplateType;
	}

	uint32 getCRC() {
		return crc;
	}
};

}
}
}
}

using namespace server::zone::templates::mobile;

#endif /* CONVERSATIONTEMPLATE_H_ */
