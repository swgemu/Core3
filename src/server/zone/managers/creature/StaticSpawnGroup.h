/*
 * StaticSpawnGroup.h
 *
 *  Created on: Nov 13, 2010
 *      Author: da
 */

#ifndef STATICSPAWNGROUP_H_
#define STATICSPAWNGROUP_H_

#include "SpawnGroup.h"

namespace server {
namespace zone {
namespace managers {
namespace creature {

class SpawnCoordinate : public Coordinate, public Quaternion {
protected:
	String templateName;

public:
	SpawnCoordinate() {}

	SpawnCoordinate(const SpawnCoordinate& cr) : Object(), Coordinate(cr), Quaternion(cr) {
		templateName = cr.templateName;
	}

	virtual ~SpawnCoordinate() {}

	SpawnCoordinate& operator=(const SpawnCoordinate& cr) {
		if (this == &cr)
			return *this;

		templateName = cr.templateName;

		return *this;
	}

	String getTemplateName() const {
		return templateName;
	}

	void setTemplateName(String templateName) {
		this->templateName = templateName;
	}

};

class StaticSpawnGroup : public SpawnGroup {
protected:
	Vector<SpawnCoordinate> spawnMap;

	int respawnTime;

	float x, y, z;
	uint64 cellID;

public:
	StaticSpawnGroup() {}

	StaticSpawnGroup(const StaticSpawnGroup& gr) : SpawnGroup(gr) {
		spawnMap = gr.spawnMap;
		respawnTime = gr.respawnTime;
		x = gr.x;
		y = gr.y;
		z = gr.z;
		cellID = gr.cellID;
	}

	StaticSpawnGroup(String tempName, LuaObject group) : SpawnGroup(tempName, group) {
		respawnTime = group.getIntField("respawnTime");
		x = group.getFloatField("x");
		y = group.getFloatField("y");
		z = group.getFloatField("z");
		cellID = group.getLongField("cellID");

		LuaObject spawns = group.getObjectField("spawns");
		if (spawns.isValidTable()) {
			lua_State* L = spawns.getLuaState();

			for (int i = 1; i <= spawns.getTableSize(); ++i) {
				lua_rawgeti(L, -1, i);
				LuaObject templ(L);

				if (templ.isValidTable()) {
					if (templ.getTableSize() >= 8) {
						SpawnCoordinate coord;

						coord.setTemplateName(templ.getStringAt(1));

						coord.setPosition(templ.getFloatAt(2), templ.getFloatAt(4), templ.getFloatAt(3));

						coord.set(templ.getFloatAt(5), templ.getFloatAt(6), templ.getFloatAt(7), templ.getFloatAt(8));

						spawnMap.add(coord);
					}
				}

				templ.pop();
			}
		}

		spawns.pop();
	}

	virtual ~StaticSpawnGroup() {}

	StaticSpawnGroup& operator=(const StaticSpawnGroup& gr) {
		if (this == &gr)
			return *this;

		spawnMap = gr.spawnMap;
		respawnTime = gr.respawnTime;
		x = gr.x;
		y = gr.y;
		z = gr.z;
		cellID = gr.cellID;

		return *this;
	}

	Vector<SpawnCoordinate> getSpawnList() {
		return spawnMap;
	}

	int getRespawnTime() const {
		return respawnTime;
	}

	float getX() const {
		return x;
	}

	float getY() const {
		return y;
	}

	float getZ() const {
		return z;
	}

	uint64 getCellID() const {
		return cellID;
	}

	bool isStaticGroup() {
		return true;
	}
};

}
}
}
}

#endif /* STATICSPAWNGROUP_H_ */
