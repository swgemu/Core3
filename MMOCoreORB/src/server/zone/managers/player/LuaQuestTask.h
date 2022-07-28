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
		int getPrerequisiteTasks(lua_State* L);
		int getExclusionTasks(lua_State* L);
		int getAttachScript(lua_State* L);
		int getJournalEntryTitle(lua_State* L);
		int getJournalEntryDescription(lua_State* L);
		int getTasksOnComplete(lua_State* L);
		int getTasksOnFail(lua_State* L);
		int getTaskName(lua_State* L);
		int getIsVisible(lua_State* L);
		int getShowSystemMessages(lua_State* L);
		int getAllowRepeats(lua_State* L);
		int getMusicOnActivate(lua_State* L);
		int getTarget(lua_State* L);
		int getParameter(lua_State* L);
		int getGrantQuestOnComplete(lua_State* L);
		int getGrantQuestOnFail(lua_State* L);
		int getExperienceType(lua_State* L);
		int getExperienceAmount(lua_State* L);
		int getFactionName(lua_State* L);
		int getFactionAmount(lua_State* L);
		int getBankCredits(lua_State* L);
		int getItem(lua_State* L);
		int getPlanetName(lua_State* L);
		int getLocationX(lua_State* L);
		int getLocationY(lua_State* L);
		int getLocationZ(lua_State* L);
		int getRadius(lua_State* L);
		int getSignalName(lua_State* L);
		int getMinTime(lua_State* L);
		int getMaxTime(lua_State* L);
		int getCreatureType(lua_State* L);
		int getTargetServerTemplate(lua_State* L);
		int getSocialGroup(lua_State* L);
		int getRequiredRegion(lua_State* L);
		int getCount(lua_State* L);
		int getMinDistance(lua_State* L);
		int getMaxDistance(lua_State* L);
		int getDirection(lua_State* L);
		int getRewardCredits(lua_State* L);
		int getLootItemName(lua_State* L);
		int getLootItemsRequired(lua_State* L);
		int getLootDropPercent(lua_State* L);

	private:
		Reference<QuestTask*> realObject;
	};

}
}
}
}

using namespace server::zone::managers::player;


#endif /* LUAQUESTTASK_H_ */
