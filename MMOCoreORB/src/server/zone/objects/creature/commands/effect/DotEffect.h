/*
 * DotEffect.h
 *
 *  Created on: Jan 19, 2012
 *      Author: da
 */

#ifndef DOTEFFECT_H_
#define DOTEFFECT_H_

#include "engine/engine.h"

class DotEffect : public Object {
protected:
	uint32 dotType;
	Vector<String> defenderStateDefenseModifers;
	uint8 dotPool;
	bool dotDamageofHit;
	uint32 dotDuration;
	uint32 dotStrength;
	uint32 dotPotency;
    uint32 dotChance;
public:
    DotEffect()
    :Object()
    {
        dotType = 0;
        dotPool = 0;
        dotDamageofHit = 0;
        dotDuration = 0;
        dotStrength = 0;
        dotPotency = 0;
        dotChance = 0;
    }

    DotEffect(LuaObject dot)
    :Object()
    {
        loadDot(dot);
    }

    DotEffect(const DotEffect & effect)
    :Object()
    {
        dotType = effect.dotType;
        defenderStateDefenseModifers = effect.defenderStateDefenseModifers;
        dotPool = effect.dotPool;
        dotDamageofHit = effect.dotDamageofHit;
        dotDuration = effect.dotDuration;
        dotStrength = effect.dotStrength;
        dotPotency = effect.dotPotency;
        dotChance = effect.dotChance;
    }

    virtual ~DotEffect()
    {
    }

    DotEffect & operator =(const DotEffect & effect)
    {
        if(this == &effect)
            return *this;

        dotType = effect.dotType;
        defenderStateDefenseModifers = effect.defenderStateDefenseModifers;
        dotPool = effect.dotPool;
        dotDamageofHit = effect.dotDamageofHit;
        dotDuration = effect.dotDuration;
        dotStrength = effect.dotStrength;
        dotPotency = effect.dotPotency;
        dotChance = effect.dotChance;
        return *this;
    }
    inline int compareTo(const DotEffect & effect)
    {
        return 0;
    }

    void loadDot(LuaObject dot)
    {
        dotType = dot.getIntField("dotType");
        dotPool = dot.getByteField("dotPool");
        LuaObject dohBool = dot.getObjectField("dotDamageofHit");
        lua_State *L = dohBool.getLuaState();
        dotDamageofHit = (bool)((lua_toboolean(L, -1)));
        dohBool.pop();
        dotDuration = dot.getIntField("dotDuration");
        dotStrength = dot.getIntField("dotStrength");
        dotPotency = dot.getIntField("dotPotency");
        dotChance = dot.getIntField("dotChance");
        LuaObject defMods = dot.getObjectField("defenderStateDefenseModifiers");
        for(int i = 1;i <= defMods.getTableSize();++i){
            defenderStateDefenseModifers.add(defMods.getStringAt(i));
        }
        defMods.pop();
    }

    Vector<String> getDefenderStateDefenseModifers() const
    {
        return defenderStateDefenseModifers;
    }

    uint32 getDotDuration() const
    {
        return dotDuration;
    }

    uint8 getDotPool() const
    {
        return dotPool;
    }

    uint32 getDotPotency() const
    {
        return dotPotency;
    }

    uint32 getDotStrength() const
    {
        return dotStrength;
    }

    uint32 getDotType() const
    {
        return dotType;
    }

    bool isDotDamageofHit() const
    {
        return dotDamageofHit;
    }

    void setDefenderStateDefenseModifers(Vector<String> defenderStateDefenseModifers)
    {
        this->defenderStateDefenseModifers = defenderStateDefenseModifers;
    }

    void setDotDamageofHit(bool dotDamageofHit)
    {
        this->dotDamageofHit = dotDamageofHit;
    }

    void setDotDuration(uint32 dotDuration)
    {
        this->dotDuration = dotDuration;
    }

    void setDotPool(uint8 dotPool)
    {
        this->dotPool = dotPool;
    }

    void setDotPotency(uint32 dotPotency)
    {
        this->dotPotency = dotPotency;
    }

    void setDotStrength(uint32 dotStrength)
    {
        this->dotStrength = dotStrength;
    }

    void setDotType(uint32 dotType)
    {
        this->dotType = dotType;
    }

    uint32 getDotChance() const {
        return dotChance;
    }

    void setDotChance(uint32 dotChance) {
        this->dotChance = dotChance;
    }

};


#endif /* DOTEFFECT_H_ */
