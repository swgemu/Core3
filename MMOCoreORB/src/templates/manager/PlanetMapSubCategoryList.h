
#ifndef PLANETMAPSUBCATEGORYLIST_H_
#define PLANETMAPSUBCATEGORYLIST_H_

#include "engine/engine.h"

#include "system/util/HashTable.h"

class PlanetMapSubCategory;

class PlanetMapSubCategoryList : public HashTable<int, Reference<PlanetMapSubCategory*>> {
	int hash(const int& key) const override {
		return key; // this is the string crc so no need to rehash
	}

	int hash(const String& key) const {
		return key.hashCode();
	}

public:
	PlanetMapSubCategoryList() : HashTable<int, Reference<PlanetMapSubCategory*>>(256) {
		setNullValue(nullptr);
	}

	bool containsKey(const String& key) const {
		return HashTable<int, Reference<PlanetMapSubCategory*>>::containsKey(key.hashCode());
	}

	const Reference<PlanetMapSubCategory*>& get(const String& key) const {
		return HashTable<int, Reference<PlanetMapSubCategory*>>::get(key.hashCode());
	}

	const Reference<PlanetMapSubCategory*>& get(const int& key) const {
		return HashTable<int, Reference<PlanetMapSubCategory*>>::get(key);
	}

	Reference<PlanetMapSubCategory*> put(const String& key, const Reference<PlanetMapSubCategory*>& value) {
		return HashTable<int, Reference<PlanetMapSubCategory*>>::put(key.hashCode(), value);
	}
};

#endif /* PLANETMAPSUBCATEGORYLIST_H_ */
