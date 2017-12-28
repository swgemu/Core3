/*
 * LuaSuiCallback.cpp
 *
 *  Created on: Jan 28, 2012
 *      Author: xyborn
 */

#include "LuaSuiCallback.h"

#include "engine/lua/Lua.h"
#include "engine/lua/LuaFunction.h"
#include "server/zone/managers/director/DirectorManager.h"
#include "system/lang/UnicodeString.h"
#include "system/util/Vector.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
class CreatureObject;
}  // namespace creature
namespace player {
namespace sui {
class SuiBox;
}  // namespace sui
}  // namespace player
}  // namespace objects
}  // namespace zone
}  // namespace server

void LuaSuiCallback::run(CreatureObject* creature, SuiBox* sui, uint32 eventIndex, Vector<UnicodeString>* args) {
	Lua* lua = DirectorManager::instance()->getLuaInstance();

	LuaFunction startScreenPlay(lua->getLuaState(), screenPlay, screenPlayCallback, 0);
	startScreenPlay << creature;
	startScreenPlay << sui;
	startScreenPlay << eventIndex;

	for (int i = 0; i < args->size(); ++i) {
		startScreenPlay << args->get(i).toString().toCharArray();
	}

	startScreenPlay.callFunction();
}
