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

private:
	// The pointer to the 'real object' defined in object.cc
	Reference<ConversationScreen*> realObject;
};


#endif /* LUACONVERSATIONSCREEN_H_ */
