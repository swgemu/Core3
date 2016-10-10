/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.
*/

#include "server/zone/managers/director/ScreenPlayObserver.h"
#include "DirectorManager.h"
#include "engine/lua/LuaPanicException.h"

int ScreenPlayObserverImplementation::notifyObserverEvent(uint32 eventType, Observable* observable, ManagedObject* arg1, int64 arg2) {
	int ret = 1;

	try {
		Lua* lua = DirectorManager::instance()->getLuaInstance();

		LuaFunction startScreenPlay(lua->getLuaState(), play, key, 1);
		startScreenPlay << observable;
		startScreenPlay << arg1;
		startScreenPlay << arg2;

		startScreenPlay.callFunction();

		if (lua_gettop(lua->getLuaState()) == 0) {
			Logger::console.error("ScreenPlayObserverImplementation::notifyObserverEvent didnt return a value from " + play + ":" + key);

			assert(0 && "no return value in  ScreenPlayObserverImplementation::notifyObserverEvent");

			return 1;
		}

		if (!lua_isnumber(lua->getLuaState(), -1)) {
			String msg = "ScreenPlayObserver " + play + ":" + key + "didnt return a valid value in an observer handler";
			Logger::console.error(msg);
			assert(0 && "Failed");
		}

		ret = lua->getIntParameter(lua->getLuaState());

	} catch (LuaPanicException& panic) {
		Logger::console.error("Panic exception: " + panic.getMessage() + " while trying to run SceenPlayObserver: " + play + ":" + key);
	}

	//1 remove observer, 0 keep observer

	return ret;
}
