/*
 * LuaConversationSession.h
 *
 *  Created on: 04/01/2012
 *      Author: victor
 */

#ifndef LUACONVERSATIONSESSION_H_
#define LUACONVERSATIONSESSION_H_


#include "ConversationSession.h"

#include "engine/engine.h"

class LuaConversationSession {
public:
	// Constants
	static const char className[];
	static Luna<LuaConversationSession>::RegType Register[];

	// Initialize the pointer
	LuaConversationSession(lua_State *L);
	~LuaConversationSession();

	int _setObject(lua_State* L);
	// Methods we will need to use
	int setLastConversationScreen(lua_State* L);
	int getLastConversationScreen(lua_State* L);


private:
	// The pointer to the 'real object' defined in object.cc
	Reference<ConversationSession*> realObject;
};



#endif /* LUACONVERSATIONSESSION_H_ */
