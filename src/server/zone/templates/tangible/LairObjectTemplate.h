/*
 * LairObjectTemplate.h
 *
 *  Created on: 13/07/2010
 *      Author: victor
 */

#ifndef LAIROBJECTTEMPLATE_H_
#define LAIROBJECTTEMPLATE_H_

#include "../SharedTangibleObjectTemplate.h"

class LairObjectTemplate : public SharedTangibleObjectTemplate {
	SortedVector<uint32> objectsToSpawn;
	int maxObjectsToSpawn;

public:
	LairObjectTemplate() {
		objectsToSpawn.setNoDuplicateInsertPlan();
	}

	~LairObjectTemplate() {
	}

	void readObject(LuaObject* templateData) {
		SharedTangibleObjectTemplate::readObject(templateData);

		maxObjectsToSpawn = templateData->getIntField("maxObjectsToSpawn");

		LuaObject luaItemList = templateData->getObjectField("objectsToSpawn");

		for (int i = 1; i <= luaItemList.getTableSize(); ++i) {
			String templateToSpawn = luaItemList.getStringAt(i);

			objectsToSpawn.put(templateToSpawn.hashCode());
		}

		luaItemList.pop();
    }

	inline SortedVector<uint32>* getObjectsToSpawn() {
		return &objectsToSpawn;
	}

	inline int getMaxObjectsToSpawn() {
		return maxObjectsToSpawn;
	}

	bool isLairObjectTemplate() {
		return true;
	}
};

#endif /* LAIROBJECTTEMPLATE_H_ */
