/*
 * LuaConversationSession.cpp
 *
 *  Created on: 04/01/2012
 *      Author: victor
 */

#include "LuaConversationSession.h"
#include "server/zone/objects/player/sessions/ConversationSession.h"

const char LuaConversationSession::className[] = "LuaConversationSession";

Luna<LuaConversationSession>::RegType LuaConversationSession::Register[] = {
		{ "_setObject", &LuaConversationSession::_setObject },
		{ "setLastConversationScreen", &LuaConversationSession::setLastConversationScreen },
		{ "getLastConversationScreen", &LuaConversationSession::getLastConversationScreen },
		{ 0, 0 }
};

LuaConversationSession::LuaConversationSession(lua_State *L) {
	realObject = static_cast<ConversationSession*>(lua_touserdata(L, 1));
}

LuaConversationSession::~LuaConversationSession(){
}

int LuaConversationSession::_setObject(lua_State* L) {
	realObject = static_cast<ConversationSession*>(lua_touserdata(L, -1));

	return 0;
}

int LuaConversationSession::setLastConversationScreen(lua_State* L) {
	/*const char* str = lua_tostring(L, -1);

	if (str != NULL) {
		String text(str);

		realObject->setLastConversationScreenName(text);
	}*/

	ConversationScreen* screen = (ConversationScreen*) lua_touserdata(L, -1);

	realObject->setLastConversationScreen(screen);

	return 0;
}

int LuaConversationSession::getLastConversationScreen(lua_State* L) {
	ConversationScreen* screen = realObject->getLastConversationScreen();

	//lua_pushstring(L, text.toCharArray());

	if (screen == NULL)
		lua_pushnil(L);
	else
		lua_pushlightuserdata(L, screen);

	return 1;
}
