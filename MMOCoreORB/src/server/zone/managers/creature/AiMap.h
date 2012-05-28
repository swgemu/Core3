/*
 * AiMap.h
 *
 *  Created on: May 17, 2012
 *      Author: da
 */

#ifndef AIMAP_H_
#define AIMAP_H_

#include "engine/engine.h"

#include "server/zone/templates/AiTemplate.h"
#include "server/zone/objects/creature/ai/AiActor.h"

class AiMap : public Singleton<AiMap>, public Lua {
public:
	HashTable<String, Reference<AiTemplate*> > aiMap;

	AiMap() {
		aiMap.setNullValue(NULL);
	}

	~AiMap() {
	}

	void initialize() {
		Lua::init();

		registerFunctions();
		registerGlobals();

		Lua::runFile("scripts/mobile/ai/ai.lua");
		Lua::runFile("scripts/mobile/ai/serverobjects.lua");
	}

	int getSize() {
		return aiMap.size();
	}

	void put(String name, Reference<AiTemplate*> ait) {
		aiMap.put(name, ait);
	}

	Reference<AiTemplate*> get(String name) {
		return aiMap.get(name);
	}

private:
	void registerFunctions() {
		lua_register(getLuaState(), "addAiTemplate", addAiTemplate);
		lua_register(getLuaState(), "includeFile", includeFile);
	}

	void registerGlobals() {
		Lua::setGlobalInt("FINISHED", AiActor::FINISHED);
		Lua::setGlobalInt("UNFINISHED", AiActor::UNFINISHED);
		Lua::setGlobalInt("ATTACKED", AiActor::ATTACKED);
		Lua::setGlobalInt("INTERESTED", AiActor::INTERESTED);
		Lua::setGlobalInt("DEAD", AiActor::DEAD);
		Lua::setGlobalInt("ALMOSTDEAD", AiActor::ALMOSTDEAD);
		Lua::setGlobalInt("SCARED", AiActor::SCARED);
		Lua::setGlobalInt("FORGOT", AiActor::FORGOT);
		Lua::setGlobalInt("NONE", AiActor::NONE);
	}

	static int includeFile(lua_State* L) {
		String filename = Lua::getStringParameter(L);

		Lua::runFile("scripts/mobile/ai/" + filename, L);

		return 0;
	}

	static int addAiTemplate(lua_State* L) {
		String name = lua_tostring(L, -2);

		LuaObject obj(L);

		Reference<AiTemplate*> ait = new AiTemplate(name);
		ait->readObject(&obj);

		instance()->put(name, ait);

		return 0;
	}
};

#endif /* AIMAP_H_ */
