/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SKILLMODENTRY_H_
#define SKILLMODENTRY_H_

#include "engine/engine.h"
#include "engine/util/json_utils.h"

class SkillModEntry : public virtual Object {
private:
	int skillMod;
	int skillBonus;

public:
	SkillModEntry() : Object() {
		skillMod = 0;
		skillBonus = 0;

	}

	SkillModEntry(const SkillModEntry& mod) : Object() {

		skillMod = mod.skillMod;
		skillBonus = mod.skillBonus;
	}

	SkillModEntry& operator=(const SkillModEntry& mod) {
		if (this == &mod)
			return *this;

		skillMod = mod.skillMod;
		skillBonus = mod.skillBonus;

		return *this;
	}

	bool operator==(SkillModEntry mod) {
		return
			skillMod == mod.skillMod &&
			skillBonus == mod.skillBonus;
	}

	void setSkillMod(int mod) {
		skillMod = mod;
	}

	int getSkillMod() const {
		return skillMod;
	}

	void setSkillBonus(int bonus) {
		skillBonus = bonus;
	}

	int getSkillBonus() const {
		return skillBonus;
	}

	int getTotalSkill() const {
		return getSkillMod() + getSkillBonus();
	}

	bool toBinaryStream(ObjectOutputStream* stream) {
		return TypeInfo<int >::toBinaryStream(&skillMod, stream) &&
				TypeInfo<int >::toBinaryStream(&skillBonus, stream);
	}

	friend void to_json(nlohmann::json& j, const SkillModEntry& e) {
		j["skillMod"] = e.skillMod;
		j["skillBonus"] = e.skillBonus;
	}

	bool parseFromBinaryStream(ObjectInputStream* stream) {

		TypeInfo<int >::parseFromBinaryStream(&skillMod, stream);
		TypeInfo<int >::parseFromBinaryStream(&skillBonus, stream);

		return true;
	}
};

#endif /*SKILLMODENTRY_H_*/
