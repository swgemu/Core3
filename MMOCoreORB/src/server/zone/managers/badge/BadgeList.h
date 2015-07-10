#ifndef _H_BADGELIST_
#define _H_BADGELIST_

#include "engine/engine.h"
#include "server/zone/objects/player/badges/Badge.h"

class BadgeList : public Object {
	// idx to Badge
	VectorMap<unsigned int, const Badge*> badges;
	
	// Name to badge
	HashTable<String, const Badge*> names;
#ifdef GROUP_BADGES
	// group by category
	VectorMap<unsigned int, Vector<const Badge*>* > categories;

	// Type to Badge
	HashTable<String, Vector<const Badge*>* > types;
#endif
public:
	BadgeList();
	~BadgeList();

	/*
	 * Adds a badge, takes over ownership
	 */
	void add(Badge* badge);

	/*
	 * Get a badge by name
         * returns NULL if the name wasn't found
	 */
	inline const Badge* get(const String& name) {
		return names.get(name);
	}

	/*
         * Get a badge by index
	 * return NULLe if the name wasn't found
	 */
	inline const Badge* get(unsigned int idx) {
		return badges.get(idx);
	}

	/*
	 * Returns the (idx, Badge*) vector map
	 */
	inline VectorMap<unsigned int, const Badge*>* getMap() {
		return &badges;
	}

#ifdef GROUP_BADGES
	/*
 	 * Get a list of badges by category
	 * returns NULL if the category wasn't found
	 */
	inline const Vector<const Badge*>* getCategory(int cat) {
		return categories.get(unsigned int(cat));
	}
	
	/*
	 * Get a list of badges by type
	 * returns NULL if the type wasn't found
 	 */
	inline const Vector<const Badge*>* getType(const String& type) {
		return types.get(type);
	}
#endif	
};
#endif /* _H_BADGELIST_ */
