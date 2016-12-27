#ifndef _H_BADGELIST_
#define _H_BADGELIST_

#include "server/zone/objects/player/badges/Badge.h"

class BadgeList : public Singleton<BadgeList>, Logger, public Object {
	// idx to Badge
	VectorMap<unsigned int, const Badge*> badges;
	
	// Name to badge
	HashTable<String, const Badge*> names;

	void loadData();
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

};
#endif /* _H_BADGELIST_ */
