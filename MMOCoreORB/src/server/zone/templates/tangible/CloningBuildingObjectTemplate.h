/*
 * CloningBuildingObject.h
 *
 *  Created on: 23/06/2010
 *      Author: victor
 */

#ifndef CLONINGBUILDINGOBJECTTEMPLATE_H_
#define CLONINGBUILDINGOBJECTTEMPLATE_H_

#include "SharedBuildingObjectTemplate.h"
#include "server/zone/objects/building/cloning/CloneSpawnPoint.h"

class CloningBuildingObjectTemplate : public SharedBuildingObjectTemplate {
	Vector<CloneSpawnPoint> spawningPoints;

public:
	CloningBuildingObjectTemplate() {
	}

	~CloningBuildingObjectTemplate() {
	}

	void readObject(LuaObject* templateData) {
		SharedBuildingObjectTemplate::readObject(templateData);

		spawningPoints.removeAll();

		LuaObject luaItemList = templateData->getObjectField("spawningPoints");

		int size = luaItemList.getTableSize();

		lua_State* L = luaItemList.getLuaState();

		for (int i = 0; i < size; ++i) {
			lua_rawgeti(L, -1, i + 1);
			LuaObject a(L);

			CloneSpawnPoint point;
			point.parseFromLua(&a);

			//System::out << "adding spawning point" << endl;

			spawningPoints.add(point);

			a.pop();
		}

		luaItemList.pop();
	}

	CloneSpawnPoint* getRandomSpawnPoint() {
		if (spawningPoints.size() == 0)
			return NULL;

		return &spawningPoints.get(System::random(spawningPoints.size() - 1));
	}

	bool isCloningBuildingObjectTemplate() {
		return true;
	}

	inline Vector<CloneSpawnPoint>* getCloneSpawnPoints() {
		return &spawningPoints;
	}
};


#endif /* CLONINGBUILDINGOBJECT_H_ */
