#include "LuaSkill.h"

const char LuaSkill::className[] = "LuaSkill";

Luna<LuaSkill>::RegType LuaSkill::Register[] = {
		{ "_setObject", &LuaSkill::_setObject },
		{ "getName", &LuaSkill::getName },
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
