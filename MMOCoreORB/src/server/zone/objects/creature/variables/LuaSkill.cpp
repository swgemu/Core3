#include "LuaSkill.h"

const char LuaSkill::className[] = "LuaSkill";

Luna<LuaSkill>::RegType LuaSkill::Register[] = {
		{ "_setObject", &LuaSkill::_setObject },
		{ "getName", &LuaSkill::getName },
		{ "getMoneyRequired", &LuaSkill::getMoneyRequired },
		{ "getSkillPointsRequired", &LuaSkill::getSkillPointsRequired },
		{ "getSkillsRequired", &LuaSkill::getSkillsRequired },
		{ "getXpType", &LuaSkill::getXpType },
		{ "getXpCost", &LuaSkill::getXpCost },
		{ 0, 0 }
};

LuaSkill::LuaSkill(lua_State *L) {
	realObject = reinterpret_cast<Skill*>(lua_touserdata(L, 1));
}

LuaSkill::~LuaSkill(){
}

int LuaSkill::_setObject(lua_State* L) {
	realObject = reinterpret_cast<Skill*>(lua_touserdata(L, -1));

	return 0;
}

int LuaSkill::getName(lua_State* L) {
	String text = realObject->getSkillName();
	lua_pushstring(L, text.toCharArray());
	return 1;
}

int LuaSkill::getMoneyRequired(lua_State* L) {
	int amount = realObject->getMoneyRequired();
	lua_pushinteger(L, amount);
	return 1;
}

int LuaSkill::getSkillPointsRequired(lua_State* L) {
	int amount = realObject->getSkillPointsRequired();
	lua_pushinteger(L, amount);
	return 1;
}

int LuaSkill::getSkillsRequired(lua_State* L) {
	auto requiredSkills = realObject->getSkillsRequired();

	if (requiredSkills->size() == 0) {
		lua_pushnil(L);
	} else {
		lua_newtable(L);

		for (int i = 0; i < requiredSkills->size(); i++) {
			lua_pushstring(L, requiredSkills->get(i).toCharArray());

			lua_rawseti(L, -2, i + 1);
		}
	}

	return 1;
}

int LuaSkill::getXpType(lua_State* L) {
	String text = realObject->getXpType();
	lua_pushstring(L, text.toCharArray());
	return 1;
}

int LuaSkill::getXpCost(lua_State* L) {
	int amount = realObject->getXpCost();
	lua_pushinteger(L, amount);
	return 1;
}
