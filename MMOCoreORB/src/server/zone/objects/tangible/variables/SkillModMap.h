/*
 * SkillModMap.h
 *
 *  Created on: Jan 31, 2012
 *      Author: xyborn
 */

#ifndef SKILLMODMAP_H_
#define SKILLMODMAP_H_

#include "engine/engine.h"

class SkillModMap : public Serializable {
	VectorMap<String, int64> skillMods;

public:
	SkillModMap();
	SkillModMap(const SkillModMap& smm);

	SkillModMap& operator=(const SkillModMap& smm);

	void add(SkillModMap* map);
	void add(VectorMap<String, int64>* map);

	void subtract(SkillModMap* map);
	void subtract(VectorMap<String, int64>* map);

	void addSerializableVariables() {
		addSerializableVariable("skillMods", &skillMods);
	}

	/**
	 * Returns the number of mods in the map.
	 */
	inline int size() {
		return skillMods.size();
	}

	/**
	 * Returns true if the map contains a value for the mod.
	 */
	inline bool contains(const String& mod) {
		return skillMods.contains(mod);
	}

	/**
	 * If the key exists, returns the value, otherwise returns 0.
	 */
	inline int64 get(const String& mod) {
		return skillMods.get(mod);
	}

	inline int64 get(int idx) {
		return skillMods.get(idx);
	}

	/**
	 * If the key does not exist, it will put this value. If the key does exist, it will be ignored.
	 */
	inline void put(const String& mod, int64 value) {
		skillMods.put(mod, value);
	}

	/**
	 * If the key exists, it will overwrite it's value with this value.
	 */
	void overwrite(const String& mod, int64 value) {
		if (skillMods.contains(mod)) {
			if (value <= 0) {
				skillMods.drop(mod);
			} else {
				skillMods.get(mod) = value;
			}
		} else {
			skillMods.put(mod, value);
		}
	}

	/**
	 * Adds the value to an existing mod, or puts into the map if not existing.
	 */
	void add(const String& mod, int64 value) {
		if (skillMods.contains(mod)) {
			skillMods.get(mod) += value;
		} else {
			skillMods.put(mod, value);
		}
	}

	/**
	 * Subtracts the value of an existing mod, and drops the mod if it is equal to 0.
	 */
	void subtract(const String& mod, int64 value) {
		int64 final = skillMods.get(mod) - value;

		if (final <= 0) {
			skillMods.drop(mod);
		} else {
			skillMods.put(mod, final);
		}
	}
};


#endif /* SKILLMODMAP_H_ */
