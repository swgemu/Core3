/*
 * LuaConversationSession.h
 *
 *  Created on: 04/01/2012
 *      Author: victor
 */

#ifndef LUACONVERSATIONSESSION_H_
#define LUACONVERSATIONSESSION_H_


#include "engine/engine.h"
#include "engine/lua/Luna.h"

#include "server/zone/objects/player/sessions/ConversationSession.h"
#include "system/lang/ref/Reference.h"

namespace server {
namespace zone {
namespace objects {
namespace player {
namespace sessions {
class ConversationSession;
}  // namespace sessions
}  // namespace player
}  // namespace objects
}  // namespace zone
}  // namespace server

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
