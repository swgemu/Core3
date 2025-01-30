/*
 * LuaMissionObject.cpp
 *
 * Created on: 2024-12-29
 * Author: Hakry
*/

#include "server/zone/objects/mission/LuaMissionObject.h"
#include "server/zone/objects/mission/MissionObject.h"

const char LuaMissionObject::className[] = "LuaMissionObject";

Luna<LuaMissionObject>::RegType LuaMissionObject::Register[] = {
	{ "_setObject", &LuaMissionObject::_setObject },
	{ "_getObject", &LuaIntangibleObject::_getObject },
	{ "setTemplateStrings", &LuaMissionObject::setTemplateStrings },
	{ "setTypeCRC", &LuaMissionObject::setTypeCRC },
	{ "setQuestType", &LuaMissionObject::setQuestType },
	{ "setQuestName", &LuaMissionObject::setQuestName },
	{ "setFaction", &LuaMissionObject::setFaction },
	{ "setCreatorName", &LuaMissionObject::setCreatorName },
	{ "setMissionTitle", &LuaMissionObject::setMissionTitle },
	{ "setMissionDescription", &LuaMissionObject::setMissionDescription },
	{ "setStartPosition", &LuaMissionObject::setStartPosition },
	{ "setEndPosition", &LuaMissionObject::setEndPosition },
	{ "setMissionTargetName", &LuaMissionObject::setMissionTargetName },
	{ "setTargetTemplate", &LuaMissionObject::setTargetTemplate },
	{ "setMissionNumber", &LuaMissionObject::setMissionNumber },
	{ "setRewardCredits", &LuaMissionObject::setRewardCredits },
	{ "setMissionDifficulty", &LuaMissionObject::setMissionDifficulty },
	{ "setSpaceDutyMission", &LuaMissionObject::setSpaceDutyMission },

	{ "getQuestCRC", &LuaMissionObject::getQuestCRC },
	{ "isSpaceDutyMission", &LuaMissionObject::isSpaceDutyMission },
	{ 0, 0}
};

LuaMissionObject::LuaMissionObject(lua_State *L) : LuaIntangibleObject(L) {
#ifdef DYNAMIC_CAST_LUAOBJECTS
	realObject = dynamic_cast<MissionObject*>(_getRealSceneObject());
	assert(!_getRealSceneObject() || realObject != nullptr);
#else
	realObject = static_cast<MissionObject*>(lua_touserdata(L, 1));
#endif
}

LuaMissionObject::~LuaMissionObject(){
}

int LuaMissionObject::_setObject(lua_State* L) {
	LuaIntangibleObject::_setObject(L);

#ifdef DYNAMIC_CAST_LUAOBJECTS
	auto obj = dynamic_cast<MissionObject*>(_getRealSceneObject());

	if (obj != realObject)
		realObject = obj;

	assert(!_getRealSceneObject() || realObject != nullptr);
#else
	auto obj = static_cast<MissionObject*>(lua_touserdata(L, -1));

	if (realObject != obj)
		realObject = obj;
#endif

	return 0;
}

int LuaMissionObject::setTemplateStrings(lua_State* L) {
	int numberOfArguments = lua_gettop(L) - 1;

	if (numberOfArguments != 2) {
		realObject->error() << "Improper number of arguments in LuaMissionObject::setTemplateStrings.";
		return 0;
	}

	String template2 = lua_tostring(L, -1);
	String template1 = lua_tostring(L, -2);

	Locker lock(realObject);

	realObject->setTemplateStrings(template1, template2);

	return 0;
}


int LuaMissionObject::setTypeCRC(lua_State* L) {
	int numberOfArguments = lua_gettop(L) - 1;

	if (numberOfArguments != 1) {
		realObject->error() << "Improper number of arguments in LuaMissionObject::setTypeCRC.";
		return 0;
	}

	int typeCRC = lua_tointeger(L, -1);

	Locker lock(realObject);

	realObject->setTypeCRC(typeCRC);

	return 0;
}

int LuaMissionObject::setQuestType(lua_State* L) {
	int numberOfArguments = lua_gettop(L) - 1;

	if (numberOfArguments != 1) {
		realObject->error() << "Improper number of arguments in LuaMissionObject::setQuestType.";
		return 0;
	}

	String questType = lua_tostring(L, -1);

	Locker lock(realObject);

	realObject->setQuestType(questType);

	return 0;
}

int LuaMissionObject::setQuestName(lua_State* L) {
	int numberOfArguments = lua_gettop(L) - 1;

	if (numberOfArguments != 1) {
		realObject->error() << "Improper number of arguments in LuaMissionObject::setQuestName.";
		return 0;
	}

	String questName = lua_tostring(L, -1);

	Locker lock(realObject);

	realObject->setQuestName(questName);

	return 0;
}

int LuaMissionObject::setFaction(lua_State* L) {
	int numberOfArguments = lua_gettop(L) - 1;

	if (numberOfArguments != 1) {
		realObject->error() << "Improper number of arguments in LuaMissionObject::setFaction.";
		return 0;
	}

	int factionCRC = lua_tointeger(L, -1);

	Locker lock(realObject);

	realObject->setFaction(factionCRC);

	return 0;
}

int LuaMissionObject::setCreatorName(lua_State* L) {
	int numberOfArguments = lua_gettop(L) - 1;

	if (numberOfArguments != 1) {
		realObject->error() << "Improper number of arguments in LuaMissionObject::setCreatorName.";
		return 0;
	}

	String creatorName = lua_tostring(L, -1);

	Locker lock(realObject);

	realObject->setCreatorName(creatorName);

	return 0;
}

int LuaMissionObject::setMissionTitle(lua_State* L) {
	int numberOfArguments = lua_gettop(L) - 1;

	if (numberOfArguments != 2) {
		realObject->error() << "Improper number of arguments in LuaMissionObject::setMissionTitle.";
		return 0;
	}

	String id = lua_tostring(L, -1);
	String file = lua_tostring(L, -2);

	Locker lock(realObject);

	realObject->setMissionTitle(file, id);

	return 0;
}

int LuaMissionObject::setMissionDescription(lua_State* L) {
	int numberOfArguments = lua_gettop(L) - 1;

	if (numberOfArguments != 2) {
		realObject->error() << "Improper number of arguments in LuaMissionObject::setMissionDescription.";
		return 0;
	}

	String id = lua_tostring(L, -1);
	String file = lua_tostring(L, -2);

	Locker lock(realObject);

	realObject->setMissionDescription(file, id);

	return 0;
}

int LuaMissionObject::setStartPosition(lua_State* L) {
	int numberOfArguments = lua_gettop(L) - 1;

	if (numberOfArguments != 4) {
		realObject->error() << "Improper number of arguments in LuaMissionObject::setStartPosition.";
		return 0;
	}

	float y = lua_tonumber(L, -1);
	float z =  lua_tonumber(L, -2);
	float x = lua_tonumber(L, -3);
	String zoneName =  lua_tostring(L, -4);

	Locker lock(realObject);

	realObject->setStartPosition(x, z, y, zoneName);

	return 0;
}

int LuaMissionObject::setEndPosition(lua_State* L) {
	int numberOfArguments = lua_gettop(L) - 1;

	if (numberOfArguments != 4) {
		realObject->error() << "Improper number of arguments in LuaMissionObject::setEndPosition.";
		return 0;
	}

	float y = lua_tonumber(L, -1);
	float z =  lua_tonumber(L, -2);
	float x = lua_tonumber(L, -3);
	String zoneName =  lua_tostring(L, -4);

	Locker lock(realObject);

	realObject->setEndPosition(x, z, y, zoneName);

	return 0;
}

int LuaMissionObject::setMissionTargetName(lua_State* L) {
	int numberOfArguments = lua_gettop(L) - 1;

	if (numberOfArguments != 1) {
		realObject->error() << "Improper number of arguments in LuaMissionObject::setMissionTargetName.";
		return 0;
	}

	String targetName = lua_tostring(L, -1);

	Locker lock(realObject);

	realObject->setMissionTargetName(targetName);

	return 0;
}

int LuaMissionObject::setTargetTemplate(lua_State* L) {
	int numberOfArguments = lua_gettop(L) - 1;

	if (numberOfArguments != 1) {
		realObject->error() << "Improper number of arguments in LuaMissionObject::setTargetTemplate.";
		return 0;
	}

	//TODO: Taret Temp Setting

	Locker lock(realObject);

	//realObject->setTargetTemplate(sharedTemplate);

	return 0;
}

int LuaMissionObject::setMissionNumber(lua_State* L) {
	int numberOfArguments = lua_gettop(L) - 1;

	if (numberOfArguments != 1) {
		realObject->error() << "Improper number of arguments in LuaMissionObject::setMissionNumber.";
		return 0;
	}

	int number = lua_tointeger(L, -1);

	Locker lock(realObject);

	realObject->setMissionNumber(number);

	return 0;
}

int LuaMissionObject::setRewardCredits(lua_State* L) {
	int numberOfArguments = lua_gettop(L) - 1;

	if (numberOfArguments != 1) {
		realObject->error() << "Improper number of arguments in LuaMissionObject::setRewardCredits.";
		return 0;
	}

	int reward = lua_tointeger(L, -1);

	Locker lock(realObject);

	realObject->setRewardCredits(reward);

	return 0;
}

int LuaMissionObject::setMissionDifficulty(lua_State* L) {
	int numberOfArguments = lua_gettop(L) - 1;

	if (numberOfArguments != 1) {
		realObject->error() << "Improper number of arguments in LuaMissionObject::setMissionDifficulty.";
		return 0;
	}

	int difficulty = lua_tointeger(L, -1);

	Locker lock(realObject);

	realObject->setMissionDifficulty(difficulty);

	return 0;
}

int LuaMissionObject::setSpaceDutyMission(lua_State* L) {
	Locker lock(realObject);

	realObject->setSpaceDutyMission();

	return 0;
}

int LuaMissionObject::getQuestCRC(lua_State* L) {
	lua_pushnumber(L, realObject->getQuestCRC());

	return 1;
}

int LuaMissionObject::isSpaceDutyMission(lua_State* L) {
	bool val = realObject->isSpaceDutyMission();

	lua_pushboolean(L, val);

	return 1;
}