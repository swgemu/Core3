#ifndef LUAQUESTINFO_H_
#define LUAQUESTINFO_H_

#include "server/zone/managers/player/QuestInfo.h"
#include "engine/lua/Lua.h"

namespace server {
namespace zone {
namespace managers {
namespace player {

	class LuaQuestInfo {
	public:
		static const char className[];
		static Luna<LuaQuestInfo>::RegType Register[];

		LuaQuestInfo(lua_State *L);
		~LuaQuestInfo();

		int _setObject(lua_State* L);
		int shouldSendSystemMessage(lua_State* L);
		int getQuestName(lua_State* L);
		int getQuestParent(lua_State* L);
		int getQuestParameter(lua_State* L);
		int getJournalSummary(lua_State* L);
		int getAttachScript(lua_State* L);
		int getTaskOnComplete(lua_State* L);
		int getTaskOnFail(lua_State* L);
		int getQuestTarget(lua_State* L);

	private:
		Reference<QuestInfo*> realObject;
	};

}
}
}
}

using namespace server::zone::managers::player;


#endif /* LUAQUESTINFO_H_ */
