#ifndef _H_BADGELIST_
#define _H_BADGELIST_

#include "server/zone/objects/player/badges/Badge.h"

class BadgeList : public Singleton<BadgeList>, public Logger, public Object {
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
         * returns nullptr if the name wasn't found
	 */
	inline const Badge* get(const String& name) const {
		return names.get(name);
	}

	/*
         * Get a badge by index
	 * return nullptre if the name wasn't found
	 */
	inline const Badge* get(unsigned int idx) const {
		return badges.get(idx);
	}

	/*
	 * Returns the (idx, Badge*) vector map
	 */
	inline const VectorMap<unsigned int, const Badge*>* getMap() const {
		return &badges;
	}

};
#endif /* _H_BADGELIST_ */
