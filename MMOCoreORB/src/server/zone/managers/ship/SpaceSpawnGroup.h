/*
 * SpaceSpawnGroup.h
 *
 *  Created on: Nov 3, 2010
 *      Author: da
 */

#ifndef SPACESPAWNGROUP_H_
#define SPACESPAWNGROUP_H_

// #include "LairSpawn.h"

namespace server {
namespace zone {
namespace managers {
namespace ship {

class SpaceSpawnGroup : public Object {
protected:
	String templateName;

	Vector<uint32> spawnList;

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
				//Reference<LairSpawn*> lairSpawn = new LairSpawn();
				//lairSpawn->readObject(spawn);

				//spawnList.add(lairSpawn);
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

	const Vector<uint32>& getSpawnList() {
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
