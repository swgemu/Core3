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
		{ "cloneScreen", &LuaConversationScreen::cloneScreen},
		{ "addOption", &LuaConversationScreen::addOption},
		{ "setDialogTextTT", &LuaConversationScreen::setDialogTextTT},
		{ "setDialogTextTO", &LuaConversationScreen::setDialogTextTO},
		{ "setDialogTextTU", &LuaConversationScreen::setDialogTextTU},
		{ "setDialogTextDF", &LuaConversationScreen::setDialogTextDF},
		{ "setDialogTextDI", &LuaConversationScreen::setDialogTextDI},
		{ 0, 0 }
};

LuaConversationScreen::LuaConversationScreen(lua_State *L) {
	realObject = reinterpret_cast<ConversationScreen*>(lua_touserdata(L, 1));
}

LuaConversationScreen::~LuaConversationScreen(){
}

int LuaConversationScreen::_setObject(lua_State* L) {
	realObject = reinterpret_cast<ConversationScreen*>(lua_touserdata(L, -1));

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

	String text;

	if (realObject != NULL)
		realObject->getScreenID();
	else
		text = "";

	lua_pushstring(L, text.toCharArray());

	return 1;
}

int LuaConversationScreen::cloneScreen(lua_State* L) {
	lua_pushlightuserdata(L, realObject->cloneScreen());

	return 1;
}

int LuaConversationScreen::addOption(lua_State* L) {
	//void addOption(const String& optionText, const String& linkedScreenID) {

	String linked = lua_tostring(L, -1);
	String text = lua_tostring(L, -2);

	realObject->addOption(text, linked);

	return 0;
}

void LuaConversationScreen::setDialogText(StringIdParameter* param, lua_State* L) {
	if (lua_gettop(L) == 0)
		return;

	if (lua_isnumber(L, -1)) {
		uint64 integer = lua_tointeger(L, -1);

		param->set(integer);

	} else {
		const char* str1 = lua_tostring(L, -1);
		const char* str2 = NULL;

		if (lua_gettop(L) > 1 && lua_isstring(L, -2)) {
			str2 = lua_tostring(L, -2);
		}

		if (str2 != NULL) {
			param->set(str2, str1);
		} else {
			param->set(str1);
		}
	}
}

int LuaConversationScreen::setDialogTextTT(lua_State* L) {
	StringIdChatParameter* param = realObject->getDialogText();

	setDialogText(param->getTT(), L);

	return 0;
}

int LuaConversationScreen::setDialogTextTO(lua_State* L) {
	StringIdChatParameter* param = realObject->getDialogText();

	setDialogText(param->getTO(), L);

	return 0;
}

int LuaConversationScreen::setDialogTextTU(lua_State* L) {
	StringIdChatParameter* param = realObject->getDialogText();

	setDialogText(param->getTU(), L);

	return 0;
}

int LuaConversationScreen::setDialogTextDF(lua_State* L) {
	float num = lua_tonumber(L, -1);

	realObject->setDialogTextDF(num);

	return 0;
}

int LuaConversationScreen::setDialogTextDI(lua_State* L) {
	int num = lua_tointeger(L, -1);

	realObject->setDialogTextDI(num);

	return 0;
}
