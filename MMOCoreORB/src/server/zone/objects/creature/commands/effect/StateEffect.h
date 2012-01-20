/*
 * StateEffect.h
 *
 *  Created on: Jan 16, 2012
 *      Author: da
 */

#ifndef STATEEFFECT_H_
#define STATEEFFECT_H_

#include "server/zone/objects/creature/CreatureState.h"

#include "engine/engine.h"

class StateEffect : public Object {
protected:
	uint8 effectType;
	Vector<String> defenderExclusionTimers;
	Vector<String> defenderStateDefenseModifiers;
	Vector<String> defenderJediStateDefenseModifiers;
	uint32 stateChance;
	uint32 stateStrength;
	uint32 stateLength;

public:
	StateEffect() : Object() {
		effectType = 0;
		stateChance = 0;
		stateStrength = 0;
		stateLength = 0;
	}

	StateEffect(LuaObject state) : Object() {
		loadState(state);
	}

	StateEffect(const StateEffect& effect) : Object() {
		effectType = effect.effectType;
		defenderExclusionTimers =  effect.defenderExclusionTimers;
		defenderStateDefenseModifiers = effect.defenderStateDefenseModifiers;
		defenderJediStateDefenseModifiers = effect.defenderJediStateDefenseModifiers;
		stateChance = effect.stateChance;
		stateStrength = effect.stateStrength;
		stateLength = effect.stateLength;
	}

	StateEffect& operator= (const StateEffect& effect) {
		if (this == &effect)
			return *this;

		effectType = effect.effectType;
		defenderExclusionTimers =  effect.defenderExclusionTimers;
		defenderStateDefenseModifiers = effect.defenderStateDefenseModifiers;
		defenderJediStateDefenseModifiers = effect.defenderJediStateDefenseModifiers;
		stateChance = effect.stateChance;
		stateStrength = effect.stateStrength;
		stateLength = effect.stateLength;

		return *this;
	}

	inline int compareTo(const StateEffect& effect) const {
		return 0;
	}

	virtual ~StateEffect() {}

	void loadState(LuaObject state) {
		effectType = state.getByteField("effectType");
		stateChance = state.getIntField("stateChance");
		stateStrength = state.getIntField("stateStrength");
		stateLength = state.getIntField("stateLength");

		LuaObject defTimers = state.getObjectField("defenderExclusionTimers");

		for (int i = 1; i <= defTimers.getTableSize(); ++i) {
			defenderExclusionTimers.add(defTimers.getStringAt(i));
		}

		defTimers.pop();

		LuaObject defMods = state.getObjectField("defenderStateDefenseModifiers");

		for (int i = 1; i <= defMods.getTableSize(); ++i) {
			defenderStateDefenseModifiers.add(defMods.getStringAt(i));
		}

		defMods.pop();

		LuaObject jediMods = state.getObjectField("defenderJediStateDefenseModifiers");

		for (int i = 1; i <= jediMods.getTableSize(); ++i) {
			defenderJediStateDefenseModifiers.add(jediMods.getStringAt(i));
		}

		jediMods.pop();
	}

    Vector<String> getDefenderExclusionTimers() const {
        return defenderExclusionTimers;
    }

    Vector<String> getDefenderJediStateDefenseModifiers() const {
        return defenderJediStateDefenseModifiers;
    }

    Vector<String> getDefenderStateDefenseModifiers() const {
        return defenderStateDefenseModifiers;
    }

    uint8 getEffectType() const {
        return effectType;
    }

    uint32 getStateChance() const {
        return stateChance;
    }

    uint32 getStateLength() const {
        return stateLength;
    }

    uint32 getStateStrength() const {
        return stateStrength;
    }

    void setDefenderExclusionTimers(Vector<String> defenderExclusionTimers) {
        this->defenderExclusionTimers = defenderExclusionTimers;
    }

    void setDefenderJediStateDefenseModifiers(Vector<String> defenderJediStateDefenseModifiers) {
        this->defenderJediStateDefenseModifiers = defenderJediStateDefenseModifiers;
    }

    void setDefenderStateDefenseModifiers(Vector<String> defenderStateDefenseModifiers) {
        this->defenderStateDefenseModifiers = defenderStateDefenseModifiers;
    }

    void setEffectType(uint8 effectType) {
        this->effectType = effectType;
    }

    void setStateChance(uint32 stateChance) {
        this->stateChance = stateChance;
    }

    void setStateLength(uint32 stateLength) {
        this->stateLength = stateLength;
    }

    void setStateStrength(uint32 stateStrength) {
        this->stateStrength = stateStrength;
    }
};


#endif /* STATEEFFECT_H_ */
