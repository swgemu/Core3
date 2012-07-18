/*
 * LuaConversationScreen.h
 *
 *  Created on: 03/01/2012
 *      Author: victor
 */

#ifndef LUACONVERSATIONSCREEN_H_
#define LUACONVERSATIONSCREEN_H_

#include "ConversationScreen.h"

#include "engine/engine.h"

class LuaConversationScreen {
public:
	// Constants
	static const char className[];
	static Luna<LuaConversationScreen>::RegType Register[];

	// Initialize the pointer
	LuaConversationScreen(lua_State *L);
	~LuaConversationScreen();

	int _setObject(lua_State* L);
	// Methods we will need to use
	int getOptionText(lua_State* L);
	int getOptionLink(lua_State* L);
	int getOptionCount(lua_State* L);
	int sendTo(lua_State* L);
	int getScreenID(lua_State* L);
	int cloneScreen(lua_State* L);
	int addOption(lua_State* L);
	int setDialogTextTT(lua_State* L);
	int setDialogTextTO(lua_State* L);
	int setDialogTextTU(lua_State* L);
	int setDialogTextDF(lua_State* L);
	int setDialogTextDI(lua_State* L);
	int setCustomDialogText(lua_State* L);

private:
	//removed Reference<> because we are cloning in lua and returning
	ConversationScreen* realObject;

	static void setDialogText(StringIdParameter* param, lua_State* L);
};


#endif /* LUACONVERSATIONSCREEN_H_ */
