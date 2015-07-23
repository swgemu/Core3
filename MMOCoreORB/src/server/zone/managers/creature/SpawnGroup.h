/*
 * SpawnGroup.h
 *
 *  Created on: Nov 3, 2010
 *      Author: da
 */

#ifndef SPAWNGROUP_H_
#define SPAWNGROUP_H_

#include "engine/engine.h"
#include "LairSpawn.h"

namespace server {
namespace zone {
namespace managers {
namespace creature {

class SpawnGroup : public Object {
protected:
	String templateName;

	int minLevelCeiling;

	Vector<Reference<LairSpawn*> > spawnList;

public:
	SpawnGroup() {
		minLevelCeiling = 20;
	}

	SpawnGroup(const String& tempName, LuaObject& group) {
		templateName = tempName;
		minLevelCeiling = group.getIntField("minLevelCeiling");

		LuaObject lairSpawns = group.getObjectField("lairSpawns");

		for (int i = 1; i <= lairSpawns.getTableSize(); ++i) {
			lua_rawgeti(lairSpawns.getLuaState(), -1, i);
			LuaObject spawn(lairSpawns.getLuaState());

			if (spawn.isValidTable()) {
				Reference<LairSpawn*> lairSpawn = new LairSpawn();
				lairSpawn->readObject(spawn);

				spawnList.add(lairSpawn);
			}

			spawn.pop();
		}

		lairSpawns.pop();

	}

	SpawnGroup(const SpawnGroup& gr) : Object() {
		templateName = gr.templateName;
		spawnList = gr.spawnList;
		minLevelCeiling = gr.minLevelCeiling;
	}

	virtual ~SpawnGroup() {}

	SpawnGroup& operator=(const SpawnGroup& gr) {
		if (this == &gr)
			return *this;

		templateName = gr.templateName;
		spawnList = gr.spawnList;
		minLevelCeiling = gr.minLevelCeiling;

		return *this;
	}

	String getTemplateName() const {
		return templateName;
	}

	Vector<Reference<LairSpawn*> >* getSpawnList() {
		return &spawnList;
	}

	void setTemplateName(String templateName) {
		this->templateName = templateName;
	}

	int getMinLevelCeiling() {
		return minLevelCeiling;
	}
};

}
}
}
}

#endif /* SPAWNGROUP_H_ */
