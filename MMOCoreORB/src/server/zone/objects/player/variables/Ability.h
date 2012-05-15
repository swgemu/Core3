/*
 * Ability.h
 *
 *  Created on: Aug 23, 2011
 *      Author: crush
 */

#ifndef ABILITY_H_
#define ABILITY_H_

#include "engine/engine.h"

class Ability : public Object {
	String abilityName;

public:
	Ability() : Object() {
	}

	Ability(const String& name) : Object() {
		abilityName = name;
	}

	Ability(const Ability& a) : Object() {
		abilityName = a.abilityName;
	}

	Ability& operator=(const Ability& a) {
		if (this == &a)
			return *this;

		abilityName = a.abilityName;

		return *this;
	}

	int compareTo(const Ability& a) {
		return abilityName.compareTo(a.abilityName);
	}

	String& getAbilityName() {
		return abilityName;
	}

	void setAbilityName(const String& name) {
		abilityName = name;
	}

	bool toBinaryStream(ObjectOutputStream* stream) {
		abilityName.toBinaryStream(stream);

		return true;
	}
};

#endif /* ABILITY_H_ */
