/*
 * LuaConversationTemplate.cpp
 *
 *  Created on: 04/01/2012
 *      Author: victor
 */

#include "LuaConversationTemplate.h"
#include "ConversationScreen.h"

const char LuaConversationTemplate::className[] = "LuaConversationTemplate";

Luna<LuaConversationTemplate>::RegType LuaConversationTemplate::Register[] = {
		{ "_setObject", &LuaConversationTemplate::_setObject },
		{ "getScreen", &LuaConversationTemplate::getScreen},
		{ "getInitialScreen", &LuaConversationTemplate::getInitialScreen},
		{ 0, 0 }
};

LuaConversationTemplate::LuaConversationTemplate(lua_State *L) {
	realObject = static_cast<ConversationTemplate*>(lua_touserdata(L, 1));
}

LuaConversationTemplate::~LuaConversationTemplate(){
}

int LuaConversationTemplate::_setObject(lua_State* L) {
	realObject = static_cast<ConversationTemplate*>(lua_touserdata(L, -1));

	return 0;
}

int LuaConversationTemplate::getScreen(lua_State* L) {
	const char* str = lua_tostring(L, -1);
	ConversationScreen* screen = NULL;

	if (str != NULL) {
		String text(str);

		screen = realObject->getScreen(text);
	}

	lua_pushlightuserdata(L, screen);

	return 1;
}


int LuaConversationTemplate::getInitialScreen(lua_State* L) {
	ConversationScreen* screen = realObject->getInitialScreen();

	lua_pushlightuserdata(L, screen);

	return 1;
}
