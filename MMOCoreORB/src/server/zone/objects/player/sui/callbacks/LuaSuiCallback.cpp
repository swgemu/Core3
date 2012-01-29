/*
 * LuaSuiCallback.cpp
 *
 *  Created on: Jan 28, 2012
 *      Author: xyborn
 */


#include "LuaSuiCallback.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/sui/SuiBox.h"

void LuaSuiCallback::run(CreatureObject* creature, SuiBox* sui, bool cancelPressed, Vector<UnicodeString>* args) {
		Lua* lua = DirectorManager::instance()->getLuaInstance();

		LuaFunction startScreenPlay(lua->getLuaState(), screenPlay, screenPlayCallback, 0);
		startScreenPlay << creature;
		startScreenPlay << sui;
		startScreenPlay << cancelPressed;

		for (int i = 0; i < args->size(); ++i) {
			startScreenPlay << args->get(i).toString();
		}

		lua->callFunction(&startScreenPlay);
}
