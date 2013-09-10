#ifndef DUNGEONLIST_H_
#define DUNGEONLIST_H_

#include "engine/engine.h"
#include "Dungeon.h"

class DungeonList : public VectorMap<String, Reference<Dungeon*> >, public ReadWriteLock {
	String zoneName;
public:

	DungeonList() : VectorMap<String, Reference<Dungeon*> >() {
		setNoDuplicateInsertPlan();
		setNullValue(NULL);
	}

	void readLuaObject(LuaObject* luaObject) {
		wlock();

		if (!luaObject->isValidTable())
			return;

		for (int i = 1; i <= luaObject->getTableSize(); ++i) {
			lua_State* L = luaObject->getLuaState();
			lua_rawgeti(L, -1, i);

			LuaObject dungeonObject(L);

			Reference<Dungeon*> dun = new Dungeon(zoneName);

			put(dun->getName(), dun);
			dun->readLuaObject(&dungeonObject);

			dungeonObject.pop();
		}

		unlock();
	}

	inline void setZoneName(const String& name) {
		zoneName = name;
	}
};

#endif /* DUNGEONLIST_H_ */
