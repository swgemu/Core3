/*
 * PermissionLevelList.h
 *
 *  Created on: May 10, 2012
 *      Author: Itac
 */

#ifndef PERMISSIONLEVELLIST_H_
#define PERMISSIONLEVELLIST_H_

#include "engine/engine.h"

class PermissionLevel : public Object{
protected:
	int permissionLevel, priviledgeFlag;
	String name;
	UnicodeString tag;
	Vector<String> skillList;

public:
	PermissionLevel() {
		permissionLevel = 0;
		priviledgeFlag = 0;
	}

	PermissionLevel(int staffLev, String levelName, String staffTag, int flag, Vector<String> skills) : Object() {
		permissionLevel = staffLev;
		name = levelName;
		tag = staffTag;
		priviledgeFlag = flag;
		skillList = skills;
	}

	~PermissionLevel() {
	}

	PermissionLevel(const PermissionLevel& al) : Object() {
		permissionLevel = al.permissionLevel;
		tag  = al.tag;
		priviledgeFlag = al.priviledgeFlag;
		skillList = al.skillList;
		name = al.name;
	}

	int getPermissionLevel() {
		return permissionLevel;
	}

	int getPriviledgeFlag() {
		return priviledgeFlag;
	}

	String getName() {
		return name;
	}

	UnicodeString getTag() {
		return tag;
	}

	Vector<String>* getSkillList() {
		return &skillList;
	}


};

class PermissionLevelList : public Singleton<PermissionLevelList>, public VectorMap<uint32, Reference< PermissionLevel*> > {
protected:
	static Lua lua;
	VectorMap<String, int> permissionNames;

public:

	PermissionLevelList() {
	}

	~PermissionLevelList() {
	}

	static void loadLevels() {
		lua.init();
		lua_register(lua.getLuaState(), "includeFile", &includeFile);
		lua_register(lua.getLuaState(), "addLevel", &addLevel);
		lua.runFile("scripts/staff/levels/serverobjects.lua");
	}

	static int addLevel(lua_State* L) {
		LuaObject obj(L);
		PermissionLevelList::instance()->loadLevel(&obj);
		obj.pop();

		return 0;
	}

	static int includeFile(lua_State* L) {
		String filename = lua.getStringParameter(L);
		lua.runFile("scripts/staff/" + filename,  L);

		return 0;
	}

	void loadLevel(LuaObject* luaLevel) {

		if (!luaLevel->isValidTable()) {
			return;
		}

		Vector<String> skills;

		uint32 levelNum = luaLevel->getIntField("level");

		String name = luaLevel->getStringField("name");

		String tag = luaLevel->getStringField("tag");

		int priviledgeFlag = luaLevel->getIntField("flag");

		LuaObject skillsTable = luaLevel->getObjectField("skills");
		for(int i = 1; i <= skillsTable.getTableSize(); ++i) {
			skills.add(skillsTable.getStringAt(i));
		}
		skillsTable.pop();
		put(levelNum, new PermissionLevel(levelNum, name, tag, priviledgeFlag, skills));
		permissionNames.put(name, levelNum);
	}

	UnicodeString getPermissionTag(uint32 permissionLevel) {
		if(!contains(permissionLevel))
			return "";
		else
			return get(permissionLevel)->getTag();
	}

	Vector<String>* getPermissionSkills(uint32 permissionLevel) {
		if(!contains(permissionLevel))
			return NULL;
		else
			return get(permissionLevel)->getSkillList();
	}

	int getPriviledgeFlag(uint32 permissionLevel) {
		if(!contains(permissionLevel))
			return 0;
		else
			return get(permissionLevel)->getPriviledgeFlag();
	}

	int getLevelNumber(String name) {
		return permissionNames.get(name);
	}

	bool containsLevel(String name) {
		return permissionNames.contains(name);
	}
};

#endif //PERMISSIONLEVELLIST_H_
