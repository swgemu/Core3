#include "LuaQuestTask.h"

const char LuaQuestTask::className[] = "LuaQuestTask";

Luna<LuaQuestTask>::RegType LuaQuestTask::Register[] = {
		{ "_setObject", &LuaQuestTask::_setObject },
		{ "getAttachScript", &LuaQuestTask::getAttachScript },
		{ "getPlanetName", &LuaQuestTask::getPlanetName },
		{ "getLocationX", &LuaQuestTask::getLocationX },
		{ "getLocationY", &LuaQuestTask::getLocationY },
		{ "getLocationZ", &LuaQuestTask::getLocationZ },
		{ "getRadius", &LuaQuestTask::getRadius },
		{ 0, 0 }
};

LuaQuestTask::LuaQuestTask(lua_State *L) {
	realObject = static_cast<QuestTask*>(lua_touserdata(L, 1));
}

LuaQuestTask::~LuaQuestTask(){
}

int LuaQuestTask::_setObject(lua_State* L) {
	realObject = static_cast<QuestTask*>(lua_touserdata(L, -1));

	return 0;
}

int LuaQuestTask::getAttachScript(lua_State* L) {
	String text = realObject->getAttachScript();
	lua_pushstring(L, text.toCharArray());
	return 1;
}

int LuaQuestTask::getPlanetName(lua_State* L) {
	String text = realObject->getPlanetName();
	lua_pushstring(L, text.toCharArray());
	return 1;
}

int LuaQuestTask::getLocationX(lua_State* L) {
	lua_pushinteger(L, realObject->getLocationX());
	return 1;
}

int LuaQuestTask::getLocationY(lua_State* L) {
	lua_pushinteger(L, realObject->getLocationY());
	return 1;
}

int LuaQuestTask::getLocationZ(lua_State* L) {
	lua_pushinteger(L, realObject->getLocationZ());
	return 1;
}

int LuaQuestTask::getRadius(lua_State* L) {
	lua_pushinteger(L, realObject->getRadius());
	return 1;
}

