#include "ConversationTemplate.h"

#include "server/zone/managers/conversation/ConversationManager.h"

void ConversationTemplate::readObject(LuaObject* templateData) {
	initialScreenID = templateData->getStringField("initialScreen");

	String templateType;

	try {
		templateType = templateData->getStringField("templateType");
	}
	catch (Exception&) {
		Logger::info("Missing templateType.", true);
		templateType = "Normal";
	}

	if (templateType == "DeliverNPC") {
		conversationTemplateType = ConversationTemplateTypeDeliverMission;
	}
	else if (templateType == "InformantNPC") {
		conversationTemplateType = ConversationTemplateTypeInformantMission;
	}
	else if (templateType == "Lua") {
		conversationTemplateType = ConversationTemplateTypeLua;
	}
	else if (templateType == "Personality") {
		conversationTemplateType = ConversationTemplateTypePersonality;
	}
	else {
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
