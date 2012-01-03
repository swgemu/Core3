/*
 * LuaConversationScreen.cpp
 *
 *  Created on: 03/01/2012
 *      Author: victor
 */

#include "LuaConversationScreen.h"


const char LuaConversationScreen::className[] = "LuaConversationScreen";

Luna<LuaConversationScreen>::RegType LuaConversationScreen::Register[] = {
		{ "_setObject", &LuaConversationScreen::_setObject },
		{ "getOptionText", &LuaConversationScreen::getOptionText},
		{ "getOptionLink", &LuaConversationScreen::getOptionLink},
		{ "getOptionCount", &LuaConversationScreen::getOptionCount},
		{ "sendTo", &LuaConversationScreen::sendTo},
		{ "getScreenID", &LuaConversationScreen::getScreenID},
		{ 0, 0 }
};

LuaConversationScreen::LuaConversationScreen(lua_State *L) {
	realObject = static_cast<ConversationScreen*>(lua_touserdata(L, 1));
}

LuaConversationScreen::~LuaConversationScreen(){
}

int LuaConversationScreen::_setObject(lua_State* L) {
	realObject = static_cast<ConversationScreen*>(lua_touserdata(L, -1));

	return 0;
}

int LuaConversationScreen::getOptionText(lua_State* L) {
	int idx = lua_tonumber(L, -1);

	String text;

	try {
		text = realObject->getOptionText(idx);
	} catch (Exception& e) {

	}

	lua_pushstring(L, text.toCharArray());

	return 1;
}


int LuaConversationScreen::getOptionLink(lua_State* L) {
	//String getOptionLink(int idx) const {
	int idx = lua_tonumber(L, -1);

	String text;

	try {
		text = realObject->getOptionLink(idx);
	} catch (Exception& e) {

	}

	lua_pushstring(L, text.toCharArray());

	return 1;
}

int LuaConversationScreen::getOptionCount(lua_State* L) {
	int size = realObject->getOptionCount();

	lua_pushnumber(L, size);

	return 1;
}

int LuaConversationScreen::sendTo(lua_State* L) {
	//void sendTo(CreatureObject* player, CreatureObject* npc) {

	CreatureObject* player = (CreatureObject*) lua_touserdata(L, -2);
	CreatureObject* npc = (CreatureObject*) lua_touserdata(L, -1);

	realObject->sendTo(player, npc);

	return 0;
}

int LuaConversationScreen::getScreenID(lua_State* L) {
	//inline String& getScreenID() {

	String text = realObject->getScreenID();

	lua_pushstring(L, text.toCharArray());

	return 1;
}


