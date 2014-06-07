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

	float wanderRadius;
	int commandLevel;

	unsigned int type;

	Vector<Reference<LairSpawn*> > lairList;
	int maxSpawnLimit;

public:
	SpawnGroup() {}

	SpawnGroup(const String& tempName, LuaObject& group) {
		templateName = tempName;
		wanderRadius = group.getFloatField("wanderRadius");
		commandLevel = group.getIntField("commandLevel");
		type = group.getIntField("type");
		maxSpawnLimit = group.getIntField("maxSpawnLimit");
		LuaObject lairSpawns = group.getObjectField("lairSpawns");

		for (int i = 1; i <= lairSpawns.getTableSize(); ++i) {
			lua_rawgeti(lairSpawns.getLuaState(), -1, i);
			LuaObject spawn(lairSpawns.getLuaState());

			if (spawn.isValidTable()) {
				Reference<LairSpawn*> lairSpawn = new LairSpawn();
				lairSpawn->readObject(spawn);

				lairList.add(lairSpawn);
			}

			spawn.pop();
		}

		lairSpawns.pop();

	}

	SpawnGroup(const SpawnGroup& gr) : Object() {
		templateName = gr.templateName;
		wanderRadius = gr.wanderRadius;
		commandLevel = gr.commandLevel;
		type = gr.type;
		lairList = gr.lairList;
		maxSpawnLimit = gr.maxSpawnLimit;
	}

	virtual ~SpawnGroup() {}

	SpawnGroup& operator=(const SpawnGroup& gr) {
		if (this == &gr)
			return *this;

		templateName = gr.templateName;
		wanderRadius = gr.wanderRadius;
		commandLevel = gr.commandLevel;
		type = gr.type;
		lairList = gr.lairList;
		maxSpawnLimit = gr.maxSpawnLimit;

		return *this;
	}

	String getTemplateName() const {
		return templateName;
	}

	float getWanderRadius() const {
		return wanderRadius;
	}

	int getCommandLevel() const {
		return commandLevel;
	}

	unsigned int getType() const {
		return type;
	}

	Vector<Reference<LairSpawn*> >* getLairList() {
		return &lairList;
	}

	int getMaxSpawnLimit() {
		return maxSpawnLimit;
	}

	void setWanderRadius(float wanderRadius) {
		this->wanderRadius = wanderRadius;
	}

	void setTemplateName(String templateName) {
		this->templateName = templateName;
	}

	void setCommandLevel(int commandLevel) {
		this->commandLevel = commandLevel;
	}

	void setType(unsigned int type) {
		this->type = type;
	}

};

}
}
}
}

#endif /* SPAWNGROUP_H_ */
