/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef LUASTRINGIDCHATPARAMETER_H_
#define LUASTRINGIDCHATPARAMETER_H_

#include "engine/engine.h"
#include "server/chat/StringIdChatParameter.h"

namespace server {
namespace chat {

class LuaStringIdChatParameter {
	Reference<StringIdChatParameter*> realObject;
public:
	// Constants
	static const char className[];
	static Luna<LuaStringIdChatParameter>::RegType Register[];

	// Initialize the string
	LuaStringIdChatParameter(lua_State *L);
	~LuaStringIdChatParameter();

	int _setObject(lua_State* L);
	int _getObject(lua_State* L);
	int setTT(lua_State* L);
	int setTU(lua_State* L);
	int setTO(lua_State* L);
	int setDI(lua_State* L);
	int setDF(lua_State* L);
};

}
}

using namespace server::chat;

#endif /* LUASTRINGIDCHATPARAMETER_H_ */
