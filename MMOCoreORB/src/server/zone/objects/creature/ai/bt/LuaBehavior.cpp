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

Status LuaBehavior::update(AiActor* actor) {
	// re-use director maager
	Lua* lua = DirectorManager::instance()->getLuaInstance();
	// setup a callable actor
	LuaAiActor* lactor = new LuaAiActor(NULL);
	lactor->realObject = actor;
	LuaFunction update(lua->getLuaState(), this->className, "update", 1);
	update << lactor;
	// run the fnction and fetch result
	lua_State* L = lua->callFunction(&update);
	int rc = lua_tonumber(L, -1);
	// delete our agent proxy
	delete lactor;

	return static_cast<Status>(rc);
}
void LuaBehavior::onInitialize(AiActor* actor) {
	// re-use director maager
	Lua* lua = DirectorManager::instance()->getLuaInstance();
	// setup a callable actor
	LuaAiActor* lactor = new LuaAiActor(NULL);
	lactor->realObject = actor;
	LuaFunction initialize(lua->getLuaState(), this->className, "OnInitialize", 0);
	initialize << lactor;
	// run the fnction and fetch result
	lua->callFunction(&initialize);
	// delete our agent proxy
	delete lactor;

}
void LuaBehavior::onTerminate(AiActor* actor, Status s) {
	// re-use director maager
	Lua* lua = DirectorManager::instance()->getLuaInstance();
	// setup a callable actor
	LuaAiActor* lactor = new LuaAiActor(NULL);
	lactor->realObject = actor;
	LuaFunction terminate(lua->getLuaState(), this->className, "OnTerminiate", 0);
	terminate << lactor;
	terminate << s;
	// run the function
	lua->callFunction(&terminate);
	// delete our agent proxy
	delete lactor;
}


}
}
}
}
}
}
