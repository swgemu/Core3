#ifndef LUAQUESTTASKS_H_
#define LUAQUESTTASKS_H_

#include "server/zone/managers/player/QuestTasks.h"
#include "engine/lua/Lua.h"

namespace server {
namespace zone {
namespace managers {
namespace player {

	class LuaQuestTasks {
	public:
		static const char className[];
		static Luna<LuaQuestTasks>::RegType Register[];

		LuaQuestTasks(lua_State *L);
		~LuaQuestTasks();

		int _setObject(lua_State* L);
		int getNumberOfTasks(lua_State* L);
		int getTask(lua_State* L);

	private:
		Reference<QuestTasks*> realObject;
	};

}
}
}
}

using namespace server::zone::managers::player;


#endif /* LUAQUESTTASKS_H_ */
