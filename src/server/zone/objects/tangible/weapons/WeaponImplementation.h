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
//#include "../ItemAttributes.h"

#include "../Inventory.h"
#include "../InventoryImplementation.h"

#include "Weapon.h"

#include "../powerup/Powerup.h"
#include "../powerup/PowerupImplementation.h"

#include "WeaponSkillModMap.h"
#include "WeaponSkillMods.h"

class CombatManager;
class Powerup;

class WeaponImplementation : public WeaponSkillModMap, public WeaponServant {
protected:
	int type;

	int category;

	String cert;
	bool certified;

	int usesRemaining;

	int damageType;
	float minDamage;
	float maxDamage;

	float attackSpeed;

	int healthAttackCost;
	int actionAttackCost;
	int mindAttackCost;
	int forceCost;

	int pointBlankAccuracy;
	int pointBlankRange;

	int idealRange;
	int idealAccuracy;

	int maxRange;
	int maxRangeAccuracy;

	float woundsRatio;

	int armorPiercing;

	int powerupUses;

	float bonusMinDamage;
	float bonusMaxDamage;

	float bonusAttackSpeed;

	int bonusHealthAttackCost;
	int bonusActionAttackCost;
	int bonusMindAttackCost;

	int bonusPointBlankAccuracy;
	int bonusPointBlankRange;

	int bonusIdealRange;
	int bonusIdealAccuracy;

	int bonusMaxRange;
	int bonusMaxRangeAccuracy;

	float bonusWoundsRatio;

	String xpType;
	float area;

	WeaponSkillMods weaponSkillMods;

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
	static const int RIFLEBEAM = 10;
	static const int RIFLEFLAMETHROWER = 11;
	static const int RIFLELIGHTNING = 12;
	static const int RIFLEACIDBEAM = 13;
	static const int HEAVYACIDBEAM = 14;
	static const int HEAVYLIGHTNINGBEAM = 15;
	static const int HEAVYPARTICLEBEAM = 17;
	static const int HEAVYROCKETLAUNCHER = 18;
	static const int HEAVYLAUNCHER = 19;
	static const int GRENADE = 20;
	static const int TRAP = 21;
	static const int SPECIALHEAVYWEAPON = 22;

	static const int NONE = 0;
	static const int LIGHT = 1;
	static const int MEDIUM = 2;
	static const int HEAVY = 3;

	static const int KINETIC = 1;
	static const int ENERGY = 2;
	static const int ELECTRICITY = 3;
	static const int STUN = 4;
	static const int BLAST = 5;
	static const int HEAT = 6;
	static const int COLD = 7;
	static const int ACID = 8;
	static const int LIGHTSABER = 9;
	static const int FORCE = 10;

public:
	WeaponImplementation(uint64 objid, uint32 tempCRC, const UnicodeString& n, const String& tempn, bool eqp, int tp, int cat);
	WeaponImplementation(CreatureObject* creature, const String& temp, const UnicodeString& n, const String& tempn, bool eqp, int tp, int cat);

	void init();

	void parseItemAttributes();

	void updateCraftingValues(DraftSchematic* draftSchematic);

	void sendTo(Player* player, bool doClose = true);

	void sendRadialResponseTo(Player* player, ObjectMenuResponse* omr);

	void generateAttributes(SceneObject* obj);

	void generateDotAttributes(class AttributeListMessage* alm);

	void generatePowerup(class AttributeListMessage* alm);

	void setXpType();

	void setWeaponStats(int modifier);

	void decay(float decayRate);

	void removePowerup(Player* player, bool notify);

	void powerupMinDamage(float powerupValue);
	void powerupMaxDamage(float powerupValue);
	void powerupHealthAttackCost(float powerupValue);
	void powerupActionAttackCost(float powerupValue);
	void powerupMindAttackCost(float powerupValue);
	void powerupWoundsRatio(float powerupValue);
	void powerupAttackSpeed(float powerupValue);
	void powerupPointBlankAccuracy(float powerupValue);
	void powerupIdealRange(float powerupValue);
	void powerupIdealAccuracy(float powerupValue);
	void powerupMaxRangeAccuracy(float powerupValue);

	void saveSkillModMap();
	void saveDotMap();
	void setInnateMods(Player* player);
	void unsetInnateMods(Player* player);

	void createTestDot(int type);

	void onEquip(Player* player);
	void onUnequip(Player* player);

	void addAttributes(AttributeListMessage* alm);

	inline bool decreasePowerupUses() {
		if (powerupUses > 0) {
			String name = "powerupUses";
			itemAttributes->setIntAttribute(name, --powerupUses);
			return true;
		} else
			return false;
	}

	inline bool decreaseUsesRemaining() {
		if (usesRemaining > 0) {
			String name = "usesRemaining";
			itemAttributes->setIntAttribute(name, --usesRemaining);
			return true;
		} else
			return false;
	}

	// setters
	inline void setDamageType(int type) {
		damageType = type;
		String name = "damageType";
		itemAttributes->setIntAttribute(name, type);
	}

	inline void setMinDamage(float minDmg) {
		minDamage = minDmg;
		String name = "minDamage";
		itemAttributes->setFloatAttribute(name, minDmg);
	}

	inline void setMaxDamage(float maxDmg) {
		maxDamage = maxDmg;
		String name = "maxDamage";
		itemAttributes->setFloatAttribute(name, maxDmg);
	}

	inline void setAttackSpeed(float attackSpd) {
		attackSpeed = attackSpd;
		String name = "attackSpeed";
		itemAttributes->setFloatAttribute(name, attackSpd);
	}

	inline void setHealthAttackCost(int healthCost) {
		healthAttackCost = healthCost;
		String name = "healthCost";
		itemAttributes->setIntAttribute(name, healthCost);
	}

	inline void setActionAttackCost(int actionCost) {
		actionAttackCost = actionCost;
		String name = "actionCost";
		itemAttributes->setIntAttribute(name, actionCost);
	}

	inline void setMindAttackCost(int mindCost) {
		mindAttackCost = mindCost;
		String name = "mindCost";
		itemAttributes->setIntAttribute(name, mindCost);
	}

	inline void setForceCost(int fcost) {
		forceCost = fcost;
		String name = "forceCost";
		itemAttributes->setIntAttribute(name, fcost);
	}

	inline void setType(int tp) {
		type = tp;
		String name = "type";
		itemAttributes->setIntAttribute(name, tp);
	}

	inline void setCategory(int cat) {
		category = cat;
		String name = "category";
		itemAttributes->setIntAttribute(name, cat);
	}

	inline void setUsesRemaining(int charges) {
		usesRemaining = charges;
		String name = "usesRemaining";
		itemAttributes->setIntAttribute(name, charges);
	}

	inline void setPointBlankRange(int pointBlankRnge) {
		pointBlankRange = pointBlankRnge;
		String name = "pointBlankRange";
		itemAttributes->setIntAttribute(name, pointBlankRnge);
	}

	inline void setPointBlankAccuracy(int pointBlankAcc) {
		pointBlankAccuracy = pointBlankAcc;
		String name = "pointBlankAccuracy";
		itemAttributes->setIntAttribute(name, pointBlankAcc);
	}

	inline void setMaxRange(int maxRnge) {
		maxRange = maxRnge;
		String name = "maxRange";
		itemAttributes->setIntAttribute(name, maxRnge);
	}

	inline void setMaxRangeAccuracy(int maxRangeAcc) {
		maxRangeAccuracy = maxRangeAcc;
		String name = "maxRangeAccuracy";
		itemAttributes->setIntAttribute(name, maxRangeAcc);
	}

	inline void setIdealRange(int idealRnge) {
		idealRange = idealRnge;
		String name = "idealRange";
		itemAttributes->setIntAttribute(name, idealRnge);
	}

	inline void setIdealAccuracy(int idealAcc) {
		idealAccuracy = idealAcc;
		String name = "idealAccuracy";
		itemAttributes->setIntAttribute(name, idealAcc);
	}

	inline void setWoundsRatio(float woundsRat) {
		woundsRatio = woundsRat;
		String name = "woundsRatio";
		itemAttributes->setFloatAttribute(name, woundsRat);
	}

	inline void setArmorPiercing(int armorPierce) {
		armorPiercing = armorPierce;
		String name = "armorPiercing";
		itemAttributes->setIntAttribute(name, armorPierce);
	}

	inline void setPowerupUses(int uses) {
		powerupUses = uses;
		String name = "powerupUses";
		itemAttributes->setIntAttribute(name, uses);
	}

	inline void setBonusMinDamage(float minDmg) {
		bonusMinDamage = minDmg;
		String name = "bonusMinDamage";
		itemAttributes->setFloatAttribute(name, minDmg);
	}

	inline void setBonusMaxDamage(float maxDmg) {
		bonusMaxDamage = maxDmg;
		String name = "bonusMaxDamage";
		itemAttributes->setFloatAttribute(name, maxDmg);
	}

	inline void setBonusAttackSpeed(float attackSpd) {
		bonusAttackSpeed = attackSpd;
		String name = "bonusAttackSpeed";
		itemAttributes->setFloatAttribute(name, attackSpd);
	}

	inline void setBonusHealthAttackCost(int healthCost) {
		bonusHealthAttackCost = healthCost;
		String name = "bonusHealthCost";
		itemAttributes->setIntAttribute(name, healthCost);
	}

	inline void setBonusActionAttackCost(int actionCost) {
		bonusActionAttackCost = actionCost;
		String name = "bonusActionCost";
		itemAttributes->setIntAttribute(name, actionCost);
	}

	inline void setBonusMindAttackCost(int mindCost) {
		bonusMindAttackCost = mindCost;
		String name = "bonusMindCost";
		itemAttributes->setIntAttribute(name, mindCost);
	}

	inline void setBonusPointBlankRange(int pointBlankRnge) {
		bonusPointBlankRange = pointBlankRnge;
		String name = "bonusPointBlankRange";
		itemAttributes->setIntAttribute(name, pointBlankRnge);
	}

	inline void setBonusPointBlankAccuracy(int pointBlankAcc) {
		bonusPointBlankAccuracy = pointBlankAcc;
		String name = "bonusPointBlankAccuracy";
		itemAttributes->setIntAttribute(name, pointBlankAcc);
	}

	inline void setBonusMaxRange(int maxRnge) {
		bonusMaxRange = maxRnge;
		String name = "bonusMaxRange";
		itemAttributes->setIntAttribute(name, maxRnge);
	}

	inline void setBonusMaxRangeAccuracy(int maxRangeAcc) {
		bonusMaxRangeAccuracy = maxRangeAcc;
		String name = "bonusMaxRangeAccuracy";
		itemAttributes->setIntAttribute(name, maxRangeAcc);
	}

	inline void setBonusIdealRange(int idealRnge) {
		bonusIdealRange = idealRnge;
		String name = "bonusIdealRange";
		itemAttributes->setIntAttribute(name, idealRnge);
	}

	inline void setBonusIdealAccuracy(int idealAcc) {
		bonusIdealAccuracy = idealAcc;
		String name = "bonusIdealAccuracy";
		itemAttributes->setIntAttribute(name, idealAcc);
	}

	inline void setBonusWoundsRatio(float woundsRat) {
		bonusWoundsRatio = woundsRat;
		String name = "bonusWoundsRatio";
		itemAttributes->setFloatAttribute(name, woundsRat);
	}

	inline void setCert(String certification) {
		cert = certification;
		String name = "cert";
		itemAttributes->setStringAttribute(name, certification);
	}

	inline void setCertified(bool crt) {
		certified = crt;
	}

	inline void setArea(float ar) {
		area = ar;
		String name = "area";
		itemAttributes->setFloatAttribute(name, area);
	}

	inline float getArea() {
		return area;
	}

	// getters
	inline int getDamageType() {
		return damageType;
	}

	inline int getUsesRemaining() {
		return usesRemaining;
	}

	inline float getBaseMinDamage() {
		return minDamage;
	}

	inline float getMinDamage() {
		return minDamage + bonusMinDamage;
	}

	inline float getBaseMaxDamage() {
		return maxDamage;
	}

	inline float getMaxDamage() {
		return maxDamage + bonusMaxDamage;
	}

	inline float getBaseAttackSpeed() {
		float spd = attackSpeed;

		if (spd < 1.0f)
			return 1.0f;
		else
			return spd;
	}

	inline float getAttackSpeed() {
		float spd = attackSpeed + bonusAttackSpeed;

		if (spd < 1.0f)
			return 1.0f;
		else
			return spd;
	}

	inline int getHealthAttackCost() {
		return healthAttackCost + bonusHealthAttackCost;
	}

	inline int getActionAttackCost() {
		return actionAttackCost + bonusActionAttackCost;
	}

	inline int getMindAttackCost() {
		return mindAttackCost + bonusMindAttackCost;
	}

	inline int getForceCost(){
		return forceCost;
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
		return (category == RANGED || category == HEAVYWEAPON) ;
	}

	inline bool isHeavyWeapon() {
		return (category == HEAVYWEAPON);
	}

	inline bool isCertified() {
		return certified;
	}

	inline int getCategory() {
		return category;
	}

	inline int getPointBlankRange() {
		return pointBlankRange + bonusPointBlankRange;
	}

	inline int getPointBlankAccuracy() {
		return pointBlankAccuracy + bonusPointBlankAccuracy;
	}

	inline int getMaxRange() {
		return maxRange + bonusMaxRange;
	}

	inline int getMaxRangeAccuracy() {
		return maxRangeAccuracy + bonusMaxRangeAccuracy;
	}

	inline int getIdealRange() {
		return idealRange + bonusIdealRange;
	}

	inline int getIdealAccuracy() {
		return idealAccuracy + bonusIdealAccuracy;
	}

	inline float getWoundsRatio() {
		return woundsRatio + bonusWoundsRatio;
	}

	inline int getArmorPiercing() {
		return armorPiercing;
	}

	/*
	 * returns the number of dots this weapon has
	 */
	inline int getNumDots() {
		return getDotCount();
	}

	/*
	 * Get the dot type of a dot at index i
	 * @param i int index of the dot
	 * @return int type corresponding to CreatureAttribute. Ex. CreatureAttribute::POISON
	 */
	inline int getDotType(int i) {
		if (getDotCount() > i && i >= 0){
			Dot* dot = dotVector.get(i);
			if (dot != NULL)
				return dot->getType();
		}
		return 0;
	}

	/*
	 * Get the affected attribute of a dot at index i
	 * @param i int index of the dot
	 * @return int attribute corresponding to CreatureAttribute. Ex. CreatureAttribute::HEALTH
	 */
	inline int getDotAttribute(int i) {
		if (getDotCount() > i && i >= 0){
			Dot* dot = dotVector.get(i);
			if (dot != NULL)
				return dot->getAttribute();
		}
		return 0;
	}

	/*
	 * Get the strength of a dot at index i
	 * @param i int index of the dot
	 * @return int strength of the dot.
	 */
	inline int getDotStrength(int i) {
		if (getDotCount() > i && i >= 0){
			Dot* dot = dotVector.get(i);
			if (dot != NULL)
				return dot->getStrength();
		}
		return 0;
	}

	/*
	 * Get the potency of a dot at index i
	 * @param i int index of the dot
	 * @return int potency of the dot. ex 100% potency will return 100
	 */
	inline int getDotPotency(int i) {
		if (getDotCount() > i && i >= 0){
			Dot* dot = dotVector.get(i);
			if (dot != NULL)
				return dot->getPotency();
		}
		return 0;
	}

	/*
	 * Get the duration in seconds for a dot at index i
	 * @param i int index of the dot
	 * @return int duration in seconds
	 */
	inline int getDotDuration(int i) {
		if (getDotCount() > i && i >= 0){
			Dot* dot = dotVector.get(i);
			if (dot != NULL)
				return dot->getDuration();
		}
		return 0;
	}

	/*
	 * Get the uses remaining on a dot at index i
	 * @param i int index of the dot
	 * @return int uses remaining or 0 if the dot is null
	 */
	inline int getDotUses(int i) {
		if (getDotCount() > i && i >= 0){
			Dot* dot = dotVector.get(i);
			if (dot != NULL)
				return dot->getUses();
		}
		return 0;
	}

	/*
	 * Decrease the uses remaining for a dot at index i
	 *@param i int index of the dot to decrease uses
	 *@return boolean true if successful, false if not.
	 */
	inline bool decreaseDotUses(int i) {
		if (getDotCount() > i && i >= 0){
			Dot* dot = dotVector.get(i);
			if (dot != NULL) {
				dot->setUses(dot->getUses() - 1);
				saveDotMap();
				return true;
			}
		}
		return false;
	}

	inline int getPowerupUses() {
		return powerupUses;
	}

	inline bool hasPowerup() {
		return (bonusMinDamage != 0 || bonusMaxDamage != 0 || bonusAttackSpeed != 0 ||
				bonusHealthAttackCost != 0 || bonusActionAttackCost != 0 || bonusMindAttackCost != 0 ||
				bonusPointBlankRange != 0 || bonusPointBlankAccuracy != 0 || bonusIdealRange != 0 ||
				bonusIdealAccuracy != 0 || bonusMaxRange != 0 || bonusMaxRangeAccuracy != 0 || bonusWoundsRatio != 0);
	}

	inline String& getCert() {
		return cert;
	}

	inline String& getXpType() {
		return xpType;
	}


	//Event Handlers
	void onBroken();
	void onDamageSliced(Player* slicer, uint8 percentage);
	void onSpeedSliced(Player* slicer, uint8 percentage);
	void onSlicingFailure(Player* slicer);

	//Actions
	void slice(Player* slicer);
	void sliceDamage(Player* slicer, uint8 percentage);
	void sliceSpeed(Player* slicer, uint8 percentage);

	friend class CombatManager;

};

#endif /*WEAPONIMPLEMENTATION_H_*/
