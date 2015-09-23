#include "LuaQuestInfo.h"

const char LuaQuestInfo::className[] = "LuaQuestInfo";

Luna<LuaQuestInfo>::RegType LuaQuestInfo::Register[] = {
		{ "_setObject", &LuaQuestInfo::_setObject },
		{ "shouldSendSystemMessage", &LuaQuestInfo::shouldSendSystemMessage },
		{ "getQuestName", &LuaQuestInfo::getQuestName },
		{ "getQuestParent", &LuaQuestInfo::getQuestParent },
		{ "getQuestParameter", &LuaQuestInfo::getQuestParameter },
		{ "getJournalSummary", &LuaQuestInfo::getJournalSummary },
		{ "getAttachScript", &LuaQuestInfo::getAttachScript },
		{ "getTaskOnComplete", &LuaQuestInfo::getTaskOnComplete },
		{ "getTaskOnFail", &LuaQuestInfo::getTaskOnFail },
		{ "getQuestTarget", &LuaQuestInfo::getQuestTarget },
		{ 0, 0 }
};

LuaQuestInfo::LuaQuestInfo(lua_State *L) {
	realObject = static_cast<QuestInfo*>(lua_touserdata(L, 1));
}

LuaQuestInfo::~LuaQuestInfo(){
}

int LuaQuestInfo::_setObject(lua_State* L) {
	realObject = static_cast<QuestInfo*>(lua_touserdata(L, -1));

	return 0;
}

int LuaQuestInfo::shouldSendSystemMessage(lua_State* L) {
	lua_pushboolean(L, realObject->shouldSendSystemMessage());

	return 1;
}

int LuaQuestInfo::getQuestName(lua_State* L) {
	String text = realObject->getQuestName();
	lua_pushstring(L, text.toCharArray());
	return 1;
}

int LuaQuestInfo::getQuestParent(lua_State* L) {
	String text = realObject->getQuestParent();
	lua_pushstring(L, text.toCharArray());
	return 1;
}

int LuaQuestInfo::getQuestParameter(lua_State* L) {
	String text = realObject->getQuestParameter();
	lua_pushstring(L, text.toCharArray());
	return 1;
}

int LuaQuestInfo::getJournalSummary(lua_State* L) {
	String text = realObject->getJournalSummary();
	lua_pushstring(L, text.toCharArray());
	return 1;
}

int LuaQuestInfo::getAttachScript(lua_State* L) {
	String text = realObject->getAttachScript();
	lua_pushstring(L, text.toCharArray());
	return 1;
}

int LuaQuestInfo::getTaskOnComplete(lua_State* L) {
	String text = realObject->getTaskOnComplete();
	lua_pushstring(L, text.toCharArray());
	return 1;
}

int LuaQuestInfo::getTaskOnFail(lua_State* L) {
	String text = realObject->getTaskOnFail();
	lua_pushstring(L, text.toCharArray());
	return 1;
}

int LuaQuestInfo::getQuestTarget(lua_State* L) {
	String text = realObject->getQuestTarget();
	lua_pushstring(L, text.toCharArray());
	return 1;
}
