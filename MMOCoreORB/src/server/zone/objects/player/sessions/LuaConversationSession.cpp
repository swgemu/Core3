/*
 * LuaConversationSession.cpp
 *
 *  Created on: 04/01/2012
 *      Author: victor
 */

#include "LuaConversationSession.h"
#include "ConversationSession.h"

const char LuaConversationSession::className[] = "LuaConversationSession";

Luna<LuaConversationSession>::RegType LuaConversationSession::Register[] = {
		{ "_setObject", &LuaConversationSession::_setObject },
		{ "setLastConversationScreenName", &LuaConversationSession::setLastConversationScreenName },
		{ "getLastConversationScreenName", &LuaConversationSession::getLastConversationScreenName },
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

int LuaConversationSession::setLastConversationScreenName(lua_State* L) {
	const char* str = lua_tostring(L, -1);

	if (str != NULL) {
		String text(str);

		realObject->setLastConversationScreenName(text);
	}

	return 0;
}

int LuaConversationSession::getLastConversationScreenName(lua_State* L) {
	String text = realObject->getLastConversationScreenName();

	lua_pushstring(L, text.toCharArray());

	return 1;
}
