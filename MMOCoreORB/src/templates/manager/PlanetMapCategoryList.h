/*
 * PlanetMapCategoryList.h
 *
 *  Created on: Apr 26, 2011
 *      Author: polonel
 */

#ifndef PLANETMAPCATEGORYLIST_H_
#define PLANETMAPCATEGORYLIST_H_

#include "engine/engine.h"

#include "system/util/HashTable.h"

class PlanetMapCategory;

class PlanetMapCategoryList : public HashTable<int, Reference<PlanetMapCategory*> > {
	int hash(const int& key) const override {
		return key; //this is the string crc so no need to rehash
	}

	int hash(const String& key) const {
		return key.hashCode();
	}

public:
	PlanetMapCategoryList() : HashTable<int, Reference<PlanetMapCategory*> >(256) {
		setNullValue(nullptr);
	}

	bool containsKey(const String& key) const {
		return HashTable<int, Reference<PlanetMapCategory*> >::containsKey(key.hashCode());
	}

	const Reference<PlanetMapCategory*>& get(const String& key) const {
		return HashTable<int, Reference<PlanetMapCategory*> >::get(key.hashCode());
	}

	const Reference<PlanetMapCategory*>& get(const int& key) const {
		return HashTable<int, Reference<PlanetMapCategory*> >::get(key);
	}

	Reference<PlanetMapCategory*> put(const String& key, const Reference<PlanetMapCategory*>& value) {
		return HashTable<int, Reference<PlanetMapCategory*> >::put(key.hashCode(), value);
	}
};

#endif /* PLANETMAPCATEGORYLIST_H_ */
