/*
Copyright (C) 2007 <SWGEmu>
 
This File is part of Core3.
 
This program is free software; you can redistribute 
it and/or modify it under the terms of the GNU Lesser 
General Public License as published by the Free Software
Foundation; either version 2 of the License, 
or (at your option) any later version.
 
This program is distributed in the hope that it will be useful, 
but WITHOUT ANY WARRANTY; without even the implied warranty of 
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
See the GNU Lesser General Public License for
more details.
 
You should have received a copy of the GNU Lesser General 
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
 
Linking Engine3 statically or dynamically with other modules 
is making a combined work based on Engine3. 
Thus, the terms and conditions of the GNU Lesser General Public License 
cover the whole combination.
 
In addition, as a special exception, the copyright holders of Engine3 
give you permission to combine Engine3 program with free software 
programs or libraries that are released under the GNU LGPL and with 
code included in the standard release of Core3 under the GNU LGPL 
license (or modified versions of such code, with unchanged license). 
You may copy and distribute such a system following the terms of the 
GNU LGPL for Engine3 and the licenses of the other code concerned, 
provided that you include the source code of that other code when 
and as the GNU LGPL requires distribution of source code.
 
Note that people who make modified versions of Engine3 are not obligated 
to grant this special exception for their modified versions; 
it is their choice whether to do so. The GNU Lesser General Public License 
gives permission to release a modified version without this exception; 
this exception also makes it possible to release a modified version 
which carries forward this exception.
*/

#ifndef WEAPONIMPLEMENTATION_H_
#define WEAPONIMPLEMENTATION_H_

#include "../../creature/CreatureObject.h"
#include "../../creature/CreatureObjectImplementation.h"

#include "../TangibleObject.h"

#include "../Inventory.h"
#include "../InventoryImplementation.h"

#include "Weapon.h"

class CombatManager;

class WeaponImplementation : public WeaponServant {
protected:
	int type;
	
	int category;

	int damageType;
	float minDamage;
	float maxDamage;
	
	float attackSpeed;
	
	int healthAttackCost;
	int actionAttackCost;
	int mindAttackCost;
	
	int pointBlankAccuracy;
	int pointBlankRange;
	
	int idealRange;
	int idealAccuracy;
	
	int maxRange;
	int maxRangeAccuracy;
	
	int woundsRatio;
	
	int armorPiercing;
	
	int dot0Type;
	int dot0Attribute;
	int dot0Strength;
	int dot0Duration;
	int dot0Potency;
	int dot0Uses;
	
	int dot1Type;
	int dot1Attribute;
	int dot1Strength;
	int dot1Duration;
	int dot1Potency;
	int dot1Uses;

	int dot2Type;
	int dot2Attribute;
	int dot2Strength;
	int dot2Duration;
	int dot2Potency;
	int dot2Uses;
	
	bool sliced;
	
public:

	static const int MELEE = 0x10;
	static const int RANGED = 0x20;
	static const int JEDI = 0x30;

	static const int UNARMED = 0;
	static const int ONEHANDED = 1;
	static const int TWOHANDED = 2;
	static const int POLEARM = 3;
	static const int PISTOL = 4;
	static const int CARBINE = 5;
	static const int RIFLE = 6;
	static const int ONEHANDSABER = 7;
	static const int TWOHANDSABER = 8;
	static const int POLEARMSABER = 9;
	
	static const int NONE = 0;
	static const int LIGHT = 1;
	static const int MEDIUM = 2;
	static const int HEAVY = 3;
	
	static const int BLEED = 1;
	static const int DISEASE = 2;
	static const int FIRE = 3;
	static const int POISON = 4;
	
	static const int HEALTH = 1;
	static const int STRENGTH = 2;
	static const int CONSTITUTION = 3;
	static const int ACTION = 4;
	static const int QUICKNESS = 5;
	static const int STAMINA = 6;
	static const int MIND = 7;
	static const int FOCUS = 8;
	static const int WILLPOWER = 9;
	
	static const int KINETIC = 1;
	static const int ENERGY = 2;
	static const int ELECTRICITY = 3;
	static const int STUN = 4;
	static const int BLAST = 5;
	static const int HEAT = 6;
	static const int COLD = 7;
	static const int ACID = 8;
	static const int LIGHTSABER = 9;

public:
	WeaponImplementation(uint64 objid, uint32 tempCRC, const unicode& n, const string& tempn, bool eqp, int tp, int cat);
	WeaponImplementation(CreatureObject* creature, const string& temp, const unicode& n, const string& tempn, bool eqp, int tp, int cat); 

	void initialize();
	
	void sendTo(Player* player, bool doClose = true);
	
	void generateAttributes(SceneObject* obj);
	void generateDotAttributes(class AttributeListMessage* alm);
	
	void setWeaponStats(int modifier);
	
	void decay(int decayRate);

	// slicing methods
	void sliceWeapon(Player* player);

	int sliceWeaponDamage();
	int sliceWeaponSpeed();

	inline bool isSliced() {
		return sliced;
	}	

	// dots
	inline bool decreaseDot0Uses() {
		if (dot0Uses != -1) { 
			--dot0Uses;
			return true;
		} else
			return false;
	}

	inline bool decreaseDot1Uses() {
		if (dot1Uses != -1) { 
			--dot1Uses;
			return true;
		} else
			return false;
	}

	inline bool decreaseDot2Uses() {
		if (dot2Uses != -1) { 
			--dot2Uses;
			return true;
		} else
			return false;
	}

	// setters
	inline void setDamageType(int type) {
		damageType = type;
	}
	
	inline void setMinDamage(float minDmg) {
		minDamage = minDmg;
	}

	inline void setMaxDamage(float maxDmg) {
		maxDamage = maxDmg;
	}

	inline void setAttackSpeed(float attackSpd) {
		attackSpeed = attackSpd;
	}

	inline void setHealthAttackCost(int healthCost) {
		healthAttackCost = healthCost;
	}

	inline void setActionAttackCost(int actionCost) {
		actionAttackCost = actionCost;
	}

	inline void setMindAttackCost(int mindCost) {
		mindAttackCost = mindCost;
	}
		
	inline void setCategory(int cat) {
		category = cat;
	}
	
	inline void setPointBlankRange(int pointBlankRnge) {
		pointBlankRange = pointBlankRnge;
	}
	
	inline void setPointBlankAccuracy(int pointBlankAcc) {
		pointBlankAccuracy = pointBlankAcc;
	}
	
	inline void setMaxRange(int maxRnge) {
		maxRange = maxRnge;
	}
	
	inline void setMaxRangeAccuracy(int maxRangeAcc) {
		maxRangeAccuracy = maxRangeAcc;
	}
	
	inline void setIdealRange(int idealRnge) {
		idealRange = idealRnge;
	}
	
	inline void setIdealAccuracy(int idealAcc) {
		idealAccuracy = idealAcc;
	}
	
	inline void setWoundsRatio(int woundsRat) {
		woundsRatio = woundsRat;
	}
	
	inline void setArmorPiercing(int armorPierce) {
		armorPiercing = armorPierce;
	}

	inline void setDot0Type(int type) {
		dot0Type = type;
	}
	
	inline void setDot0Attribute(int attribute) {
		dot0Attribute = attribute;
	}
	
	inline void setDot0Strength(int strength) {
		dot0Strength = strength;
	}
	
	inline void setDot0Duration(int duration) {
		dot0Duration = duration;
	}
	
	inline void setDot0Potency(int potency) {
		dot0Potency = potency;
	}
	
	inline void setDot0Uses(int uses) {
		dot0Uses = uses;
	}

	inline void setDot1Type(int type) {
		dot1Type = type;
	}
	
	inline void setDot1Attribute(int attribute) {
		dot1Attribute = attribute;
	}
	
	inline void setDot1Strength(int strength) {
		dot1Strength = strength;
	}
	
	inline void setDot1Duration(int duration) {
		dot1Duration = duration;
	}
	
	inline void setDot1Potency(int potency) {
		dot1Potency = potency;
	}
	
	inline void setDot1Uses(int uses) {
		dot1Uses = uses;
	}
	
	inline void setDot2Type(int type) {
		dot2Type = type;
	}
	
	inline void setDot2Attribute(int attribute) {
		dot2Attribute = attribute;
	}
	
	inline void setDot2Strength(int strength) {
		dot2Strength = strength;
	}
	
	inline void setDot2Duration(int duration) {
		dot2Duration = duration;
	}
	
	inline void setDot2Potency(int potency) {
		dot2Potency = potency;
	}
	
	inline void setDot2Uses(int uses) {
		dot2Uses = uses;
	}

	inline void setSliced(int hacked) {
		sliced = hacked;
	}
	
	// getters
	inline int getDamageType() {
		return damageType;
	}
	
	inline float getMinDamage() {
		return minDamage;
	}

	inline float getMaxDamage() {
		return maxDamage;
	}

	inline float getAttackSpeed() {
		return attackSpeed;
	}

	inline int getHealthAttackCost() {
		return healthAttackCost;
	}

	inline int getActionAttackCost() {
		return actionAttackCost;
	}

	inline int getMindAttackCost() {
		return mindAttackCost;
	}
	
	inline int getType() {
		return type;
	}
	
	inline bool isJedi() {
		return (category == JEDI);
	}
	
	inline bool isMelee() {
		return (category == MELEE);
	}
	
	inline bool isRanged() {
		return (category == RANGED) ;
	}
	
	inline int getCategory() {
		return category;
	}
	
	inline int getPointBlankRange() {
		return pointBlankRange;
	}
	
	inline int getPointBlankAccuracy() {
		return pointBlankAccuracy;
	}
	
	inline int getMaxRange() {
		return maxRange;
	}
	
	inline int getMaxRangeAccuracy() {
		return maxRangeAccuracy;
	}
	
	inline int getIdealRange() {
		return idealRange;
	}
	
	inline int getIdealAccuracy() {
		return idealAccuracy;
	}
	
	inline int getWoundsRatio() {
		return woundsRatio;
	}
	
	inline int getArmorPiercing() {
		return armorPiercing;
	}
	
	inline int getDot0Type() {
		return dot0Type;
	}

	inline int getDot0Attribute() {
		return dot0Attribute;
	}

	inline int getDot0Strength() {
		return dot0Strength;
	}

	inline int getDot0Duration() {
		return dot0Duration;
	}

	inline int getDot0Potency() {
		return dot0Potency;
	}

	inline int getDot0Uses() {
		return dot0Uses;
	}

	inline int getDot1Type() {
		return dot1Type;
	}

	inline int getDot1Attribute() {
		return dot1Attribute;
	}

	inline int getDot1Strength() {
		return dot1Strength;
	}

	inline int getDot1Duration() {
		return dot1Duration;
	}

	inline int getDot1Potency() {
		return dot1Potency;
	}

	inline int getDot1Uses() {
		return dot1Uses;
	}
	
	inline int getDot2Type() {
		return dot2Type;
	}

	inline int getDot2Attribute() {
		return dot2Attribute;
	}

	inline int getDot2Strength() {
		return dot2Strength;
	}

	inline int getDot2Duration() {
		return dot2Duration;
	}

	inline int getDot2Potency() {
		return dot2Potency;
	}

	inline int getDot2Uses() {
		return dot2Uses;
	}

	friend class CombatManager;
	
};

#endif /*WEAPONIMPLEMENTATION_H_*/
