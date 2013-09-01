/*
 * LuaBehavior.cpp
 *
 *  Created on: Sep 1, 2013
 *      Author: swgemu
 */

#include "LuaBehavior.h"
#include "server/zone/objects/creature/ai/LuaAiActor.h"
#include "server/zone/managers/director/DirectorManager.h"
#include "engine/engine.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace ai {
namespace bt {

LuaBehavior::LuaBehavior(String name) {
	this->className = name;
}

LuaBehavior::~LuaBehavior() {
}

int LuaBehavior::update(AiActor* actor) {
	// re-use director maager
	Lua* lua = DirectorManager::instance()->getLuaInstance();
	LuaFunction update(lua->getLuaState(), this->className, "update", 1);
	update << actor;
	// run the function and fetch result
	lua_State* L = lua->callFunction(&update);
	int rc = lua_tonumber(L, -1);
	return rc;
}
void LuaBehavior::onInitialize(AiActor* actor) {
	// re-use director maager
	Lua* lua = DirectorManager::instance()->getLuaInstance();
	LuaFunction initialize(lua->getLuaState(), this->className, "OnInitialize", 0);
	initialize << actor;
	// run the function and fetch result
	lua->callFunction(&initialize);
}
void LuaBehavior::onTerminate(AiActor* actor, int s) {
	// re-use director maager
	Lua* lua = DirectorManager::instance()->getLuaInstance();
	LuaFunction terminate(lua->getLuaState(), this->className, "OnTerminiate", 0);
	terminate << actor;
	terminate << s;
	// run the function
	lua->callFunction(&terminate);
}


}
}
}
}
}
}
