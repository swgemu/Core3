/*
 * CitySpecializationMap.h
 *
 *  Created on: Jul 20, 2012
 *      Author: swgemu
 */

#ifndef CITYSPECIALIZATIONMAP_H_
#define CITYSPECIALIZATIONMAP_H_

#include "CitySpecialization.h"

class CitySpecializationMap : public HashTable<String, CitySpecialization> {
public:
	void readObject(LuaObject* luaObject) {
		if (!luaObject->isValidTable())
			return;

		for (int i = 1; i <= luaObject->getTableSize(); ++i) {
			LuaObject spec = luaObject->getObjectAt(i);

			if (spec.isValidTable()) {
				CitySpecialization citySpec;
				citySpec.readObject(&spec);

				put(citySpec.getName(), citySpec);
			}

			spec.pop();
		}
	}
};

#endif /* CITYSPECIALIZATIONMAP_H_ */
