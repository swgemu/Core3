#ifndef LUAQUESTTASK_H_
#define LUAQUESTTASK_H_

#include "server/zone/managers/player/QuestTasks.h"
#include "engine/lua/Lua.h"

namespace server {
namespace zone {
namespace managers {
namespace player {

	class LuaQuestTask {
	public:
		static const char className[];
		static Luna<LuaQuestTask>::RegType Register[];

		LuaQuestTask(lua_State *L);
		~LuaQuestTask();

		int _setObject(lua_State* L);
		int getAttachScript(lua_State* L);
		int getPlanetName(lua_State* L);
		int getLocationX(lua_State* L);
		int getLocationY(lua_State* L);
		int getLocationZ(lua_State* L);
		int getRadius(lua_State* L);

	private:
		Reference<QuestTask*> realObject;
	};

}
}
}
}

using namespace server::zone::managers::player;


#endif /* LUAQUESTTASK_H_ */
