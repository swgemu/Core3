/*
 * SpaceSpawnGroup.h
 *
 *  Created on: 2024-09-15
 *  Author: Hakry
 */

#ifndef SPACESPAWNGROUP_H_
#define SPACESPAWNGROUP_H_

#include "SpaceSpawn.h"

namespace server {
namespace zone {
namespace managers {
namespace ship {

class SpaceSpawnGroup : public Object {
protected:
	String templateName;

	Vector<Reference<SpaceSpawn*>> spawnList;

public:
	SpaceSpawnGroup() {
	}

	SpaceSpawnGroup(const String& tempName, LuaObject& shipSpawnGroups) {
		templateName = tempName;

		if (!shipSpawnGroups.isValidTable()) {
			return;
		}

		for (int i = 1; i <= shipSpawnGroups.getTableSize(); ++i) {
			lua_rawgeti(shipSpawnGroups.getLuaState(), -1, i);
			LuaObject shipSpawn(shipSpawnGroups.getLuaState());

			if (shipSpawn.isValidTable()) {
				Reference<SpaceSpawn*> spaceSpawn = new SpaceSpawn();
				spaceSpawn->readObject(shipSpawn);

				spawnList.add(spaceSpawn);
			}

			shipSpawn.pop();
		}

		shipSpawnGroups.pop();
	}

	SpaceSpawnGroup(const SpaceSpawnGroup& gr) : Object() {
		templateName = gr.templateName;
		spawnList = gr.spawnList;
	}

	virtual ~SpaceSpawnGroup() {
	}

	SpaceSpawnGroup& operator=(const SpaceSpawnGroup& gr) {
		if (this == &gr) {
			return *this;
		}

		templateName = gr.templateName;
		spawnList = gr.spawnList;

		return *this;
	}

	const String& getTemplateName() const {
		return templateName;
	}

	const Vector<Reference<SpaceSpawn*>>& getSpawnList() {
		return spawnList;
	}

	void setTemplateName(const String& templateName) {
		this->templateName = templateName;
	}
};

} // namespace ship
} // namespace managers
} // namespace zone
} // namespace server

#endif /* SPACESPAWNGROUP_H_ */
