/*
 * SkillModMap.cpp
 *
 *  Created on: Jan 31, 2012
 *      Author: xyborn
 */

#include "SkillModMap.h"

SkillModMap::SkillModMap() {
	skillMods.setNoDuplicateInsertPlan();
	skillMods.setNullValue(0);

	addSerializableVariables();
}

SkillModMap::SkillModMap(const SkillModMap& smm) : Object(), Serializable(smm) {
	skillMods = smm.skillMods;

	addSerializableVariables();
}

SkillModMap& SkillModMap::operator=(const SkillModMap& smm) {
	if (this == &smm)
		return *this;

	skillMods = smm.skillMods;

	return *this;
}

void SkillModMap::add(const SkillModMap* smm) {
	for (int i = 0; i < smm->size(); ++i) {
		const auto& entry = smm->skillMods.elementAt(i);

		skillMods.put(entry.getKey(), skillMods.get(entry.getKey()) + entry.getValue());
	}
}

void SkillModMap::add(const VectorMap<String, int64>* map) {
	for (int i = 0; i < map->size(); ++i) {
		const auto& entry = map->elementAt(i);

		skillMods.put(entry.getKey(), skillMods.get(entry.getKey()) + entry.getValue());
	}
}

void SkillModMap::subtract(const SkillModMap* smm) {
	for (int i = 0; i < smm->skillMods.size(); ++i) {
		const auto& entry = smm->skillMods.elementAt(i);

		int val = skillMods.get(entry.getKey()) - entry.getValue();

		if (val <= 0) {
			skillMods.drop(entry.getKey());
		} else {
			skillMods.put(entry.getKey(), val);
		}
	}
}

void SkillModMap::subtract(const VectorMap<String, int64>* map) {
	for (int i = 0; i < map->size(); ++i) {
		const auto& entry = map->elementAt(i);

		int val = skillMods.get(entry.getKey()) - entry.getValue();

		if (val <= 0) {
			skillMods.drop(entry.getKey());
		} else {
			skillMods.put(entry.getKey(), val);
		}
	}
}
