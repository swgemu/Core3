#include "LuaQuestTask.h"

const char LuaQuestTask::className[] = "LuaQuestTask";

Luna<LuaQuestTask>::RegType LuaQuestTask::Register[] = {
		{ "_setObject", &LuaQuestTask::_setObject },
		{ "getPrerequisiteTasks", &LuaQuestTask::getPrerequisiteTasks },
		{ "getExclusionTasks", &LuaQuestTask::getExclusionTasks },
		{ "getAttachScript", &LuaQuestTask::getAttachScript },
		{ "getJournalEntryTitle", &LuaQuestTask::getJournalEntryTitle },
		{ "getJournalEntryDescription", &LuaQuestTask::getJournalEntryDescription },
		{ "getTasksOnComplete", &LuaQuestTask::getTasksOnComplete },
		{ "getTasksOnFail", &LuaQuestTask::getTasksOnFail },
		{ "getTaskName", &LuaQuestTask::getTaskName },
		{ "getIsVisible", &LuaQuestTask::getIsVisible },
		{ "getShowSystemMessages", &LuaQuestTask::getShowSystemMessages },
		{ "getAllowRepeats", &LuaQuestTask::getAllowRepeats },
		{ "getMusicOnActivate", &LuaQuestTask::getMusicOnActivate },
		{ "getTarget", &LuaQuestTask::getTarget },
		{ "getParameter", &LuaQuestTask::getParameter },
		{ "getGrantQuestOnComplete", &LuaQuestTask::getGrantQuestOnComplete },
		{ "getGrantQuestOnFail", &LuaQuestTask::getGrantQuestOnFail },
		{ "getExperienceType", &LuaQuestTask::getExperienceType },
		{ "getExperienceAmount", &LuaQuestTask::getExperienceAmount },
		{ "getFactionName", &LuaQuestTask::getFactionName },
		{ "getFactionAmount", &LuaQuestTask::getFactionAmount },
		{ "getBankCredits", &LuaQuestTask::getBankCredits },
		{ "getItem", &LuaQuestTask::getItem },
		{ "getPlanetName", &LuaQuestTask::getPlanetName },
		{ "getLocationX", &LuaQuestTask::getLocationX },
		{ "getLocationY", &LuaQuestTask::getLocationY },
		{ "getLocationZ", &LuaQuestTask::getLocationZ },
		{ "getRadius", &LuaQuestTask::getRadius },
		{ "getSignalName", &LuaQuestTask::getSignalName },
		{ "getMinTime", &LuaQuestTask::getMinTime },
		{ "getMaxTime", &LuaQuestTask::getMaxTime },
		{ "getCreatureType", &LuaQuestTask::getCreatureType },
		{ "getTargetServerTemplate", &LuaQuestTask::getTargetServerTemplate },
		{ "getSocialGroup", &LuaQuestTask::getSocialGroup },
		{ "getRequiredRegion", &LuaQuestTask::getRequiredRegion },
		{ "getCount", &LuaQuestTask::getCount },
		{ "getMinDistance", &LuaQuestTask::getMinDistance },
		{ "getMaxDistance", &LuaQuestTask::getMaxDistance },
		{ "getDirection", &LuaQuestTask::getDirection },
		{ "getRewardCredits", &LuaQuestTask::getRewardCredits },
		{ "getLootItemName", &LuaQuestTask::getLootItemName },
		{ "getLootItemsRequired", &LuaQuestTask::getLootItemsRequired },
		{ "getLootDropPercent", &LuaQuestTask::getLootDropPercent },
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

int LuaQuestTask::getPrerequisiteTasks(lua_State* L) {
	const Vector<int> tasks = realObject->getPrerequisiteTasks();

	lua_newtable(L);

	for (int i = 0; i < tasks.size(); i++) {
		lua_pushnumber(L, tasks.get(i));

		lua_rawseti(L, -2, i + 1);
	}

	return 1;
}

int LuaQuestTask::getExclusionTasks(lua_State* L) {
	const Vector<int> tasks = realObject->getExclusionTasks();

	lua_newtable(L);

	for (int i = 0; i < tasks.size(); i++) {
		lua_pushnumber(L, tasks.get(i));

		lua_rawseti(L, -2, i + 1);
	}

	return 1;
}

int LuaQuestTask::getAttachScript(lua_State* L) {
	String text = realObject->getAttachScript();
	lua_pushstring(L, text.toCharArray());
	return 1;
}

int LuaQuestTask::getJournalEntryTitle(lua_State* L) {
	String text = realObject->getJournalEntryTitle();
	lua_pushstring(L, text.toCharArray());
	return 1;
}

int LuaQuestTask::getJournalEntryDescription(lua_State* L) {
	String text = realObject->getJournalEntryDescription();
	lua_pushstring(L, text.toCharArray());
	return 1;
}

int LuaQuestTask::getTasksOnComplete(lua_State* L) {
	const Vector<int> tasks = realObject->getTasksOnComplete();

	lua_newtable(L);

	for (int i = 0; i < tasks.size(); i++) {
		lua_pushnumber(L, tasks.get(i));

		lua_rawseti(L, -2, i + 1);
	}

	return 1;
}

int LuaQuestTask::getTasksOnFail(lua_State* L) {
	const Vector<int> tasks = realObject->getTasksOnFail();

	lua_newtable(L);

	for (int i = 0; i < tasks.size(); i++) {
		lua_pushnumber(L, tasks.get(i));

		lua_rawseti(L, -2, i + 1);
	}

	return 1;
}

int LuaQuestTask::getTaskName(lua_State* L) {
	String text = realObject->getTaskName();
	lua_pushstring(L, text.toCharArray());
	return 1;
}

int LuaQuestTask::getIsVisible(lua_State* L) {
	lua_pushboolean(L, realObject->getIsVisible());

	return 1;
}

int LuaQuestTask::getShowSystemMessages(lua_State* L) {
	lua_pushboolean(L, realObject->getShowSystemMessages());

	return 1;
}

int LuaQuestTask::getAllowRepeats(lua_State* L) {
	lua_pushboolean(L, realObject->getAllowRepeats());

	return 1;
}

int LuaQuestTask::getMusicOnActivate(lua_State* L) {
	String text = realObject->getMusicOnActivate();
	lua_pushstring(L, text.toCharArray());
	return 1;
}

int LuaQuestTask::getTarget(lua_State* L) {
	String text = realObject->getTarget();
	lua_pushstring(L, text.toCharArray());
	return 1;
}

int LuaQuestTask::getParameter(lua_State* L) {
	String text = realObject->getParameter();
	lua_pushstring(L, text.toCharArray());
	return 1;
}

int LuaQuestTask::getGrantQuestOnComplete(lua_State* L) {
	String text = realObject->getGrantQuestOnComplete();
	lua_pushstring(L, text.toCharArray());
	return 1;
}

int LuaQuestTask::getGrantQuestOnFail(lua_State* L) {
	String text = realObject->getGrantQuestOnFail();
	lua_pushstring(L, text.toCharArray());
	return 1;
}

int LuaQuestTask::getExperienceType(lua_State* L) {
	String text = realObject->getExperienceType();
	lua_pushstring(L, text.toCharArray());
	return 1;
}

int LuaQuestTask::getExperienceAmount(lua_State* L) {
	lua_pushinteger(L, realObject->getExperienceAmount());
	return 1;
}

int LuaQuestTask::getFactionName(lua_State* L) {
	String text = realObject->getFactionName();
	lua_pushstring(L, text.toCharArray());
	return 1;
}

int LuaQuestTask::getFactionAmount(lua_State* L) {
	lua_pushinteger(L, realObject->getFactionAmount());
	return 1;
}

int LuaQuestTask::getBankCredits(lua_State* L) {
	lua_pushinteger(L, realObject->getBankCredits());
	return 1;
}

int LuaQuestTask::getItem(lua_State* L) {
	String text = realObject->getItem();
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

int LuaQuestTask::getSignalName(lua_State* L) {
	String text = realObject->getSignalName();
	lua_pushstring(L, text.toCharArray());
	return 1;
}

int LuaQuestTask::getMinTime(lua_State* L) {
	lua_pushinteger(L, realObject->getMinTime());
	return 1;
}

int LuaQuestTask::getMaxTime(lua_State* L) {
	lua_pushinteger(L, realObject->getMaxTime());
	return 1;
}

int LuaQuestTask::getCreatureType(lua_State* L) {
	String text = realObject->getCreatureType();
	lua_pushstring(L, text.toCharArray());
	return 1;
}

int LuaQuestTask::getTargetServerTemplate(lua_State* L) {
	String text = realObject->getTargetServerTemplate();
	lua_pushstring(L, text.toCharArray());
	return 1;
}

int LuaQuestTask::getSocialGroup(lua_State* L) {
	String text = realObject->getSocialGroup();
	lua_pushstring(L, text.toCharArray());
	return 1;
}

int LuaQuestTask::getRequiredRegion(lua_State* L) {
	String text = realObject->getRequiredRegion();
	lua_pushstring(L, text.toCharArray());
	return 1;
}

int LuaQuestTask::getCount(lua_State* L) {
	lua_pushinteger(L, realObject->getCount());
	return 1;
}

int LuaQuestTask::getMinDistance(lua_State* L) {
	lua_pushinteger(L, realObject->getMinDistance());
	return 1;
}

int LuaQuestTask::getMaxDistance(lua_State* L) {
	lua_pushinteger(L, realObject->getMaxDistance());
	return 1;
}

int LuaQuestTask::getDirection(lua_State* L) {
	String text = realObject->getDirection();
	lua_pushstring(L, text.toCharArray());
	return 1;
}

int LuaQuestTask::getRewardCredits(lua_State* L) {
	lua_pushinteger(L, realObject->getRewardCredits());
	return 1;
}

int LuaQuestTask::getLootItemName(lua_State* L) {
	String text = realObject->getLootItemName();
	lua_pushstring(L, text.toCharArray());
	return 1;
}

int LuaQuestTask::getLootItemsRequired(lua_State* L) {
	lua_pushinteger(L, realObject->getLootItemsRequired());
	return 1;
}

int LuaQuestTask::getLootDropPercent(lua_State* L) {
	lua_pushinteger(L, realObject->getLootDropPercent());
	return 1;
}
