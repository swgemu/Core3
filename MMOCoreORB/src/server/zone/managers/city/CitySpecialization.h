/*
 * CitySpecialization.h
 *
 *  Created on: Jul 20, 2012
 *      Author: swgemu
 */

#ifndef CITYSPECIALIZATION_H_
#define CITYSPECIALIZATION_H_

class CitySpecialization : public Object {
	String name;
	int cost;
	VectorMap<String, int> skillMods;

public:
	CitySpecialization() {
		cost = 0;
		skillMods.setNoDuplicateInsertPlan();
		skillMods.setNullValue(0);
	}

	CitySpecialization(const String& name, int cost) {
		this->name = name;
		this->cost = cost;
	}

	CitySpecialization(const CitySpecialization& spec) : Object() {
		name = spec.name;
		cost = spec.cost;
		skillMods = spec.skillMods;
	}

	CitySpecialization& operator=(const CitySpecialization& spec) {
		if (this == &spec)
			return *this;

		name = spec.name;
		cost = spec.cost;
		skillMods = spec.skillMods;

		return *this;
	}

	void readObject(LuaObject* luaObject) {
		name = luaObject->getStringField("name");
		cost = luaObject->getIntField("cost");

		LuaObject smods = luaObject->getObjectField("skillMods");

		for (int i = 1; i <= smods.getTableSize(); ++i) {
			LuaObject mod = smods.getObjectAt(i);

			if (mod.isValidTable()) {
				String k = mod.getStringAt(1);
				int v = mod.getIntAt(2);

				skillMods.put(k, v);
			}

			mod.pop();
		}

		smods.pop();
	}

	inline const String& getName() const {
		return name;
	}

	inline int getCost() const {
		return cost;
	}

	inline const VectorMap<String, int>* getSkillMods() const {
		return &skillMods;
	}
};

#endif /* CITYSPECIALIZATION_H_ */
