#include "LuaQuestTasks.h"

const char LuaQuestTasks::className[] = "LuaQuestTasks";

Luna<LuaQuestTasks>::RegType LuaQuestTasks::Register[] = {
		{ "_setObject", &LuaQuestTasks::_setObject },
		{ "getNumberOfTasks", &LuaQuestTasks::getNumberOfTasks },
		{ "getTask", &LuaQuestTasks::getTask },
		{ 0, 0 }
};

LuaQuestTasks::LuaQuestTasks(lua_State *L) {
	realObject = static_cast<QuestTasks*>(lua_touserdata(L, 1));
}

LuaQuestTasks::~LuaQuestTasks(){
}

int LuaQuestTasks::_setObject(lua_State* L) {
	realObject = static_cast<QuestTasks*>(lua_touserdata(L, -1));

	return 0;
}

int LuaQuestTasks::getNumberOfTasks(lua_State* L) {
	lua_pushinteger(L, realObject->getNumberOfTasks());
	return 1;
}

int LuaQuestTasks::getTask(lua_State* L) {
	int taskNumber = lua_tointeger(L, -1);
	if (taskNumber >= 0 && taskNumber < realObject->getNumberOfTasks()) {
		lua_pushlightuserdata(L, realObject->getTask(taskNumber));
		return 1;
	} else {
		Logger::console.error("Trying to retrieve non existen QuestTask index " + String::valueOf(taskNumber) + ", valid indexes = 0 - " + String::valueOf(realObject->getNumberOfTasks()));
		return 0;
	}
}
