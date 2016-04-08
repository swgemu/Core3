/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.
*/

#include "PlayerCreatureTemplate.h"

void PlayerCreatureTemplate::parseVariableData(const String& varName, LuaObject* templateData) {
	lua_State* state = templateData->getLuaState();
	if (varName == "defaultLanguage")
		defaultLanguage = Lua::getIntParameter(state);
	else if (varName == "startingSkills") {
		startingSkills->removeAll();

		LuaObject skills(state);

		for (int i = 1; i <= skills.getTableSize(); ++i) {
			startingSkills->add(skills.getStringAt(i));
		}

		skills.pop();
	} else if (varName == "startingItems") {
		startingItems->removeAll();

		LuaObject items(state);

		for (int i = 1; i <= items.getTableSize(); ++i) {
			startingItems->add(items.getStringAt(i));
		}

		items.pop();
	} else {
		templateData->pop();
	}
}

void PlayerCreatureTemplate::readObject(LuaObject* templateData) {
	SharedCreatureObjectTemplate::readObject(templateData);

	lua_State* L = templateData->getLuaState();

	if (!templateData->isValidTable())
		return;

	int i = 0;

	lua_pushnil(L);  
	while (lua_next(L, -2) != 0) {
		// 'key' is at index -2 and 'value' at index -1 
		//printf("%s - %s\n",
		//		lua_tostring(L, -2), lua_typename(L, lua_type(L, -1)));

		int type = lua_type(L, -2);

		if (type == LUA_TSTRING) {
			size_t len = 0;
			const char* varName = lua_tolstring(L, -2, &len);

			parseVariableData(varName, templateData);
		} else {
			lua_pop(L, 1);
		}
		
		++i;
	}
	
	return;
}

