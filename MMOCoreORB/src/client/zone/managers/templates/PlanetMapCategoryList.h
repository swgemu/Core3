/*
 * PlanetMapCategoryList.h
 *
 *  Created on: Apr 26, 2011
 *      Author: polonel
 */

#ifndef PLANETMAPCATEGORYLIST_H_
#define PLANETMAPCATEGORYLIST_H_

#include "engine/engine.h"

class PlanetMapCategory;

class PlanetMapCategoryList : public HashTable<int, Reference<PlanetMapCategory*> >, public HashTableIterator<int, Reference<PlanetMapCategory*> > {
	int hash(const int& key) const {
		return Integer::hashCode(key);
	}

	int hash(const String& key) {
		return key.hashCode();
	}

public:
	PlanetMapCategoryList() :
			HashTable<int, Reference<PlanetMapCategory*> >(256),
			HashTableIterator<int, Reference<PlanetMapCategory*> >(this) {

		setNullValue(NULL);
	}

	bool containsKey(const String& key) {
		return HashTable<int, Reference<PlanetMapCategory*> >::containsKey(key.hashCode());
	}

	Reference<PlanetMapCategory*>& get(const String& key) {
		return HashTable<int, Reference<PlanetMapCategory*> >::get(key.hashCode());
	}

	Reference<PlanetMapCategory*>& get(const int& key) {
		return HashTable<int, Reference<PlanetMapCategory*> >::get(Integer::hashCode(key));
	}

	Reference<PlanetMapCategory*>& put(const String& key, const Reference<PlanetMapCategory*>& value) {
		return HashTable<int, Reference<PlanetMapCategory*> >::put(key.hashCode(), value);
	}
};


#endif /* PLANETMAPCATEGORYLIST_H_ */
